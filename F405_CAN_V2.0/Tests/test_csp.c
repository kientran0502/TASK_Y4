/*
 * test_csp.c
 *
 *  Created on: Sep 14, 2025
 *      Author: hoang
 */

#include "test_csp.h"
#include <cmsis_os2.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_can.h"

#include "csp.h"
#include "csp_conn.h"
#include "csp_promisc.h"
#include <stdio.h>
#include "csp_rtable.h"
#include "csp_if_can.h"

#include "can_stm32.h"

//#include "../../CAN Driver/include/can_stm32.h"

volatile uint8_t string_debug[80];

TaskHandle_t hCspSend;
TaskHandle_t hCspReceive;
TaskHandle_t hCspRouter;

CAN_FilterTypeDef canfil;
extern CAN_HandleTypeDef hcan1;
/**
   Get default CSP configuration.
*/
static uint8_t server_address = 255;
static unsigned int server_received = 0;

csp_can_interface_data_t can_interface_data_func =
{
		.cfp_packet_counter = 1,
		.tx_func = csp_can_tx_frame,
};

/* Add interface(s) */
volatile csp_iface_t csp_if_can = {0};

void CSP_Init(void)
{

  /* Initialising CSP */
uart_ring_buffer_put("Initialising CSP 2.0\r\n", 22);



csp_if_can.name = CSP_IF_CAN_DEFAULT_NAME,
csp_if_can.driver_data = &hcan1,
csp_if_can.netmask = (uint16_t)csp_id_get_host_bits(), //thiết lập netmask, giống với subnet mask của IP
//csp_if_can.nexthop = csp_can2_tx,
csp_if_can.interface_data = &can_interface_data_func;
csp_if_can.mtu = 64, ///?????????????????

  csp_init();

  csp_can_add_interface(&csp_if_can);

  csp_iface_t *can_iface = &csp_if_can;
//  csp_iflist_add(can_iface); //  Thêm interface (giao diện CAN) vào danh sách các giao diện của hệ thống CSP
//  error = csp_can_stm32_open_and_add_interface(csp_if_can.name, &can_iface, 0);
//  if (error != CSP_ERR_NONE)
//  {
//	  csp_log_error("csp_can_stm32_open_and_add_interface() failed, error: %d", error);
//  }
  /* Setting route table */

	  csp_rtable_set(0, 0, can_iface, CSP_NO_VIA_ADDRESS);

  /* Start router task with 1000 bytes of stack (priority is only supported on FreeRTOS) */
//  if(csp_route_start_task(1000, 1) != CSP_ERR_NONE)
//  {
//	  csp_log_warn("Failed to start router!");
//  }
	  xTaskCreate(vTaskCspRouter, "CSP_Router", 128 * 4, NULL, osPriorityNormal, &hCspRouter);
}

void vTaskCspRouter(void *pvParameters)
{
	uart_ring_buffer_put("Router: Router task started\r\n", 29);
	while (1)
	{
		csp_route_work();
		vTaskDelay(10);
	}
}


void vTaskCspSend(void *pvParameters)
{

	uart_ring_buffer_put("Client: Client task started\r\n", 33);
	vTaskDelay(10);

	// unsigned int count = 'A';

	for(;;) 
    {
		uart_ring_buffer_put((uint8_t*)"Client: csp_transaction start\r\n", 33);

        // uint8_t tx_data[4] = {1, 2, 3, 4};
        uint8_t tx_data[] = "Tran Hoang Kien";
        uint8_t rx_data[16];
        int len = csp_transaction(CSP_PRIO_NORM, server_address, MY_SERVER_PORT, 1000, tx_data, 18, rx_data, -1);
        if (len > 0) 
        {
            sprintf((char *)string_debug, "Client: Received %d bytes!\n", len);
            uart_ring_buffer_put(string_debug, strlen((char *)string_debug));
        }
		uart_ring_buffer_put((uint8_t*)"Client: csp_transaction end\r\n", 31);
		vTaskDelay(500);
	}

}



void vTaskCspReceive(void *pvParameters)
{

	sprintf(string_debug, "server task started\n");
	uart_ring_buffer_put(string_debug, strlen((char *)string_debug));

	/* Create socket with no specific socket options, e.g. accepts CRC32, HMAC, etc. if enabled during compilation */
	csp_socket_t sock = {0};
    
	/* Bind socket to all ports, e.g. all incoming connections will be handled here */
	csp_bind(&sock, CSP_ANY);

	/* Create a backlog of 10 connections, i.e. up to 10 new connections can be queued */
	csp_listen(&sock, 10);

	/* Wait for connections and then process packets on the connection */
	for(;;) 
	{

		/* Wait for a new connection, 10000 mS timeout */
		csp_conn_t *conn;
		sprintf(string_debug, "Server: Wait for a new connection\n");
		uart_ring_buffer_put(string_debug, strlen((char *)string_debug));
		if ((conn = csp_accept(&sock, 10000)) == NULL) 
		{
			/* timeout */
			continue;
		}

		/* Read packets on connection, timout is 100 mS */
		csp_packet_t *packet;
		while ((packet = csp_read(conn, 50)) != NULL) 
		{
			switch (csp_conn_dport(conn)) {
			case MY_SERVER_PORT:
				/* Process packet here */
				sprintf(string_debug, "Server: Packet received on MY_SERVER_PORT: %s\n", (const char *) packet->data);
				uart_ring_buffer_put(string_debug, strlen((char *)string_debug));
				csp_buffer_free(packet);
				++server_received;
				vTaskDelay(500);
				break;

			default:
				/* Call the default CSP service handler, handle pings, buffer use, etc. */
				csp_service_handler(packet);
				break;
			}
		}

		/* Close current connection */
		csp_close(conn);
		vTaskDelay(500);

	}
}



