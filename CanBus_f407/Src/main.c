#include "stm32f4xx_hal.h"
#include "main.h"
void System_Clock_Config(void);
void CAN1_Init(void);
CAN_HandleTypeDef can_handler;

int main(void)
{
HAL_Init();
System_Clock_Config();
CAN1_Init();
HAL_CAN_Start(&can_handler);
CAN_Filtering();
while(1)
{
	Can1_TX("muhammet");
	Can1_RX();
}

}

void CAN1_Init(void)
{
	can_handler.Instance = CAN1;
	can_handler.Init.Mode = CAN_MODE_LOOPBACK;
	can_handler.Init.AutoBusOff = DISABLE;
	can_handler.Init.AutoRetransmission = ENABLE;
	can_handler.Init.AutoWakeUp = DISABLE;
	can_handler.Init.ReceiveFifoLocked = DISABLE;
	can_handler.Init.TimeTriggeredMode = DISABLE;
	can_handler.Init.TransmitFifoPriority = DISABLE;
	can_handler.Init.Prescaler = 1;
	can_handler.Init.SyncJumpWidth = CAN_SJW_1TQ;

	can_handler.Init.TimeSeg1 = CAN_BS1_13TQ;
	can_handler.Init.TimeSeg2 = CAN_BS2_2TQ;

	HAL_CAN_Init(&can_handler);
}
uint32_t test_varib = 0;
void Can1_TX(uint8_t data[])
{
	uint8_t TxMailBox;
	CAN_TxHeaderTypeDef can_tx_handler;
	can_tx_handler.DLC = 8;
	can_tx_handler.StdId = 0x31D;
	can_tx_handler.IDE = CAN_ID_STD;
	can_tx_handler.RTR = CAN_RTR_DATA;

	HAL_CAN_AddTxMessage(&can_handler,&can_tx_handler,data,&TxMailBox);

	while(HAL_CAN_IsTxMessagePending(&can_handler,TxMailBox));
	HAL_Delay(3000);
	test_varib = 1;
	HAL_Delay(3000);
	test_varib = 0;
}

void CAN_Filtering()
{
	//CAN_FilterRegister_TypeDef can_filtering;
	CAN_FilterTypeDef can_filtering;
	can_filtering.FilterIdHigh = 0x0000;
	can_filtering.FilterIdLow = 0x0000;
	can_filtering.FilterBank = 0;
	can_filtering.FilterFIFOAssignment = CAN_RX_FIFO0;

	can_filtering.FilterMaskIdHigh = 0x00;
	can_filtering.FilterMaskIdLow = 0x00;
	can_filtering.FilterScale = CAN_FILTERSCALE_32BIT;
	can_filtering.FilterMode = CAN_FILTERMODE_IDMASK;
	can_filtering.FilterActivation = CAN_FILTER_ENABLE;
	HAL_CAN_ConfigFilter(&can_handler,&can_filtering);
}

uint8_t veri1,veri2,veri3,veri4,veri5,veri6,veri7,veri8;
void Can1_RX()
{
	CAN_RxHeaderTypeDef can_rx_handler;
	uint8_t rcvd_msg[8];


	while(!(HAL_CAN_GetRxFifoFillLevel(&can_handler,CAN_RX_FIFO0)));


	HAL_CAN_GetRxMessage(&can_handler,CAN_RX_FIFO0,&can_rx_handler,rcvd_msg);

	veri1=rcvd_msg[0];
	veri2=rcvd_msg[1];
	veri3=rcvd_msg[2];
	veri4=rcvd_msg[3];
	veri5=rcvd_msg[4];
	veri6=rcvd_msg[5];
	veri7=rcvd_msg[6];
	veri8=rcvd_msg[7];
}






void System_Clock_Config(void)
{




}
