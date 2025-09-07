/*
 * queuex.c
 *
 *  Created on: Aug 20, 2025
 *      Author: hoang
 */

#include "queuex.h"
#include <string.h>

/**
 * @brief Khởi tạo hàng đợi
 * @param queue: Con trỏ tới cấu trúc hàng đợi
 * @param buffer: Buffer để lưu dữ liệu
 * @param size: Kích thước buffer
 * @return true nếu thành công
 */
bool Queue_Init(Queuex_t* queue, uint8_t* buffer, uint32_t size) {
    if (queue == NULL || buffer == NULL || size == 0) {
        return false;
    }

    queue->buffer = buffer;
    queue->size = size;
    queue->head = 0;
    queue->tail = 0;

    // Xóa buffer
    memset(buffer, 0, size);

    return true;
}

/**
 * @brief Đẩy một byte vào hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @param data: Byte cần đẩy vào
 * @return true nếu thành công
 */
bool Queue_Push(Queuex_t* queue, uint8_t data) {
    if (queue == NULL || Queue_Is_Full(queue)) {
        return false;
    }

    queue->buffer[queue->head] = data;
    queue->head = (queue->head + 1) % queue->size;

    return true;
}

/**
 * @brief Đẩy nhiều byte vào hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @param data: Con trỏ tới dữ liệu
 * @param len: Số byte cần đẩy
 * @return Số byte thực tế đã đẩy vào
 */
uint32_t Queue_Push_Buffer(Queuex_t* queue, const uint8_t* data, uint32_t len)
{
    if (queue == NULL || data == NULL || len == 0)
    {
        return 0;
    }

    uint32_t free_space = Queue_Free_Space(queue);
    uint32_t to_push = (len > free_space) ? free_space : len;

//    for (uint32_t i = 0; i < to_push; i++) {
//        queue->buffer[queue->head] = data[i];
//        queue->head = (queue->head + 1) % queue->size;

    // Vị trí bắt đầu
    uint32_t first_chunk = queue->size - queue->head;
    if (first_chunk > to_push)
    {
        first_chunk = to_push;
        memcpy(&queue->buffer[queue->head], data, first_chunk);
    }
    else
    {
		memcpy(&queue->buffer[queue->head], data, first_chunk); // Copy phần đầu
	    uint32_t second_chunk = to_push - first_chunk;
	    memcpy(queue->buffer, data + first_chunk, second_chunk); // Copy phần còn lại
    }

    // Cập nhật head
    queue->head = (queue->head + to_push) % queue->size;

    return to_push;
}

/**
 * @brief Lấy một byte từ hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @param data: Con trỏ để lưu byte lấy ra
 * @return true nếu thành công
 */
bool Queue_Pop(Queuex_t* queue, uint8_t* data) {
    if (queue == NULL || data == NULL || Queue_Is_Empty(queue)) {
        return false;
    }

    *data = queue->buffer[queue->tail];
    queue->tail = (queue->tail + 1) % queue->size;

    return true;
}

/**
 * @brief Lấy nhiều byte từ hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @param buffer: Buffer để lưu dữ liệu
 * @param max_len: Số byte tối đa muốn lấy
 * @return Số byte thực tế đã lấy
 */
uint32_t Queue_Pop_Buffer(Queuex_t* queue, uint8_t* buffer, uint32_t max_len) {
    if (queue == NULL || buffer == NULL || max_len == 0) {
        return 0;
    }

    uint32_t available = Queue_Available(queue);
    uint32_t to_pop = (max_len > available) ? available : max_len;

//    for (uint32_t i = 0; i < to_pop; i++) {
//        buffer[i] = queue->buffer[queue->tail];
//        queue->tail = (queue->tail + 1) % queue->size;
//    }

    // Vị trí bắt đầu từ tail
    uint32_t first_chunk = queue->size - queue->tail;
    if (to_pop <= first_chunk)
    {
        memcpy(buffer, &queue->buffer[queue->tail], to_pop);
    }
    else
    {
    	memcpy(buffer, &queue->buffer[queue->tail], first_chunk); // Copy phần đầu
	    uint32_t second_chunk = to_pop - first_chunk;
	    memcpy(buffer + first_chunk, queue->buffer, second_chunk); // Copy phần còn lại
    }

    // Cập nhật tail
    queue->tail = (queue->tail + to_pop) % queue->size;

    return to_pop;
}

/**
 * @brief Xem trước dữ liệu mà không lấy ra
 * @param queue: Con trỏ tới hàng đợi
 * @param buffer: Buffer để lưu dữ liệu
 * @param max_len: Số byte tối đa muốn xem
 * @return Số byte thực tế đã copy
 */
uint32_t Queue_Peek(Queuex_t* queue, uint8_t* buffer, uint32_t max_len) {
    if (queue == NULL || buffer == NULL || max_len == 0) {
        return 0;
    }

    uint32_t available = Queue_Available(queue);
    uint32_t to_copy = (max_len > available) ? available : max_len;
    uint32_t temp_tail = queue->tail;

    for (uint32_t i = 0; i < to_copy; i++) {
        buffer[i] = queue->buffer[temp_tail];
        temp_tail = (temp_tail + 1) % queue->size;
    }

    return to_copy;
}

/**
 * @brief Lấy số byte có sẵn trong hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @return Số byte có sẵn
 */
uint32_t Queue_Available(Queuex_t* queue) {
    if (queue == NULL) {
        return 0;
    }

    if (queue->head >= queue->tail) {
        return queue->head - queue->tail;
    } else {
        return queue->size - queue->tail + queue->head;
    }
}

/**
 * @brief Lấy số byte trống trong hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @return Số byte trống
 */
uint32_t Queue_Free_Space(Queuex_t* queue) {
    if (queue == NULL) {
        return 0;
    }

    return queue->size - 1 - Queue_Available(queue);
}

/**
 * @brief Kiểm tra hàng đợi có rỗng không
 * @param queue: Con trỏ tới hàng đợi
 * @return true nếu rỗng
 */
bool Queue_Is_Empty(Queuex_t* queue) {
    if (queue == NULL) {
        return true;
    }

    return queue->head == queue->tail;
}

/**
 * @brief Kiểm tra hàng đợi có đầy không
 * @param queue: Con trỏ tới hàng đợi
 * @return true nếu đầy
 */
bool Queue_Is_Full(Queuex_t* queue) {
    if (queue == NULL) {
        return true;
    }

    return ((queue->head + 1) % queue->size) == queue->tail;
}

/**
 * @brief Xóa tất cả dữ liệu trong hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 */
void Queue_Flush(Queuex_t* queue) {
    if (queue == NULL) {
        return;
    }

    queue->head = 0;
    queue->tail = 0;
}

/**
 * @brief Tìm kiếm một byte trong hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @param target: Byte cần tìm
 * @return Vị trí của byte (-1 nếu không tìm thấy)
 */
int32_t Queue_Find(Queuex_t* queue, uint8_t target) {
    if (queue == NULL || Queue_Is_Empty(queue)) {
        return -1;
    }

    uint32_t temp_tail = queue->tail;
    uint32_t available = Queue_Available(queue);

    for (uint32_t i = 0; i < available; i++) {
        if (queue->buffer[temp_tail] == target) {
            return (int32_t)i;
        }
        temp_tail = (temp_tail + 1) % queue->size;
    }

    return -1;
}

/**
 * @brief Tìm kiếm một chuỗi trong hàng đợi
 * @param queue: Con trỏ tới hàng đợi
 * @param pattern: Chuỗi cần tìm
 * @param pattern_len: Độ dài chuỗi
 * @return Vị trí bắt đầu của chuỗi (-1 nếu không tìm thấy)
 */
int32_t Queue_Find_Pattern(Queuex_t* queue, const uint8_t* pattern, uint32_t pattern_len) {
    if (queue == NULL || pattern == NULL || pattern_len == 0 || Queue_Is_Empty(queue)) {
        return -1;
    }

    uint32_t available = Queue_Available(queue);
    if (available < pattern_len) {
        return -1;
    }

    for (uint32_t i = 0; i <= available - pattern_len; i++) {
        uint32_t temp_pos = (queue->tail + i) % queue->size;
        bool found = true;

        for (uint32_t j = 0; j < pattern_len; j++) {
            uint32_t check_pos = (temp_pos + j) % queue->size;
            if (queue->buffer[check_pos] != pattern[j]) {
                found = false;
                break;
            }
        }

        if (found) {
            return (int32_t)i;
        }
    }

    return -1;
}

uint8_t* Queue_Get_Header_Address(Queuex_t* queue)
{
    if (queue == NULL)
    {
        return NULL;
    }
    return &queue->buffer[queue->head];
}

uint32_t Queue_Get_Header_Index(Queuex_t* queue)
{
    if (queue == NULL)
    {
        return 0;
    }
    return queue->head;
}

uint32_t Queue_Set_Header_Position(Queuex_t* queue, uint32_t index)
{
    if (queue == NULL || index >= queue->size)
    {
        return 0;
    }
    queue->head = index;
    return queue->head;
}

uint8_t* Queue_Get_Tail_Address(Queuex_t* queue)
{
    if (queue == NULL)
    {
        return NULL;
    }
    return &queue->buffer[queue->tail];
}

uint32_t Queue_Get_Tail_Index(Queuex_t* queue)
{
    if (queue == NULL)
    {
        return 0;
    }
    return queue->tail;
}

uint32_t Queue_Set_Tail_Position(Queuex_t* queue, uint32_t index)
{
    if (queue == NULL || index >= queue->size)
    {
        return 0;
    }
    queue->tail = index;
    return queue->tail;
}


uint8_t* Queue_Get_Address_At_Index(Queuex_t* queue, uint32_t index)
{
    if (queue == NULL || index >= queue->size)
    {
        return NULL;
    }
    return &queue->buffer[index];
}