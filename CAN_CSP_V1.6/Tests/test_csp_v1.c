/*
 * test_csp_v1.c
 *
 *  Created on: Sep 25, 2025
 *      Author: hoang
 */

#include "test_csp_v1.h"
#include <cmsis_os2.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_can.h"
//
//#include "csp.h"
//#include "csp_conn.h"
//#include "csp_promisc.h"
#include "debug_logger.h"
#include <stdio.h>
#include "csp_if_can.h"
#include "packet.h"
#include "csp_io.h"
//#include "csp_types.h"

#include <csp/csp.h>
//#include <csp/drivers/can_socketcan.h>



#define PROTOCOL_CAN_ADDR		2
#define PROTOCOL_OBC_ADDR		1
#define PROTOCOL_TIMEOUT_HM 	100

volatile uint8_t string_debug[80];

TaskHandle_t hCspSend;
TaskHandle_t hCspReceive;
TaskHandle_t hCspRouter;

CAN_FilterTypeDef canfil;
extern CAN_HandleTypeDef hcan1;

/**
   Get default CSP configuration.
*/
//
//struct csp_can_config can_conf = {
//    .bitrate = 500000,    // 500 kbps
//    .clock_speed = 36000000, // Clock của CAN1 trên STM32F4 (APB1 = 36 MHz)
//    .ifc = NULL           // không dùng socketCAN
//};

//csp_can_interface_data_t can_interface_data_func =
//{
//		.cfp_packet_counter = 1,
//		.tx_func = csp_can_tx_frame,
//};
//
///* Add interface(s) */
//csp_iface_t csp_if_can =
//{
//		.name = "CAN",
//		.driver_data = &hcan1,
//		.netmask = (uint16_t)csp_id_get_host_bits(), //thiết lập netmask, giống với subnet mask của IP
//		.interface_data = &can_interface_data_func,
//		.mtu = 64,
//};

void CSP_Init(void)
{

//	  /* Initialising CSP */
//	uart_ring_buffer_put("Initialising CSP 1.1\r\n", 22);
//
//	// CSP-related settings
//	csp_buffer_init(2, 300); // Creating 2 buffers of size 300 bytes each
//	csp_init(PROTOCOL_CAN_ADDR); // Initialize to node's address
//	if (csp_can_init(CSP_CAN_PROMISC, &can_conf) != CSP_ERR_NONE)
//	{
//		uart_ring_buffer_put("CSP CAN init failed!\r\n", 23);
//	}
//	csp_iflist_add(&csp_if_can);
////	csp_route_set(PROTOCOL_OBC_ADDR, &csp_if_can, PROTOCOL_OBC_ADDR);
//	csp_route_set(CSP_DEFAULT_ROUTE, &csp_if_can, CSP_NODE_MAC);
//	csp_route_start_task(500, osPriorityNormal - 1); // Start the router task in CSP


    /* Init CSP with address and default settings */
    csp_conf_t csp_conf;
    csp_conf_get_defaults(&csp_conf);
    csp_conf.address = address;
    int error = csp_init(&csp_conf);
    if (error != CSP_ERR_NONE) {
        csp_log_error("csp_init() failed, error: %d", error);
        exit(1);
    }

    /* Start router task with 10000 bytes of stack (priority is only supported on FreeRTOS) */
    csp_route_start_task(500, 0);
}

//void vTaskCspRouter(void *pvParameters)
//{
//	uart_ring_buffer_put("Router: Router task started\r\n", 29);
//	while (1)
//	{
//		csp_route_work();
//		vTaskDelay(10);
//	}
//}


void vTaskCspSend(void *pvParameters)
{
    uart_ring_buffer_put((uint8_t*)"Client: Task started\r\n", 24);
    vTaskDelay(pdMS_TO_TICKS(10));

    const uint8_t server_address = 1;   // node server
    const uint8_t server_port    = 8;   // port server

    while (1)
    {
        // Tạo connection tới server
        csp_conn_t *conn = csp_connect(CSP_PRIO_NORM, server_address, server_port, 1000, CSP_O_NONE);
        if (conn == NULL) {
            uart_ring_buffer_put((uint8_t*)"Client: Connect failed\r\n", 26);
//            /* Debug all connection slots */
//            for (int i = 0; i < CSP_CONN_MAX; i++)
//            {
//            	uint8_t str[64] = {0};
//                extern csp_conn_t arr_conn[];
//                sprintf(str,"conn[%d]: state=%d type=%d id=0x%08X\r\n",
//                    i, arr_conn[i].state, arr_conn[i].type, arr_conn[i].idin.ext);
//                uart_ring_buffer_put(str, length);
//            }
            vTaskDelay(pdMS_TO_TICKS(1000));
            continue;
        }

        // Lấy buffer packet để chuẩn bị dữ liệu gửi
        csp_packet_t *packet = csp_buffer_get(64); // lấy buffer 64 byte
        if (packet == NULL) {
            uart_ring_buffer_put((uint8_t*)"Client: No buffer\r\n", 20);
            csp_close(conn);
            vTaskDelay(pdMS_TO_TICKS(1000));
            continue;
        }

        // Copy dữ liệu vào packet
        const char *msg = "Hello world\n";
        int len = strlen(msg);
        memcpy(packet->data, msg, len);
        packet->length = len;

        // Gửi packet đi
        if (csp_send(conn, packet, 1000) != CSP_ERR_NONE) {
            uart_ring_buffer_put((uint8_t*)"Client: Send failed\r\n", 23);
            csp_buffer_free(packet);  // giải phóng nếu lỗi
        } else {
            uart_ring_buffer_put((uint8_t*)"Client: Send success\r\n", 24);
        }

        // Đóng connection
        csp_close(conn);

        vTaskDelay(pdMS_TO_TICKS(2000)); // chờ 2s rồi gửi lại
    }
}

//csp_socket_t sock = {0};
static unsigned int server_received = 0;

void vTaskCspReceive(void *pvParameters)
{
	uart_ring_buffer_put("Server task started\n", 21);

	/* Create socket with no specific socket options, e.g. accepts CRC32, HMAC, etc. if enabled during compilation */
	csp_socket_t sock = {0};
	sock.type = CONN_OPEN;
//	csp_socket_t *sock = csp_socket(CSP_SO_NONE);

	/* Bind socket to my ports, e.g. all incoming connections will be handled here */
	csp_bind(&sock, 10);

	/* Create a backlog of 10 connections, i.e. up to 10 new connections can be queued */
	csp_listen(&sock, 10);

	/* Wait for connections and then process packets on the connection */
	while (1) {

		/* Wait for a new connection, 10000 mS timeout */
		csp_conn_t *conn;
		if ((conn = csp_accept(&sock, 3000)) == NULL) {
			/* timeout */
			continue;
		}

		/* Read packets on connection, timout is 100 mS */
		csp_packet_t *packet;
		while ((packet = csp_read(conn, 50)) != NULL) {
			switch (csp_conn_dport(conn)) {
			case MY_SERVER_PORT:
				/* Process packet here */
				uint8_t str[40] = {0};
				sprintf(str,"Packet received on MY_SERVER_PORT: %s\n", (char *) packet->data);
				uart_ring_buffer_put(str, strlen(str));
				csp_buffer_free(packet);
				++server_received;
				break;

			default:
				/* Call the default CSP service handler, handle pings, buffer use, etc. */
//				csp_service_handler(packet);
				break;
			}
		}

		/* Close current connection */
		csp_close(conn);

	}

	return;
}
