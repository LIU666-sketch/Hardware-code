/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32g4xx_it.h"
#include "string.h"
#include "LED.h"
#include "LCD.h"
//#include "insect.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern  uint8_t uart_dma_temp_rx[19];
extern uint8_t uart_dma_temp_tx[38];
char message[] = "\nData Format Error!";
char id1[] = "20221071116";
char id2[] = "20221071117";
char id3[] = "20221071222";
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32G4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel1 global interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */
/*
	if(__HAL_DMA_GET_FLAG(&hdma_usart1_rx,DMA_FLAG_TC1))
{
	__HAL_DMA_GET_FLAG(&hdma_usart1_rx,DMA_FLAG_TC1);
	uint8_t receive_x[19];
	Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
	LCD_PutString(50,100,(char*)receive_x,Red,White,0);
	for(int i=0;i<19;i++)
		{
		receive_x[i] = uart_dma_temp_rx[i];
		}
	if(strcmp((char*)receive_x,"A55A20221071116A5A5")==0)
	{

	HAL_UART_Transmit_DMA(&huart1,(uint8_t*)id1,11);
	Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
	LCD_PutString(50,60,"Finished",Red,White,0);
	LCD_PutString(50,60,"Liu Fenyi",Red,White,0);
	LCD_PutString(50,100,"20221071116",Red,White,0);
//	LCD_Fill_Pic(50,130,120,120, piclfy);

}
	if(strcmp((char*)receive_x,"A55A20221071117A5A5")==0)
	{
		HAL_UART_Transmit_DMA(&huart1,(uint8_t*)id2,11);
		Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
			LCD_PutString(50,60,"Finished",Red,White,0);
		LCD_PutString(50,60,"Ma Xinyu",Red,White,0);
		LCD_PutString(50,100,"20221071117",Red,White,0);
//		LCD_Fill_Pic(50,130,120,120, picmxy);

	}
	if(strcmp((char*)receive_x,"A55A20221071222A5A5")==0)
	{
		HAL_UART_Transmit_DMA(&huart1,(uint8_t*)id3,11);
		Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
			LCD_PutString(50,60,"Finished",Red,White,0);
		LCD_PutString(50,45,"Yu Changjiang",Red,White,0);
		LCD_PutString(50,60,"20221071222",Red,White,0);
//		LCD_Fill_Pic(50,130,120,120, picycj);

	}
		if(strcmp((char*)receive_x,"A55AA5A5")==0)
	{
    Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
		LCD_PutString(50,60,"Chuan Kou Tong Xin",Red,White,0);
    LCD_PutString(50,100,"Yan Shi Xi Tong",Red,White,0);
    LCD_PutString(50,140,"Liu Fenyi 20221071116",Red,White,0);
    LCD_PutString(50,180,"Ma Xinyu 20221071117",Red,White,0);
    LCD_PutString(30,220,"Yu Changjiang 20221071222",Red,White,0);
    LCD_PutString(50,260,"Please Press!",Red,White,0);
		for(int i=0;uart_dma_temp_rx[i]!='\0';i++)
		{
		 uart_dma_temp_rx[i] = '\0';
		}
	}
	if(strcmp((char*)receive_x,"A55A20221071116A5A5")!=0&strcmp((char*)receive_x,"A55A20221071117A5A5")!=0&strcmp((char*)receive_x,"A55A20221071222A5A5")!=0&strcmp((char*)receive_x,"A55AA5A5")!=0)
	{
		for(int i=0;i<19;i++)
		{
		uart_dma_temp_tx[i] = uart_dma_temp_rx[i];
		}
		for(int i=19;i<38;i++)
		{
			uart_dma_temp_tx[i] = (uint8_t)message[i-19];
		}
		HAL_UART_Transmit_DMA(&huart1,(uint8_t*)uart_dma_temp_tx,38);
		HAL_UART_Transmit_DMA(&huart1,(uint8_t*)message,11);

		Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
		LCD_PutString(50,60,"Chuan Kou Tong Xin",Red,White,0);
    LCD_PutString(50,100,"Yan Shi Xi Tong",Red,White,0);
    LCD_PutString(50,140,"Liu Fenyi 20221071116",Red,White,0);
    LCD_PutString(50,180,"Ma Xinyu 20221071117",Red,White,0);
    LCD_PutString(30,220,"Yu Changjiang 20221071222",Red,White,0);
    LCD_PutString(50,260,"Please Press!",Red,White,0);

	}
}
*/
  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel2 global interrupt.
  */
void DMA1_Channel2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel2_IRQn 0 */

  /* USER CODE END DMA1_Channel2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* USER CODE BEGIN DMA1_Channel2_IRQn 1 */

  /* USER CODE END DMA1_Channel2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
