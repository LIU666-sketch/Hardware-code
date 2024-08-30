/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "dma.h"
#include "usart.h"
#include "dma.h"
#include "gpio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LED.h"
#include "LCD.h"
//#include "key.h"
#include "math.h"
#include "insect.h"
#include "stdio.h"
#include "string.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

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
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// 全局变量
uint8_t mode = 0;
uint8_t receivedData[50];
uint8_t sendData[50];
uint8_t UART_temp1[5]="A55A0";
uint8_t UART_temp2[11], UART_temp3[5];
int sign = 1;
// 初始化函数

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_USART1_UART_Init(void);
void MX_LCD_Init(void);

typedef enum {
    NONE,
    KEY1,
    KEY2,
    KEY3
} KeyPress_t;

volatile KeyPress_t currentKeyPress = NONE;

// 按键中断处理函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
}
uint8_t UART_temp;
uint8_t uart_dma_temp_rx[19];
uint8_t uart_dma_temp_tx[38];

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{  /* USER CODE BEGIN 1 */
	
	 /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Receive(&huart1,UART_temp1,255,1);
	LCD_Initial();
	Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,Blue);
	Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,Red);
	BlockWrite(0,400,0,400);


	int i,j;
	const unsigned char*  pic;
	int x = 0;
	int y = 0; //guang biao bian liang
	int num=0;
	unsigned char key_value;
	uint8_t receivedData = 0;

	//8.menu
	Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
	HAL_Delay(200);

   // 显示功能界面1
	LCD_PutString(30,60,"system of chuankou tongxin",Red,White,0 );
	LCD_PutString(30,90,"liu fenyi 20221071001",Red,White,0 );
	LCD_PutString(30,130,"ma xinyu 20221071001",Red,White,0 );
	LCD_PutString(30,170,"yu changjiang 20221071001",Red,White,0 );
  LCD_PutString(70,220,"mode 0",Red,White,0 );


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
 while (1)     //大while
 {
		// 主循环，根据按键和串口接收的数据进行不同的操作
        // 这里省略具体的实现逻辑
	 int num=0;
	if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4) == 0) // 按键1,进行模式循环切换，分别为模式0123，
    {
							Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
        mode = (mode + 1) % 4;
        switch (mode)
        {
        case 0:
						LED_ALL_OFF();
				    LCD_PutString(50,60,"mode 0",Red,White,0 );
            break;
        case 1:
					LED_red_ON();
				    LCD_PutString(50,80,"mode 1",Red,White,0 );
            HAL_UART_Transmit(&huart1, (uint8_t *)"KEY1 Press!\n", 12, HAL_MAX_DELAY);
            sprintf((char *)sendData, "A55A20221071001A5A5");
            HAL_UART_Transmit(&huart1, sendData, strlen((char *)sendData), HAL_MAX_DELAY);
            break;
        case 2:
					LED_green_ON();
				    LCD_PutString(50,100,"mode 2",Red,White,0 );
            HAL_UART_Transmit(&huart1, (uint8_t *)"KEY2 Press!\n", 12, HAL_MAX_DELAY);
            sprintf((char *)sendData, "A55A20221071002A5A5");
            HAL_UART_Transmit(&huart1, sendData, strlen((char *)sendData), HAL_MAX_DELAY);
            break;
        case 3:
					LED_ALL_ON();
            LCD_PutString(50,120,"mode 3",Red,White,0 );    
				HAL_UART_Transmit(&huart1, (uint8_t *)"KEY3 Press!\n", 12, HAL_MAX_DELAY);
            sprintf((char *)sendData, "A55A20221071003A5A5");
            HAL_UART_Transmit(&huart1, sendData, strlen((char *)sendData), HAL_MAX_DELAY);
            break;
        }
    }
    else if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5) == 0) // 按键2
    {
			uint8_t a_1[12] = "KEY1 Press!", b_1[22] = "A55A 20221071116 A5A5",
	    a_2[12] = "KEY2 Press!", b_2[22] = "A55A 20221071117 A5A5",
	    a_3[12] = "KEY3 Press!", b_3[22] = "A55A 20221071222 A5A5",
	    d[19] = "Data Format Error!",
	    num_1[11] = "20221071116", num_2[11] = "20221071117", num_3[11] = "20221071222", 
	    num_4[5] = "A55AA";
        // 切换到功能界面2
			Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
			LCD_PutString(50,120,"system of chuankou tongxin",Red,White,0 );    
			LCD_PutString(50,140,"Receiving data...",Red,White,0 );
			while(1)
			{
									
        //LCD_DisplayStringLine(0, "串口通信系统");

				if(HAL_UART_Receive(&huart1,UART_temp1,5,1) == HAL_OK)
		{

			HAL_UART_Receive(&huart1,UART_temp2,11,1);
			HAL_UART_Receive(&huart1,UART_temp3,5,1);
			Lcd_ColorBox(0, 0, 240, 320, White);
			
			if(memcmp(UART_temp2, num_1, 11) == 0)
			{
				HAL_UART_Transmit(&huart1,UART_temp2,11,1);
				Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
	      LCD_PutString(50,60,"Liu Fenyi",Red,White,0);
	      LCD_PutString(50,100,"20221071116",Red,White,0);
				//	LCD_Fill_Pic(50,130,120,120, piclfy);

			}
			else if(memcmp(UART_temp2, num_2, 11) == 0)
			{
				HAL_UART_Transmit(&huart1,UART_temp2,11,1);
				Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
		    LCD_PutString(50,60,"Ma Xinyu",Red,White,0);
				//		LCD_Fill_Pic(50,130,120,120, picmxy);
		    LCD_PutString(50,100,"20221071117",Red,White,0);
			}
			else if(memcmp(UART_temp2, num_3, 11) == 0)
			{
				HAL_UART_Transmit(&huart1,UART_temp2,11,1);
				Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
		    LCD_PutString(50,45,"Yu Changjiang",Red,White,0);
		    LCD_PutString(50,60,"20221071222",Red,White,0);
								//		LCD_Fill_Pic(50,130,120,120, picycj);//转换界面效果
			}
			else if(memcmp(UART_temp1, num_4, 5) == 0)
			{
 // 显示功能界面1
	LCD_PutString(30,60,"system of chuankou tongxin",Red,White,0 );
	LCD_PutString(30,90,"liu fenyi 20221071001",Red,White,0 );
	LCD_PutString(30,130,"ma xinyu 20221071001",Red,White,0 );
	LCD_PutString(30,170,"yu changjiang 20221071001",Red,White,0 );
  LCD_PutString(70,220,"mode 0",Red,White,0 );
				break;
			}
			else
			{
				HAL_UART_Transmit(&huart1,UART_temp1,5,1);
				HAL_UART_Transmit(&huart1,UART_temp2,11,1);
				HAL_UART_Transmit(&huart1,UART_temp3,5,1);
				HAL_Delay(500);
				HAL_UART_Transmit(&huart1,d,18,1);
				HAL_Delay(500);
				Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
			  LCD_PutString(50,120,"system of chuankou tongxin",Red,White,0 );    
			  LCD_PutString(50,140,"Receiving data...",Red,White,0 );
			}
			HAL_UART_Receive(&huart1,UART_temp1,255,1);
			}
    }
	}

		else if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6) == 0) // 按键3
    {
        // 切换到功能界面4
        // 这里省略具体的实现逻辑
		
	
		while (1)     //大while
    {
		// 主循环，根据按键和串口接收的数据进行不同的操作
        // 这里省略具体的实现逻辑

        if (mode == 1) {
					  Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
            //LCD_PutString(20,20,"A",Red,White,0);
						LCD_Fill_Pic(20,20,120,120, picA);
					while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x02&&num==0)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic2);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x00&&num==1)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic0);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x02&&num==2)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic2);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x02&&num==3)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic2);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x01&&num==4)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic1);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x00&&num==5)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic0);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x07&&num==6)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic7);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x01&&num==7)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic1);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x01&&num==8)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic1);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x01&&num==9)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic1);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x06&&num==10)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic6);
								break;
						  }
					 }
					if(num==11)
					{
						 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
						//gongnengzhanshi
							Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
							LCD_PutString(50,60,"Liu Fenyi",Red,White,0);
							LCD_PutString(50,100,"20221071116",Red,White,0);
							LCD_Fill_Pic(50,130,120,120, piclfy);
							mode=0;
						num=0;
							HAL_Delay(500);
					}
					
				}
				
				//展示马新宇的信息
        if (mode == 2) {
					  Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
						LCD_Fill_Pic(20,20,120,120, picB);
					while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x02&&num==0)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic2);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x00&&num==1)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic0);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x02&&num==2)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic2);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x02&&num==3)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic2);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x01&&num==4)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic1);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x00&&num==5)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic0);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x07&&num==6)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic7);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x01&&num==7)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic1);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x01&&num==8)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic1);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x01&&num==9)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic1);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x07&&num==10)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic7);
								break;
						  }
					 }
					if(num==11)
					{
						 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
						//gongnengzhanshi
							Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
							LCD_PutString(50,60,"MA Xinyu",Red,White,0);
							LCD_PutString(50,100,"20221071117",Red,White,0);
							LCD_Fill_Pic(50,130,120,120, picmxy);
							mode=0;
						num = 0;
							HAL_Delay(500);
					}
					
				}
				
				//展示于长江的信息
        if (mode == 3) {
					  Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
            //LCD_PutString(20,20,"A",Red,White,0);
						LCD_Fill_Pic(20,20,120,120, picC);
					while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x02&&num==0)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic2);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x00&&num==1)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic0);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x02&&num==2)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic2);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x02&&num==3)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic2);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x01&&num==4)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic1);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x00&&num==5)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic0);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x07&&num==6)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic7);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x01&&num==7)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic1);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x02&&num==8)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic2);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x02&&num==9)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic2);
								break;
						  }
					 }
					
					 while(1)
					{
						uint8_t receivedData = 9;
						HAL_UART_Receive(&huart1, &receivedData, 1, HAL_MAX_DELAY);
            if (receivedData == 0x02&&num==10)
							{
								num=num+1;
								 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
								LCD_Fill_Pic(20,20,120,120, pic2);
								break;
						  }
					 }
					if(num==11)
					{
						 Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
						//gongnengzhanshi
							Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
							LCD_PutString(50,60,"YU changjiang",Red,White,0);
							LCD_PutString(50,100,"20221071222",Red,White,0);
							LCD_Fill_Pic(50,130,120,120, picycj);
						num=0;
							mode=0;
							HAL_Delay(500);
					}
					
				}
				
				
				break;
			}										
		}	
 
						
   // 模式2和模式3处理类似
        // 模式2和模式3处理类似
    
  /* USER CODE END 3 */
 }
 }

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//外部中断处理
// 串口接收中断处理函数
/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
    {
        if (strncmp((char *)receivedData, "A55A", 4) == 0 && strncmp((char *)(receivedData + 14), "A5A5", 4) == 0)
        {
            // 收到正确数据
            //LCD_Clear();
						Lcd_ColorBox(0,0,XSIZE_PHYS,YSIZE_PHYS,White);
							LCD_PutString(50,200,"收到正确数据",Red,White,0 );
           
					if (strncmp((char *)(receivedData + 4), "20221071001", 11) == 0)
            {
							LCD_PutString(50,200,"zhangsan",Red,White,0 );
            }
            else if (strncmp((char *)(receivedData + 4), "20221071002", 11) == 0)
            {
							LCD_PutString(50,200,"lisi",Red,White,0 );
            }
						else if (strncmp((char *)(receivedData + 4), "20221071003", 11) == 0)
            {
							LCD_PutString(50,200,"wangwu",Red,White,0 );
            }

            // 显示头像照片（这里假设有函数LCD_DisplayPhoto用于显示照片）
         //	LCD_Fill_Pic(50,130,120,120, picycj); // 需要根据实际情况调整照片
        }
        else
        {
            // 数据格式错误
            HAL_UART_Transmit(&huart1, receivedData, strlen((char *)receivedData), HAL_MAX_DELAY);
            HAL_UART_Transmit(&huart1, (uint8_t *)"Data Format Error!\n", 19, HAL_MAX_DELAY);
												LCD_PutString(50,200,"串口通信系统",Red,White,0 );
												LCD_PutString(50,200,"正在接收串口数据",Red,White,0 );

        }

        // 重新开启接收中断
        HAL_UART_Receive_DMA(&huart1, receivedData, sizeof(receivedData));
    }
}
*/

/*
	HAL_Delay(5);
	
	if(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4))
	{
	HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4));
	}
}
*/


/*
else if(GPIO_Pin==GPIO_PIN_5)
{

	if(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5))
	{
		HAL_Delay(5);
	HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5));
	}
}
}
*/
/*

*/
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
