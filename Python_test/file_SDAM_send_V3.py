





# C:\Users\hoang\Desktop\Đo_an_1.docx
# C:\Users\hoang\Desktop\Bao_cao_thuc_tap.pptx
# C:\Users\hoang\Desktop\download.png



import serial
import struct
import time
import os
import threading
from CRC import calculate_crc32  # giữ nguyên hàm CRC bạn viết

# Cố định COM14
ser = serial.Serial("COM14", baudrate=115200, timeout=1.5, write_timeout=5)


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
    try:
        with open(filepath, "rb") as f:
            data = f.read()
    except FileNotFoundError:
        print(f"[HOST] File not found: {filepath}")
        return

    file_size = len(data)
    crc32 = calculate_crc32(data)

    print(f"[HOST] Sending file: {filepath}")
    print(f"  Size = {file_size} bytes")
    print(f"  CRC32 = 0x{crc32:08X}")

    # 1. Gửi command
    ser.write(b"SEND\n")
    ser.flush()

    # 2. Chờ READY
    resp = wait_response(2.0)
    if "READY" not in resp:
        print(f"[HOST] Error: no READY, got '{resp}'")
        return

    print("[DEVICE]", resp)

    # 3. Gửi size
    ser.write(struct.pack("<I", file_size))
    ser.flush()

    # 4. Gửi data theo từng chunk
    CHUNK = 1024  # 1KB / chunk, có thể chỉnh 4096 nếu ổn định
    sent = 0
    with open(filepath, "rb") as f:
        while True:
            chunk = f.read(CHUNK)
            if not chunk:
                break
            ser.write(chunk)
            ser.flush()
            sent += len(chunk)
            # In tiến độ
            if sent % (256 * 1024) == 0 or sent == file_size:  # mỗi 256KB báo 1 lần
                print(f"[HOST] Sent {sent}/{file_size} bytes")

    # 5. Gửi CRC
    ser.write(struct.pack("<I", crc32))
    ser.flush()

    # 6. Chờ ACK/ERR
    resp = wait_response(2.0)
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

    # Đọc data theo chunk
    CHUNK = 1024
    received = 0
    data = bytearray()

    while received < file_size:
        # Đọc tối đa còn thiếu, nhưng không vượt quá CHUNK
        need = min(CHUNK, file_size - received)
        chunk = ser.read(need)
        if not chunk:
            print(f"[HOST] Error: timeout, only received {received}/{file_size} bytes")
            return
        data.extend(chunk)
        received += len(chunk)

        if received % (256 * 1024) == 0 or received == file_size:
            print(f"[HOST] Received {received}/{file_size} bytes")

    print(f"[DEVICE] Length file data sent real : {len(data)} bytes")

    time.sleep(0.1)  # Đảm bảo dữ liệu đã sẵn sàng
    # Đọc CRC
    crc_bytes = ser.read(4)
    print(f"[DEVICE] Length file CRC sent real : {len(crc_bytes)} bytes")
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



# --- Thread wrapper ---
def send_thread(path):
    send_file(path)


def recv_thread(filename):
    receive_file(filename)


if __name__ == "__main__":
    while True:
        print("\n=== USB FILE TRANSFER MENU (Threaded) ===")
        print("1. Send file to device")
        print("2. Receive file from device")
        print("0. Exit")
        choice = input("Select option: ").strip()

        if choice == "1":
            path = input("Enter file path to send: ").strip()
            t = threading.Thread(target=send_thread, args=(path,), daemon=True)
            t.start()
        elif choice == "2":
            filename = input("Enter file name (e.g. output.bin): ").strip()
            t = threading.Thread(target=recv_thread, args=(filename,), daemon=True)
            t.start()
        elif choice == "0":
            break
        else:
            print("Invalid choice")
