/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"

/* USER CODE BEGIN Includes */
#include "et_stm32f_arm_kit_lcd.h"
#include <string.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#define White 0xFFFF
#define Black 0x0000
#define Grey 0xF7DE
#define Grey2 0x8410
#define Grey3 0xCE79
#define Blue 0x001F
#define Blue2 0x051F
#define Blue3 0x041F
#define Blue4 0x07DFF
#define Red 0xF800
#define Magenta 0xF81F
#define Green 0x07E0
#define Green2 0x87F0
#define Cyan 0x7FFF
#define Yellow 0xFFE0
#define Yellow2 0xFFF0
#define Pink2 0xF810
#define Pink 0xFD5A
#define Purple 0xFC1F
#define Purple2 0xF81F
#define Orange 0xFC64
#define Orange2 0xFD62

//  void LCD_DrawFullFrame(uint8_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width)

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI3_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
uint32_t count;
uint16_t posX, posY;
char pos[50];
int x=0;
int y=1;
void DrawBomb(int Xpos,int Ypos);
void DrawKite(int Xpos,int Ypos);
void Draw0(int Xpos,int Ypos);
void Draw1(int Xpos,int Ypos);
void Draw2(int Xpos,int Ypos);
void Draw3(int Xpos,int Ypos);
void Draw4(int Xpos,int Ypos);
void Draw5(int Xpos,int Ypos);
void Draw6(int Xpos,int Ypos);
void Draw7(int Xpos,int Ypos);
void Draw8(int Xpos,int Ypos);
void Draw9(int Xpos,int Ypos);
void DrawFlag(int Xpos,int Ypos);
void Menu();
void Win();
void Lose();
//void DrawX(int Xpos,int Ypos,uint16_t color);
//void DrawShip(int Xpos,int Ypos,int numShip);
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_SPI3_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();

  /* USER CODE BEGIN 2 */

LCD_Setup();
//LCD_Clear(Blue2);
LCD_SetBackColor(Blue);
LCD_SetTextColor(Yellow);
//HAL_TIM_Base_Start_IT (&htim1);








  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

	if((HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_8) == GPIO_PIN_RESET)&&(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_9) == GPIO_PIN_RESET)) //State 0
	{  int ToDo=0;
		//Menu();
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_10)==GPIO_PIN_SET)
			ToDo+=1;
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_11)==GPIO_PIN_SET)
			ToDo+=2;
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12)==GPIO_PIN_SET)
			ToDo+=4;
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_13)==GPIO_PIN_SET)
			ToDo+=8;
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_14)==GPIO_PIN_SET)
			ToDo+=16;
		
	

		if(ToDo==1)
    {
		LCD_Clear(White); 
			/*
		char ch[13] =  " MINESWEEPER " ;
		for (int j=0;j<13;j++)
		{LCD_SetBackColor(White);
      LCD_SetTextColor(Red);
			LCD_DisplayChar(Line3,16*(4+j),ch[12-j]);}
		char ch2[13] = "  -- GAME -- ";
		for (int j=0;j<13;j++)
			{LCD_SetBackColor(White);
      LCD_SetTextColor(Red);
			LCD_DisplayChar(Line4,16*(4+j),ch2[12-j]);}
			*/
			LCD_SetBackColor(Red);
      LCD_SetTextColor(Red);
			Menu();
			while(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_10)==1)
			{		char ch[15] = "PRESS JOY STICK";
		      for (int j=0;j<15;j++)
			    {LCD_SetBackColor(White);
          LCD_SetTextColor(Black);
			    LCD_DisplayChar(214,16*(3+j)+8,ch[14-j]);}
	      	for (int j=0;j<15;j++)
			    {LCD_SetBackColor(White);
           LCD_SetTextColor(Red);
			     LCD_DisplayChar(214,16*(3+j)+8,ch[14-j]);}
					
				 }

		}
		if(ToDo==2)
    {
			LCD_Clear(Blue2);
		char ch[13] =  " Select mode " ;
		for (int j=0;j<13;j++)
		{LCD_SetBackColor(White);
      LCD_SetTextColor(Red);
			LCD_DisplayChar(Line1,16*(4+j),ch[12-j]);}
		
			LCD_SetBackColor(Yellow);
			LCD_SetTextColor(Yellow);
			LCD_DrawFullRect(2*40, 8*40, 320, 40);
		char ch2[13] = " Easy - Left ";
		for (int j=0;j<13;j++)
			{LCD_SetBackColor(Yellow);
      LCD_SetTextColor(Black);
			LCD_DisplayChar(90,16*(8+j),ch2[12-j]);}
			DrawBomb(2,3);
			Draw7(2,1);
			
			LCD_SetBackColor(Green2);
			LCD_SetTextColor(Green2);
			LCD_DrawFullRect(3*40, 8*40, 320, 40);
    char ch3[13] = " Medium - Up ";
		for (int j=0;j<13;j++)
			{LCD_SetBackColor(Green2);
      LCD_SetTextColor(Black);
			LCD_DisplayChar(130,16*(8+j),ch3[12-j]);}
			DrawBomb(3,3);
			Draw0(3,1);
			Draw1(3,2);
			
			LCD_SetBackColor(Red);
			LCD_SetTextColor(Red);
			LCD_DrawFullRect(4*40, 8*40, 320, 40);
    char ch4[13] = " Hard -Right ";
		for (int j=0;j<13;j++)
			{LCD_SetBackColor(Red);
      LCD_SetTextColor(White);
			LCD_DisplayChar(170,16*(8+j),ch4[12-j]);}
		DrawBomb(4,3);
			Draw5(4,1);
			Draw1(4,2);
		int level=0;
			
		while(1)
			{		
				
		if (HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12)==1&&HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_13)==0&&HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_14)==0)	
				{ level =1; 
				break;}
		else if (HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12)==0&&HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_13)==1&&HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_14)==0)	
				{ level =2; 
				break;}
		else if (HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12)==0&&HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_13)==0&&HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_14)==1)	
				{level =3;
				break;}
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_10)==1&&HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_9)==0)
			{	break;}
				
			}

		while(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_9)==0&&HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_10)==0)
			{			}
		
		if (HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_9)==1&&HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_8)==0)
		{
		 LCD_Clear(Blue2);
		 for (int i = 0; i<6; i++)
		 {
			for (int j=1; j<7; j++)
			{


				LCD_SetBackColor(Grey);
				LCD_SetTextColor(Grey2);
				LCD_DrawFullRect(i*40, j*40, 40, 40);
				LCD_SetBackColor(Grey2);
			  LCD_SetTextColor(Grey2);
		  	LCD_DrawFullFrame(i*40+1,j*40-1,38,38);
				LCD_SetBackColor(Grey);
				LCD_SetTextColor(Grey2);
				LCD_DrawFullRect(i*40+6, j*40-6, 28, 28);
			}
		 }
     DrawBomb(1,7);
		 LCD_SetBackColor(White);
		 LCD_SetTextColor(Blue3);
		 LCD_DrawFullRect(2*40, 8*40, 80, 40);
		 
		 if (level==1)
		 {Draw7(2,7);}
		 else if (level==2)
		 {Draw0(2,7);
		  Draw1(2,8);}
		 else if (level==3)
		 {Draw5(2,7);
		  Draw1(2,8);}
	  }
		
		
		
	 }
	}
	
	if((HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_8) == GPIO_PIN_RESET)&&(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_9) == GPIO_PIN_SET))
	{


		int x=0,y=0,ToDo=0;

		//                   get x,y,ToDo
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8)==GPIO_PIN_SET)
			x+=1;
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)==GPIO_PIN_SET)
			x+=2;
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)==GPIO_PIN_SET)
			x+=4;
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)==GPIO_PIN_SET)
			y+=1;
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12)==GPIO_PIN_SET)
			y+=2;
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_13)==GPIO_PIN_SET)
			y+=4;
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_10)==GPIO_PIN_SET)
			ToDo+=1;
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_11)==GPIO_PIN_SET)
			ToDo+=2;
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12)==GPIO_PIN_SET)
			ToDo+=4;
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_13)==GPIO_PIN_SET)
			ToDo+=8;
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_14)==GPIO_PIN_SET)
			ToDo+=16;
		
		int temp =0;
		temp = x ;
		x = y ;
		y = 5-temp + 1;
		// test
		/*
		ToDo = 14;
		x=0;
		y=2;
		*/
		
		//										play
		if(ToDo==0)
		{
			
		//Space normal		
				LCD_SetBackColor(Grey);
				LCD_SetTextColor(Grey2);
				LCD_DrawFullRect(x*40, y*40, 40, 40);
				LCD_SetBackColor(Grey2);
			  LCD_SetTextColor(Grey2);
		  	LCD_DrawFullFrame(x*40+1,y*40-1,38,38);
				LCD_SetBackColor(Grey);
				LCD_SetTextColor(Grey2);
				LCD_DrawFullRect(x*40+6, y*40-6, 28, 28);	

	 }
		else if(ToDo==1)
		{
			//DrawSpace
			LCD_SetBackColor(Grey3);
			LCD_SetTextColor(Grey2);
			LCD_DrawFullRect(x*40+4, y*40-4, 32, 32);


		}
		else if(ToDo==2)
		{
			LCD_SetBackColor(Grey3);
			LCD_SetTextColor(Grey2);
			LCD_DrawFullRect(x*40+4, y*40-4, 32, 32);
			Draw0(x, y);
		}
		else if(ToDo==3)
		{
			LCD_SetBackColor(Grey3);
			LCD_SetTextColor(Grey2);
			LCD_DrawFullRect(x*40+4, y*40-4, 32, 32);
			Draw1(x, y);
		}
		else if(ToDo==4)
		{
			LCD_SetBackColor(Grey3);
			LCD_SetTextColor(Grey2);
			LCD_DrawFullRect(x*40+4, y*40-4, 32, 32);
			Draw2(x, y);
		}
		else if(ToDo==5)
		{
			LCD_SetBackColor(Grey3);
			LCD_SetTextColor(Grey2);
			LCD_DrawFullRect(x*40+4, y*40-4, 32, 32);
			Draw3(x, y);
		}
		else if(ToDo==6)
		{
			LCD_SetBackColor(Grey3);
			LCD_SetTextColor(Grey2);
			LCD_DrawFullRect(x*40+4, y*40-4, 32, 32);
			Draw4(x, y);
		}
		else if(ToDo==7)
		{
			LCD_SetBackColor(Grey3);
			LCD_SetTextColor(Grey2);
			LCD_DrawFullRect(x*40+4, y*40-4, 32, 32);
			Draw5(x, y);
		}
		else if(ToDo==8)
		{
			LCD_SetBackColor(Grey3);
			LCD_SetTextColor(Grey2);
			LCD_DrawFullRect(x*40+4, y*40-4, 32, 32);
			Draw6(x, y);
		}
		else if(ToDo==9)
		{
			LCD_SetBackColor(Grey3);
			LCD_SetTextColor(Grey2);
			LCD_DrawFullRect(x*40+4, y*40-4, 32, 32);
			Draw7(x, y);
		}
		else if(ToDo==10)
		{
			LCD_SetBackColor(Grey3);
			LCD_SetTextColor(Grey2);
			LCD_DrawFullRect(x*40+4, y*40-4, 32, 32);
			Draw8(x, y);
		}
		else if(ToDo==11)
		{
			LCD_SetBackColor(Grey3);
			LCD_SetTextColor(Grey2);
			LCD_DrawFullRect(x*40+4, y*40-4, 32, 32);
			Draw9(x, y);
		}
		
		else if(ToDo==12)
		{
			//Draw target
			LCD_SetBackColor(Red);
			LCD_SetTextColor(Red);
			LCD_DrawFullFrame(x*40+1,y*40-1,38,38);

		}
		else if(ToDo==13)
		{
			//delete target
			LCD_SetBackColor(Grey2);
			LCD_SetTextColor(Grey2);
			LCD_DrawFullFrame(x*40+1,y*40-1,38,38);
		}
		else if(ToDo==14)
		{
			// Flag
			DrawFlag(x, y);

		}
		else if(ToDo==15)
		{
			//Draw Bomb
			LCD_SetBackColor(Grey3);
			LCD_SetTextColor(Grey2);
			LCD_DrawFullRect(x*40, y*40, 40, 40);
			DrawBomb(x,y);
		}
		else if(ToDo==16)
		{
			//drawBomb red
			LCD_SetBackColor(Red);
			LCD_SetTextColor(Grey2);
			LCD_DrawFullRect(x*40, y*40, 40, 40);
			DrawBomb(x,y);
		}
		else if(ToDo==30)
		{ /*
			//num flag
			
				LCD_SetBackColor(White);
				LCD_SetTextColor(Blue3);
				LCD_DrawFullRect(3*40, 8*40, 80, 40);
			
			int num=0;
			//print num
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8)==GPIO_PIN_SET)
			num+=1;
		  if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)==GPIO_PIN_SET)
			num+=2;
		  if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)==GPIO_PIN_SET)
			num+=4;
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)==GPIO_PIN_SET)
			num+=8;
			
			if (num/10==1)
			{
			  Draw1(3,8);
			}
			else 
			{ Draw0(3,8);}
			num%=10;
			if (num==0)
			{ Draw0(3,7);}
			else if (num==1)
			{ Draw1(3,7);}
			else if (num==2)
			{ Draw2(3,7);}
			else if (num==3)
			{ Draw3(3,7);}
			else if (num==4)
			{ Draw4(3,7);}
			else if (num==5)
			{ Draw5(3,7);}
			else if (num==6)
			{ Draw6(3,7);}
			else if (num==7)
			{ Draw7(3,7);}
			else if (num==8)
			{ Draw8(3,7);}
			else if (num==9)
			{ Draw9(3,7);}

			*/
		}


	}
	if((HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_8) == GPIO_PIN_SET)&&(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_9) == GPIO_PIN_RESET))
	{
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_10) == 1)
		{
			LCD_SetBackColor(Red);
				LCD_SetTextColor(White);
			LCD_DisplayStringLine(Line1,"        You Lose    ");
		  Lose();
			while((HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_8) == GPIO_PIN_SET)&&(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_9) == GPIO_PIN_RESET))
		{}
		}
		else if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_10) == 0)
		{
			LCD_SetBackColor(Green);
				LCD_SetTextColor(Black);
			LCD_DisplayStringLine(Line1,"        You Win     ");
		Win();
		}
		while((HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_8) == GPIO_PIN_SET)&&(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_9) == GPIO_PIN_RESET))
		{}
		
	}    
  /*char str[20];
	sprintf(str,"\r%02d",input);
	LCD_SetBackColor(White);
	LCD_SetTextColor(Black);
  LCD_DisplayStringLine(Line4,str);
  HAL_Delay(50);*/

   
	
	




  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV4;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6_5;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
  RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
  RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /**Configure the Systick interrupt time 
    */
  __HAL_RCC_PLLI2S_ENABLE();

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* SPI3 init function */
static void MX_SPI3_Init(void)
{

  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM1 init function */
static void MX_TIM1_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 6500-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 10000-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM2 init function */
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7200-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE3 PE4 PE8 PE9 
                           PE10 PE11 PE12 PE13 
                           PE14 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_8|GPIO_PIN_9 
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13 
                          |GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PE5 PE6 PE7 PE15 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA8 PA9 PA10 
                           PA11 PA12 PA13 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB11 PB13 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD11 PD12 PD13 PD14 
                           PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PC8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void DrawBomb(int x,int y)
{
	    int xb=(x*40)+5;
			int yb=(y*40)-5;
	

      LCD_SetBackColor(Black);
			LCD_SetTextColor(Black);
			LCD_DrawFullCircle((x+1)*40-20,y*40-20,10);
	
      LCD_SetBackColor(Black);
			LCD_SetTextColor(Black);
			LCD_DrawFullRect(xb+1, yb-13, 4, 4);
	    LCD_DrawFullRect(xb+13,yb-1 , 4, 4);
	    LCD_DrawFullRect(xb+25,yb-13, 4, 4);
		  LCD_DrawFullRect(xb+13, yb-26, 4, 4);
	
      DrawKite(xb+7, yb-23);
	    DrawKite(xb+7, yb-7);
	    DrawKite(xb+22, yb-23);
	    DrawKite(xb+22, yb-7);

	
	    LCD_SetBackColor(White);
			LCD_SetTextColor(Black);
			LCD_DrawFullCircle((x+1)*40-24,y*40-16,2);
	
}


void DrawKite(int x,int y)
{
	    LCD_SetBackColor(Black);
			LCD_SetTextColor(Black);
			LCD_DrawFullRect(x, y+1, 1, 1);
	    LCD_DrawFullRect(x, y+2, 1, 1);
	    LCD_DrawFullRect(x, y-1, 1, 1);
	    LCD_DrawFullRect(x, y-2, 1, 1);
	    LCD_DrawFullRect(x+1, y, 1, 1);
	    LCD_DrawFullRect(x+2, y, 1, 1);
	    LCD_DrawFullRect(x-1, y, 1, 1);
	    LCD_DrawFullRect(x-2, y, 1, 1);
	    LCD_DrawFullRect(x+1, y+1, 1, 1);
	    LCD_DrawFullRect(x+1, y-1, 1, 1);
	    LCD_DrawFullRect(x-1, y+1, 1, 1);
	    LCD_DrawFullRect(x-1, y-1, 1, 1);
}

void Draw0(int x,int y)
{
		  int xb=(x*40)+5;
			int yb=(y*40)-5;
	    LCD_SetBackColor(Pink);
			LCD_SetTextColor(Pink);
			LCD_DrawFullRect(xb+4, yb-7, 16, 4);
			LCD_DrawFullRect(xb+4, yb-7, 4, 22);
			LCD_DrawFullRect(xb+4, yb-19, 4, 22);
	    LCD_DrawFullRect(xb+22, yb-7, 16, 4);	
}
void Draw1(int x,int y)
{
	    int xb=(x*40)+5;
			int yb=(y*40)-5;
		  LCD_SetBackColor(Blue3);
			LCD_SetTextColor(Blue3);
			LCD_DrawFullRect(	xb+4,yb-8,9,4);
			LCD_DrawFullRect(xb+8,yb-13,4,15);
			LCD_DrawFullRect(xb+23, yb-8, 14, 4);

}
void Draw2(int x,int y)
{
		  int xb=(x*40)+5;
			int yb=(y*40)-5;
	    LCD_SetBackColor(Green);
			LCD_SetTextColor(Green);
			LCD_DrawFullRect(xb+4, yb-7, 16, 4);
			LCD_DrawFullRect(xb+4, yb-19, 4, 13);
			LCD_DrawFullRect(xb+13, yb-7, 16, 4);
			LCD_DrawFullRect(xb+13, yb-7, 4, 13);
	    LCD_DrawFullRect(xb+22, yb-7, 16, 4);
	    
}
void Draw3(int x,int y)
{
		  int xb=(x*40)+5;
			int yb=(y*40)-5;	
	    LCD_SetBackColor(Red);
			LCD_SetTextColor(Red);
	    LCD_DrawFullRect(xb+4, yb-7, 16, 4);
			LCD_DrawFullRect(xb+4, yb-19, 4, 22);
			LCD_DrawFullRect(xb+13, yb-7, 16, 4);
			LCD_DrawFullRect(xb+22, yb-7, 16, 4);

}
void Draw4(int x,int y)
{
		  int xb=(x*40)+5;
			int yb=(y*40)-5;
		  LCD_SetBackColor(Blue);
			LCD_SetTextColor(Blue);
			LCD_DrawFullRect(xb+4, yb-7, 4, 14);
			LCD_DrawFullRect(xb+4, yb-16, 4, 24);
			LCD_DrawFullRect(xb+14, yb-7, 16, 4);

}
void Draw5(int x,int y)
{
		  int xb=(x*40)+5;
			int yb=(y*40)-5;
		  LCD_SetBackColor(Magenta);
			LCD_SetTextColor(Magenta);
			LCD_DrawFullRect(xb+4, yb-7, 16, 4);
			LCD_DrawFullRect(xb+4, yb-7, 4, 13);
			LCD_DrawFullRect(xb+13, yb-7, 16, 4);
			LCD_DrawFullRect(xb+13, yb-19, 4, 13);
	    LCD_DrawFullRect(xb+22, yb-7, 16, 4);	
}
void Draw6(int x,int y)
{
		  int xb=(x*40)+5;
			int yb=(y*40)-5;	    
			LCD_SetBackColor(Cyan);
			LCD_SetTextColor(Cyan);
			LCD_DrawFullRect(xb+4, yb-7, 16, 4);
			LCD_DrawFullRect(xb+4, yb-7, 4, 22);
			LCD_DrawFullRect(xb+13, yb-7, 16, 4);
			LCD_DrawFullRect(xb+13, yb-19, 4, 13);
	    LCD_DrawFullRect(xb+22, yb-7, 16, 4);
}
void Draw7(int x,int y)
{
		  int xb=(x*40)+5;
			int yb=(y*40)-5;	   
			LCD_SetBackColor(Purple);
			LCD_SetTextColor(Purple);
			LCD_DrawFullRect(xb+4, yb-7, 16, 4);
			LCD_DrawFullRect(xb+4, yb-19, 4, 23);

}
void Draw8(int x,int y)
{
		  int xb=(x*40)+5;
			int yb=(y*40)-5;
			LCD_SetBackColor(Grey2);
			LCD_SetTextColor(Grey2);	
			LCD_DrawFullRect(xb+4, yb-7, 16, 4);
			LCD_DrawFullRect(xb+4, yb-7, 4, 22);
			LCD_DrawFullRect(xb+13, yb-7, 16, 4);
			LCD_DrawFullRect(xb+4, yb-19, 4, 22);
	    LCD_DrawFullRect(xb+22, yb-7, 16, 4);	
}

void Draw9(int x,int y)
{
		  int xb=(x*40)+5;
			int yb=(y*40)-5;	 
			LCD_SetBackColor(Orange);
			LCD_SetTextColor(Orange);		
			LCD_DrawFullRect(xb+4, yb-7, 16, 4);
			LCD_DrawFullRect(xb+4, yb-7, 4, 13);
			LCD_DrawFullRect(xb+13, yb-7, 16, 4);
			LCD_DrawFullRect(xb+4, yb-19, 4, 22);
	    LCD_DrawFullRect(xb+22, yb-7, 16, 4);	 
}

void DrawFlag(int x,int y)
{
		  int xb=(x*40)+5;
			int yb=(y*40)-5;	
	
      LCD_SetBackColor(Black);
	    LCD_SetTextColor(Black);
			LCD_DrawFullRect(xb+28, yb-6, 20, 2);
    	LCD_DrawFullRect(xb+26, yb-11, 14, 2);
	    LCD_DrawFullRect(xb+20, yb-19, 2, 5);
	
    	LCD_SetBackColor(Red);
	    LCD_SetTextColor(Red);
	    LCD_DrawFullRect(xb+3, yb-16, 6, 17);
	    LCD_DrawFullRect(xb+5, yb-13, 3, 13);
	    LCD_DrawFullRect(xb+8, yb-8, 5, 8);
	    LCD_DrawFullRect(xb+10, yb-5, 3, 4);

}

void Menu()
{ int x=30,y=330-20;
	//M
  LCD_DrawFullRect(x+10, y-10, 10, 50);
	int i = 0,j=0;
	while (10+i<=40&&20+j<=50)
	{
		LCD_SetBackColor(Red);
	  LCD_SetTextColor(Red);
	  LCD_DrawFullRect(x+10+i, y-10-j, 10,10);
		i++;
		j++;
	}
	i=0;
	j=0;
	while (x+50-i!=x+10&&y-40-j!=y-70)
	{
	LCD_DrawFullRect(x+40-i, y-40-j, 10, 10);
		i++;
		j++;
	}
	LCD_DrawFullRect(x+10, y-70, 10, 50);
	
	//I
	LCD_DrawFullRect(x+10, y-100, 30, 10);
	LCD_DrawFullRect(x+10, y-110, 10, 40);
	LCD_DrawFullRect(x+50, y-100, 30, 10);
	//N
	LCD_DrawFullRect(x+10, y-150, 10, 50);
	 i = 0,j=0;
	while (i!=40)
	{
		LCD_SetBackColor(Red);
	  LCD_SetTextColor(Red);
	  LCD_DrawFullRect(x+10+i, y-160-j, 10,10);
		i++;
		j++;
	}
	//LCD_DrawFullRect(x+10, y-160, 10, 20);
	//LCD_DrawFullRect(x+20, y-170, 10, 30);
	//LCD_DrawFullRect(x+40, y-180, 10, 20);
	LCD_DrawFullRect(x+10, y-200, 10, 50);
	//E
	LCD_DrawFullRect(x+10, y-220, 40, 10);
	LCD_DrawFullRect(x+10, y-220, 10, 50);
	LCD_DrawFullRect(x+30, y-220, 30, 10);
	LCD_DrawFullRect(x+50, y-220, 40, 10);
	
	
	y=310;
	//s
	LCD_DrawFullRect(x+70, y-10, 30, 10);
	LCD_DrawFullRect(x+70, y-10, 10, 30);
	LCD_DrawFullRect(x+90, y-10, 30, 10);
	LCD_DrawFullRect(x+90, y-30, 10, 40);
	LCD_DrawFullRect(x+120, y-10, 30, 10);
	
	//w
	LCD_DrawFullRect(x+70, y-50, 10, 60);
	LCD_DrawFullRect(x+120, y-50, 50, 10);
	LCD_DrawFullRect(x+100, y-70, 10, 30);
	LCD_DrawFullRect(x+70, y-90, 10, 60);
	
	//e
	LCD_DrawFullRect(x+70, y-110, 30, 10);
	LCD_DrawFullRect(x+70, y-110, 10, 60);
	LCD_DrawFullRect(x+90, y-110, 20, 10);
	LCD_DrawFullRect(x+120, y-110, 30, 10);
	
		//e
	LCD_DrawFullRect(x+70, y-150, 30, 10);
	LCD_DrawFullRect(x+70, y-150, 10, 60);
	LCD_DrawFullRect(x+90, y-150, 20, 10);
	LCD_DrawFullRect(x+120, y-150, 30, 10);
	
	//p
	LCD_DrawFullRect(x+70, y-190, 30, 10);
	LCD_DrawFullRect(x+70, y-190, 10, 60);
	LCD_DrawFullRect(x+70, y-210, 10, 40);
	LCD_DrawFullRect(x+100, y-190, 30, 10);
	
		//e
	LCD_DrawFullRect(x+70, y-230, 30, 10);
	LCD_DrawFullRect(x+70, y-230, 10, 60);
	LCD_DrawFullRect(x+90, y-230, 20, 10);
	LCD_DrawFullRect(x+120, y-230, 30, 10);
	
	//r
	LCD_DrawFullRect(x+70, y-270, 30, 10);
	LCD_DrawFullRect(x+70, y-270, 10, 60);
	LCD_DrawFullRect(x+70, y-290, 10, 40);
	LCD_DrawFullRect(x+100, y-270, 30, 10);
	LCD_DrawFullRect(x+110, y-280, 10, 10);
	for (int k=0; k<=10;k++)
	LCD_DrawFullRect(x+110+k, y-280-k, 10, 10);
	

	int xb=(1*40)+5+10;
	int yb=(1*40);	
	
	//Flag
  LCD_SetBackColor(Black);
	LCD_SetTextColor(Black);
	LCD_DrawFullRect(xb+28, yb-6, 20, 2);
  LCD_DrawFullRect(xb+26, yb-11, 14, 2);
	LCD_DrawFullRect(xb+20, yb-19, 2, 5);
	LCD_SetBackColor(Red);
	LCD_SetTextColor(Red);
	LCD_DrawFullRect(xb+3, yb-16, 6, 17);
	LCD_DrawFullRect(xb+5, yb-13, 3, 13);
	LCD_DrawFullRect(xb+8, yb-8, 5, 8);
	LCD_DrawFullRect(xb+10, yb-5, 3, 4);

	DrawBomb(0,8);
	DrawBomb(0,7);
	DrawBomb(0,6);
	DrawBomb(0,5);
	DrawBomb(0,4);
	DrawBomb(0,3);
	DrawBomb(0,2);
	DrawBomb(0,1);
	DrawBomb(4,1);
	DrawBomb(4,2);
	DrawBomb(4,3);
	DrawBomb(4,4);
	DrawBomb(4,5);
	DrawBomb(4,6);
	DrawBomb(4,7);
	DrawBomb(4,8);
	
		char ch[15] = "PRESS JOY STICK";
		for (int j=0;j<15;j++)
			{LCD_SetBackColor(White);
      LCD_SetTextColor(Black);
			LCD_DisplayChar(214,16*(3+j)+8,ch[14-j]);}

	DrawFlag(5,1);
	DrawFlag(5,8);
			
}

void Win()
{
	int x =20;
	int y =320;
	    LCD_SetBackColor(Yellow);
			LCD_SetTextColor(Yellow);
			LCD_DrawFullCircle(x+115,y-160,50);
	    LCD_DrawFullCircle(x+80,y-160,40);
		  LCD_SetBackColor(Red);//mouth
			LCD_SetTextColor(Red);
	 		LCD_DrawFullCircle(x+110,y-160,30);
	    LCD_SetBackColor(Yellow);
			LCD_SetTextColor(Yellow);
	    LCD_DrawFullCircle(x+100,y-160,30);
	    LCD_SetBackColor(Yellow);
			LCD_SetTextColor(Yellow);
	    LCD_DrawFullRect(x+100, y-120,80,20);
	    //eyes
		    LCD_SetBackColor(Black);
			LCD_SetTextColor(Black);
	    //LCD_DrawFullCircle(x+90,y-150,5);
	    //LCD_DrawFullCircle(x+90,y-170,5);
	    LCD_DrawFullRect(x+80, y-125,30,20);
			LCD_DrawFullRect(x+80, y-165,30,20);
			LCD_DrawFullRect(x+85, y-140,30,5);
	for(int k=0;k<15;k++)
	{
	    LCD_DrawFullCircle(x+82+k,y-125+k,2);
	    LCD_DrawFullCircle(x+82+k,y-195-k,2);		
  }		
	//nose
			  LCD_SetBackColor(Orange);
			LCD_SetTextColor(Orange);
	for(int k=0;k<18;k++)
	{
	    LCD_DrawFullCircle(x+117,y-150-k,1);	
  }	
	
	  //hair
			  LCD_SetBackColor(Black);
			LCD_SetTextColor(Black);
	    LCD_DrawFullCircle(x+50,y-160,10);
	for(int k=0;k<15;k++)
	{

	    LCD_DrawFullCircle(x+50+k*2,y-145+k*2,15-k);
	    LCD_DrawFullCircle(x+50+k*2,y-175-k*2,15-k);		
  }		
	//while(1)
	//{}
}

void Lose()
{
	int x =20;
	int y =320;
	    LCD_SetBackColor(Yellow);
			LCD_SetTextColor(Yellow);
			LCD_DrawFullCircle(x+115,y-160,50);
	    LCD_DrawFullCircle(x+80,y-160,40);
		  LCD_SetBackColor(Red);//mouth
			LCD_SetTextColor(Red);
	 		LCD_DrawFullCircle(x+140,y-160,30);
	    LCD_SetBackColor(Yellow);
			LCD_SetTextColor(Yellow);
	    LCD_DrawFullCircle(x+150,y-160,30);
	    LCD_SetBackColor(Yellow);
			LCD_SetTextColor(Yellow);
	   // LCD_DrawFullRect(x+160, y-120,80,20);
	    //eyes
		  LCD_SetBackColor(Black);
			LCD_SetTextColor(Black);
	    LCD_DrawFullCircle(x+90,y-140,2);
	    LCD_DrawFullCircle(x+90,y-180,2);
		for(int k=0;k<10;k++)
	{
	    LCD_DrawFullCircle(x+90+k,y-140+k,2);
		  LCD_DrawFullCircle(x+90-k,y-140-k,2);
		  LCD_DrawFullCircle(x+90+k,y-140-k,2);
		  LCD_DrawFullCircle(x+90-k,y-140+k,2);
      LCD_DrawFullCircle(x+90+k,y-180+k,2);		
		  LCD_DrawFullCircle(x+90-k,y-180-k,2);
		  LCD_DrawFullCircle(x+90+k,y-180-k,2);
		  LCD_DrawFullCircle(x+90-k,y-180+k,2);
  }	
	
	
	  //hair
			  LCD_SetBackColor(Black);
			LCD_SetTextColor(Black);
	    LCD_DrawFullCircle(x+50,y-160,10);
	for(int k=0;k<15;k++)
	{

	    LCD_DrawFullCircle(x+50+k*2,y-145+k*2,15-k);
	    LCD_DrawFullCircle(x+50+k*2,y-175-k*2,15-k);		
  }		
	//while(1)
	//{}
}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
