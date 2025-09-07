/*
 * usb_test_dummy.c
 *
 *  Created on: Aug 29, 2025
 *      Author: hoang
 */


//void TaskSendImage(void *pvParameters)
//{
//	uint32_t indx = 0;
//	uint8_t dummy[4048];
//    for (;;)
//    {
//        if (current_state == STATE_SEND_IMAGE)
//        {
//        	switch (current_stage)
//        	{
//        		case FIRST_CHUNK:
////        			Transmit_Send_Chunk(tx_state.current_chunk, &image_buffer[offset], chunk_size);
//        			if((!Check_Flag_Complete_Transmit()))
//        			{
//            			CDC_Transmit_HS(&dummy[indx], 2048);
//            			indx = indx + 20;
////        				CDC_Transmit_HS(&dummy, 2048);
//        			}
////        			else
////        			{
////        				current_state = STATE_WAIT_COMMAND;
////        				CDC_Transmit_HS("Complete\n", 12);
////        			}
//        			break;
//        		default:
//        			break;
//        	}
//        }
////        vTaskDelay(pdMS_TO_TICKS(10)); //// Delay ngắn
//    }
//}
