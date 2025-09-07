/*
 * queue.h
 *
 *  Created on: Aug 20, 2025
 *      Author: hoang
 */

#ifndef QUEUEX_H_
#define QUEUEX_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Cấu trúc hàng đợi generic
 */
typedef struct {
    uint8_t* buffer;           // Con trỏ tới buffer
    uint32_t size;             // Kích thước buffer
    volatile uint32_t head;    // Vị trí head
    volatile uint32_t tail;    // Vị trí tail
} Queuex_t;

/**
 * @brief Khởi tạo hàng đợi
 * @param queue: Con trỏ tới cấu trúc hàng đợi
 * @param buffer: Buffer để lưu dữ liệu
 * @param size: Kích thước buffer
 * @return true nếu thành công
 */
bool Queue_Init(Queuex_t* queue, uint8_t* buffer, uint32_t size);

/**
 * @brief Đẩy một byte vào hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @param data: Byte cần đẩy vào
 * @return true nếu thành công
 */
bool Queue_Push(Queuex_t* queue, uint8_t data);

/**
 * @brief Đẩy nhiều byte vào hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @param data: Con trỏ tới dữ liệu
 * @param len: Số byte cần đẩy
 * @return Số byte thực tế đã đẩy vào
 */
uint32_t Queue_Push_Buffer(Queuex_t* queue, const uint8_t* data, uint32_t len);

/**
 * @brief Lấy một byte từ hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @param data: Con trỏ để lưu byte lấy ra
 * @return true nếu thành công
 */
bool Queue_Pop(Queuex_t* queue, uint8_t* data);

/**
 * @brief Lấy nhiều byte từ hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @param buffer: Buffer để lưu dữ liệu
 * @param max_len: Số byte tối đa muốn lấy
 * @return Số byte thực tế đã lấy
 */
uint32_t Queue_Pop_Buffer(Queuex_t* queue, uint8_t* buffer, uint32_t max_len);

/**
 * @brief Xem trước dữ liệu mà không lấy ra
 * @param queue: Con trỏ tới hàng đợi
 * @param buffer: Buffer để lưu dữ liệu
 * @param max_len: Số byte tối đa muốn xem
 * @return Số byte thực tế đã copy
 */
uint32_t Queue_Peek(Queuex_t* queue, uint8_t* buffer, uint32_t max_len);

/**
 * @brief Lấy số byte có sẵn trong hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @return Số byte có sẵn
 */
uint32_t Queue_Available(Queuex_t* queue);

/**
 * @brief Lấy số byte trống trong hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @return Số byte trống
 */
uint32_t Queue_Free_Space(Queuex_t* queue);

/**
 * @brief Kiểm tra hàng đợi có rỗng không
 * @param queue: Con trỏ tới hàng đợi
 * @return true nếu rỗng
 */
bool Queue_Is_Empty(Queuex_t* queue);

/**
 * @brief Kiểm tra hàng đợi có đầy không
 * @param queue: Con trỏ tới hàng đợi
 * @return true nếu đầy
 */
bool Queue_Is_Full(Queuex_t* queue);

/**
 * @brief Xóa tất cả dữ liệu trong hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 */
void Queue_Flush(Queuex_t* queue);

/**
 * @brief Tìm kiếm một byte trong hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @param target: Byte cần tìm
 * @return Vị trí của byte (-1 nếu không tìm thấy)
 */
int32_t Queue_Find(Queuex_t* queue, uint8_t target);

/**
 * @brief Tìm kiếm một chuỗi trong hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @param pattern: Chuỗi cần tìm
 * @param pattern_len: Độ dài chuỗi
 * @return Vị trí bắt đầu của chuỗi (-1 nếu không tìm thấy)
 */
int32_t Queue_Find_Pattern(Queuex_t* queue, const uint8_t* pattern, uint32_t pattern_len);

/**
 * @brief Lấy địa chỉ phần tử head trong queue
 */
uint8_t* Queue_Get_Header_Address(Queuex_t* queue);

/**
 * @brief Lấy chỉ số head trong queue
 */
uint32_t Queue_Get_Header_Index(Queuex_t* queue);

uint32_t Queue_Set_Header_Position(Queuex_t* queue, uint32_t index);

/**
 * @brief Lấy địa chỉ phần tử tail trong queue
 */
uint8_t* Queue_Get_Tail_Address(Queuex_t* queue);

/**
 * @brief Lấy chỉ số tail trong queue
 */
uint32_t Queue_Get_Tail_Index(Queuex_t* queue);

/**
 * @brief Đặt vị trí tail mới cho queue
 */
uint32_t Queue_Set_Tail_Position(Queuex_t* queue, uint32_t index);

uint8_t* Queue_Get_Address_At_Index(Queuex_t* queue, uint32_t index);

/**
 * @brief Macro để khởi tạo hàng đợi tĩnh
 */
#define QUEUE_DECLARE_STATIC(name, size) \
    static uint8_t name##_buffer[size]; \
    static Queuex_t name = {0}; \
    static inline bool name##_init(void) { \
        return Queue_Init(&name, name##_buffer, size); \
    }

#endif /* QUEUEX_H_ */
