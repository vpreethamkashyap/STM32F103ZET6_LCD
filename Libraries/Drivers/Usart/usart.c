/*
 * usart.c
 *
 *  Created on: Nov 15, 2011
 *      Author: MMM
 */
#include "usart.h"

void USART1Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef  USART_ClockInitStructure;
	//enable bus clocks
	/* Enable USART1 and GPIOA clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	//Configure USART1 Tx (PA.09) as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//Configure USART1 Rx (PA.10) as input floating
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	USART_ClockStructInit(&USART_ClockInitStructure);
	 USART_ClockInit(USART1, &USART_ClockInitStructure);
	USART_StructInit(&USART_InitStructure);
	//Configure USART1 basic and asynchronous paramters
	USART_Init(USART1, &USART_InitStructure);
	//Enable USART1
	USART_Cmd(USART1, ENABLE);
}
void USART2Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef  USART_ClockInitStructure;
	//enable bus clocks
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	//Configure USART1 Tx (PA.02) as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//Configure USART1 Rx (PA.03) as input floating
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_ClockStructInit(&USART_ClockInitStructure);
	 USART_ClockInit(USART2, &USART_ClockInitStructure);
	USART_StructInit(&USART_InitStructure);
	//Configure USART2 basic and asynchronous paramters
	USART_Init(USART2, &USART_InitStructure);
	//Enable USART2
	USART_Cmd(USART2, ENABLE);
}

int fputc(int ch, FILE *f)
{
  //Place your implementation of fputc here
  //e.g. write a character to the USART
  USART_SendData(USART1, (u8) ch);

  //Loop until the end of transmission
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {
  }

  return ch;
}
