/*
 * queuex_eample.c
 *
 *  Created on: Aug 20, 2025
 *      Author: hoang
 */
#include "queuex.h"
#include <stdio.h>

// Ví dụ 1: Tạo queue cho USB RX
static uint8_t usb_rx_buffer[256];
static Queue_t usb_rx_queue;

// Ví dụ 2: Sử dụng macro để tạo queue tĩnh
QUEUE_DECLARE_STATIC(uart_tx, 128);
QUEUE_DECLARE_STATIC(spi_rx, 64);

void queue_example(void) {
    // Khởi tạo queue USB RX
    if (!Queue_Init(&usb_rx_queue, usb_rx_buffer, sizeof(usb_rx_buffer))) {
        printf("Failed to init USB RX queue\n");
        return;
    }

    // Khởi tạo các queue tĩnh
    uart_tx_init();
    spi_rx_init();

    // Test push/pop đơn byte
    printf("=== Test Push/Pop Single Byte ===\n");
    uint8_t data = 0xAB;
    if (Queue_Push(&usb_rx_queue, data)) {
        printf("Pushed: 0x%02X\n", data);
    }

    uint8_t received;
    if (Queue_Pop(&usb_rx_queue, &received)) {
        printf("Popped: 0x%02X\n", received);
    }

    // Test push/pop buffer
    printf("\n=== Test Push/Pop Buffer ===\n");
    uint8_t send_data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    uint32_t pushed = Queue_Push_Buffer(&usb_rx_queue, send_data, sizeof(send_data));
    printf("Pushed %u bytes\n", pushed);

    uint8_t recv_buffer[10];
    uint32_t popped = Queue_Pop_Buffer(&usb_rx_queue, recv_buffer, sizeof(recv_buffer));
    printf("Popped %u bytes: ", popped);
    for (uint32_t i = 0; i < popped; i++) {
        printf("0x%02X ", recv_buffer[i]);
    }
    printf("\n");

    // Test peek
    printf("\n=== Test Peek ===\n");
    Queue_Push_Buffer(&usb_rx_queue, send_data, sizeof(send_data));
    printf("Available: %u bytes\n", Queue_Available(&usb_rx_queue));

    uint32_t peeked = Queue_Peek(&usb_rx_queue, recv_buffer, 3);
    printf("Peeked %u bytes: ", peeked);
    for (uint32_t i = 0; i < peeked; i++) {
        printf("0x%02X ", recv_buffer[i]);
    }
    printf("\n");
    printf("Available after peek: %u bytes\n", Queue_Available(&usb_rx_queue));

    // Test find
    printf("\n=== Test Find ===\n");
    int32_t pos = Queue_Find(&usb_rx_queue, 0x03);
    if (pos >= 0) {
        printf("Found 0x03 at position %d\n", pos);
    }

    // Test find pattern
    uint8_t pattern[] = {0x02, 0x03};
    pos = Queue_Find_Pattern(&usb_rx_queue, pattern, sizeof(pattern));
    if (pos >= 0) {
        printf("Found pattern {0x02, 0x03} at position %d\n", pos);
    }

    // Test với UART TX queue
    printf("\n=== Test UART TX Queue ===\n");
    const char* message = "Hello World!";
    uint32_t sent = Queue_Push_Buffer(&uart_tx, (const uint8_t*)message, strlen(message));
    printf("Sent to UART TX: %u bytes\n", sent);
    printf("UART TX available: %u bytes\n", Queue_Available(&uart_tx));
    printf("UART TX free space: %u bytes\n", Queue_Free_Space(&uart_tx));

    // Giả lập truyền UART
    while (!Queue_Is_Empty(&uart_tx)) {
        uint8_t byte;
        if (Queue_Pop(&uart_tx, &byte)) {
            printf("UART transmit: %c\n", byte);
        }
    }

    printf("\n=== Queue Status ===\n");
    printf("USB RX - Available: %u, Free: %u, Empty: %s, Full: %s\n",
           Queue_Available(&usb_rx_queue),
           Queue_Free_Space(&usb_rx_queue),
           Queue_Is_Empty(&usb_rx_queue) ? "Yes" : "No",
           Queue_Is_Full(&usb_rx_queue) ? "Yes" : "No");
}

// Hàm mô phỏng interrupt USB receive
void USB_RX_IRQ_Handler(void) {
    // Giả sử nhận được dữ liệu từ USB
    uint8_t received_data[] = {0xAA, 0xBB, 0xCC};

    // Đẩy vào queue (thread-safe)
    Queue_Push_Buffer(&usb_rx_queue, received_data, sizeof(received_data));
}

// Hàm mô phỏng task xử lý USB data
void USB_Process_Task(void) {
    uint8_t buffer[32];

    // Lấy dữ liệu từ queue
    uint32_t received = Queue_Pop_Buffer(&usb_rx_queue, buffer, sizeof(buffer));

    if (received > 0) {
        // Xử lý dữ liệu
        printf("Processing %u bytes from USB\n", received);
        // ... xử lý dữ liệu
    }
}

int main(void) {
    queue_example();
    return 0;
}

