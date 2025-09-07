

# C:\Users\hoang\Desktop\Đo_an_1.docx
# C:\Users\hoang\Desktop\Bao_cao_thuc_tap.pptx
# C:\Users\hoang\Desktop\anh2.jpg


import serial
import struct
import time
import os
from CRC import calculate_crc32  # giữ nguyên hàm CRC bạn viết

# Cố định COM14
ser = serial.Serial("COM14", baudrate=115200, timeout=3)


def wait_response(timeout=3):
    """Đọc phản hồi từ device trong khoảng timeout giây"""
    start = time.time()
    response = b""
    while time.time() - start < timeout:
        if ser.in_waiting > 0:
            response += ser.read(ser.in_waiting)
            if b"\n" in response:
                break
        time.sleep(0.01)
    return response.decode(errors="ignore").strip()


def send_file(filepath):
    with open(filepath, "rb") as f:
        data = f.read()

    file_size = len(data)
    crc32 = calculate_crc32(data)
#198587609
    print(f"[HOST] Sending file: {filepath}")
    print(f"  Size = {file_size} bytes")
    print(f"  CRC32 = 0x{crc32:08X}")

    # 1. Gửi command
    ser.write(b"SEND\n")
    ser.flush()

    # 2. Chờ READY
    resp = wait_response(1.5)
    if "READY" not in resp:
        print(f"[HOST] Error: no READY, got '{resp}'")
        return

    print("[DEVICE]", resp)

    # 3. Gửi size
    ser.write(struct.pack("<I", file_size))
    # 4. Gửi data
    ser.write(data)
    # 5. Gửi CRC
    ser.write(struct.pack("<I", crc32))
    ser.flush()

    # 6. Chờ ACK/ERR
    resp = wait_response(1.5)
    if resp:
        print("[DEVICE]", resp)
    else:
        print("[HOST] Timeout: no ACK from device")


def receive_file(filename):
    """Nhận file từ device và lưu ngay tại thư mục hiện tại"""
    print("[HOST] Requesting file from device...")
    ser.write(b"GET\n")
    ser.flush()

    # Đọc size
    size_bytes = ser.read(4)
    if len(size_bytes) < 4:
        print("[HOST] Error: no size received")
        return
    file_size = struct.unpack("<I", size_bytes)[0]
    print(f"[HOST] File size = {file_size} bytes")

    # Đọc data
    data = ser.read(file_size)
    if len(data) != file_size:
        print(f"[HOST] Error: file data incomplete: Only received {len(data)} bytes")
        return
    
    print(f"[DEVICE] Lentgh file data send real : {len(data)} bytes")

    # Đọc CRC
    crc_bytes = ser.read(4)
    print(f"[DEVICE] Lentgh file CRC send real : {len(crc_bytes)} bytes")
    if len(crc_bytes) < 4:
        print("[HOST] Error: no CRC received")
        return
    received_crc = struct.unpack("<I", crc_bytes)[0]

    # Tính CRC
    calc_crc = calculate_crc32(data)

    print(f"[HOST] Received CRC = 0x{received_crc:08X}")
    print(f"[HOST] Calc CRC     = 0x{calc_crc:08X}")

    if calc_crc == received_crc:
        savepath = os.path.join(os.getcwd(), filename)
        with open(savepath, "wb") as f:
            f.write(data)
        print(f"[HOST] File saved to {savepath} ✅")
    else:
        print("[HOST] CRC mismatch ❌")


if __name__ == "__main__":
    while True:
        print("\n=== USB FILE TRANSFER MENU ===")
        print("1. Send file to device")
        print("2. Receive file from device")
        print("0. Exit")
        choice = input("Select option: ").strip()

        if choice == "1":
            path = input("Enter file path to send: ").strip()
            send_file(path)
        elif choice == "2":
            filename = input("Enter file name (e.g. output.bin): ").strip()
            receive_file(filename)
        elif choice == "0":
            break
        else:
            print("Invalid choice")
