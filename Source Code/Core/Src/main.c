/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dwt_stm32_delay.h"
#include "stdbool.h"
#include "stdio.h"

long int global_poz_x_axis=0;
long int global_poz_y_axis=0;

bool pwm_mode=true;



long step_x_axis=0;
bool direction_x_axis=false;

long step_y_axis=0;
bool direction_y_axis=false;

#define CCW  1
#define CW  -1



#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
	#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch,FILE *f)
	#endif

	PUTCHAR_PROTOTYPE
	{
	    HAL_UART_Transmit(&huart1,(uint8_t*)&ch,1,100);

		return ch;

	}



	char board_id='1';

	char motor_id1='1';
	char motor_id2='2';


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

void send_set_step_dir_PWM_X_axis(uint32_t step , int dir , uint16_t speed);
void send_set_step_dir_PWM_Y_axis(uint32_t step , int dir , uint16_t speed);


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//-------- usart 1 var ------

uint8_t Rx_data[2],Rx_indx,Rx_Buffer[100],Transfer_flag;
int i=0;
char buffer[100];
int len;




void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	  uint8_t i;

		if(huart->Instance==USART1)
		{

			//putchar((uint8_t)Rx_data[0]);


				if(Rx_indx==0){ for(i=0 ; i<100 ; i++ )Rx_Buffer[i]=0;}


				if(Rx_data[0]!='*') //cr lf '\r' | '\n'
				{
				  Rx_Buffer[Rx_indx++]=Rx_data[0];
				}
				else
				{
				   Rx_indx=0;
				   Transfer_flag=1;




				   if( Rx_Buffer[0] == 'A' && Rx_Buffer[1] == board_id)
				   {

						   char mstep[6] ="0000";
						   char mspeed[6]="0000";

						   mspeed[0]=Rx_Buffer[7];
						   mspeed[1]=Rx_Buffer[8];
						   mspeed[2]=Rx_Buffer[9];
						   mspeed[3]=Rx_Buffer[10];

						   mstep[0]=Rx_Buffer[12];
						   mstep[1]=Rx_Buffer[13];
						   mstep[2]=Rx_Buffer[14];
						   mstep[3]=Rx_Buffer[15];

						   uint8_t mdir = (Rx_Buffer[5])-48;

						   printf("step=%d, speed=%d, dir:%d\n", atoi(mstep),atoi(mspeed) , mdir );



						   if( Rx_Buffer[3] == motor_id1 )
						   {
							   send_set_step_dir_PWM_X_axis(   atoi(mstep) ,  mdir  ,   atoi(mspeed)  );

						   }
						   else if( Rx_Buffer[3] == motor_id2 )
						   {
							   send_set_step_dir_PWM_Y_axis(   atoi(mstep) ,   mdir   ,   atoi(mspeed)  );

						   }

				    }
				    else if( Rx_Buffer[1] == 'S' && Rx_Buffer[2] == 'T' && Rx_Buffer[3] == 'P' )//STOP
				    {
				    	  printf("STOP MOTOR\n" );
				    	  ENABLE_M_1(1);//0 ENABLE, 1 DISABLE
				    	  ENABLE_M_2(1);//0 ENABLE, 1 DISABLE
				    	  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);//stop pulse ch y axis
				    	  HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);//stop pulse ch y axis
				    }
				    else if( Rx_Buffer[1] == 'S' && Rx_Buffer[2] == 'T' && Rx_Buffer[3] == 'P' )//STOP
					{
						  printf("STOP MOTOR\n" );
						  ENABLE_M_1(1);//0 ENABLE, 1 DISABLE
						  ENABLE_M_2(1);//0 ENABLE, 1 DISABLE
						  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);//stop pulse ch y axis
						  HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);//stop pulse ch y axis
					}
				    else if( Rx_Buffer[1] == 'S' && Rx_Buffer[2] == 'L' && Rx_Buffer[3] == 'P' )//SLEEP
					{
				    	uint8_t s = 48 - (Rx_Buffer[4]) ;

				    	SLEEP_1(s);
						SLEEP_2(s);
					}
				    else if( Rx_Buffer[1] == 'R' && Rx_Buffer[2] == 'P' && Rx_Buffer[3] == 'T' )//SLEEP
					{

				    	if(Rx_Buffer[4] == '1')
				    	{
				    		printf("position motor 1=<%d>\n",global_poz_x_axis);
				    	}
				    	if(Rx_Buffer[4] == '2')
						{
				    		printf("position motor 2=<%d>\n",global_poz_y_axis);
						}

					}
				    else if( Rx_Buffer[1] == 'Z' && Rx_Buffer[2] == 'R' && Rx_Buffer[3] == 'O' )//SLEEP
					{

						if(Rx_Buffer[4] == '1')
						{
							 global_poz_x_axis=0;
						}
						if(Rx_Buffer[4] == '2')
						{
							global_poz_y_axis=0;
						}

					}


				}
				HAL_UART_Receive_IT(&huart1,(uint8_t *)Rx_data,1);

		}

}



























//############################ delay mode ##################################################################################

void send_set_step_dir_DLY_x_axis(uint32_t step , int dir,uint16_t speed)
{

	if(dir==1)
	{
		//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
		SET_DIR_1(1);
	}
	else
	{
		SET_DIR_1(0);
		//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	}

	for(uint32_t i=0 ; i < step ; i++)
	{
		HAL_GPIO_TogglePin(TIM3_CH2_STEPOUT1_GPIO_Port , TIM3_CH2_STEPOUT1_Pin);
		//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

		DWT_Delay_us(speed);//200
		//HAL_Delay(1);

//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
//		DWT_Delay_us(1);


	}

}

void send_set_step_dir_DLY_y_axis(uint32_t step , int dir,uint16_t speed)
{

	if(dir==1)
	{
		//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
		SET_DIR_2(1);
	}
	else
	{
		SET_DIR_2(0);
		//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	}

	for(uint32_t i=0 ; i < step ; i++)
	{
		HAL_GPIO_TogglePin(TIM2_CH2_STEPOUT2_GPIO_Port , TIM2_CH2_STEPOUT2_Pin);
		//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

		DWT_Delay_us(speed);//200
		//HAL_Delay(1);

//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
//		DWT_Delay_us(1);


	}

}

//########################## pwm mode ####################################################################################
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{


    if(htim->Instance==TIM3)//interrupt with every pulse for y ch--------------------------------------------------------------------
	{


				    if(direction_x_axis )
					{
				    	step_x_axis--;
				    	global_poz_x_axis--;
				    	if( step_x_axis<=0)//50000 --->>>  step_x_axis = s_value_x_p
						{
						   HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);//stop pulse ch y axis
						}

					}
				    else
					{

				    	step_x_axis++;
				    	global_poz_x_axis++;
				    	if( step_x_axis>=0)//50000 --->>>  step_x_axis = s_value_x_p
						{
						   HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);//stop pulse ch y axis
						}
					}


	}

    if(htim->Instance==TIM2)//interrupt with every pulse for y ch--------------------------------------------------------------------
	{


			if(direction_y_axis )
			{
				step_y_axis--;
				global_poz_y_axis--;
				if( step_y_axis<=0)//50000 --->>>  step_x_axis = s_value_x_p
				{
				   HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);//stop pulse ch y axis
				}
			}
			else
			{
				step_y_axis++;
				global_poz_y_axis++;
				if( step_y_axis>=0)//50000 --->>>  step_x_axis = s_value_x_p
				{
				   HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);//stop pulse ch y axis
				}
			}



	}





}
//----------------------------------------------
//##########################################################################################
//##########################################################################################
//##########################################################################################


void send_set_step_dir_PWM_X_axis(uint32_t step , int dir , uint16_t speed)
{

	ENABLE_M_1(0);//0 ENABLE, 1 DISABLE

	if(dir==0)
	{
		 direction_x_axis = true;
		 SET_DIR_1(1);
		 step_x_axis = step;
		//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	}
	else
	{
		step_x_axis = step *(-1);
		direction_x_axis=false;
		SET_DIR_1(0);
		//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	}


	//step_x_axis = step;


	htim3.Instance = TIM3;
	htim3.Init.Prescaler = speed-1 ; // 3-1
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 100;// speed-1
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(&htim3) ;

	 HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,50);// 40




}

void send_set_step_dir_PWM_Y_axis(uint32_t step , int dir , uint16_t speed)
{

	ENABLE_M_2(0);//0 ENABLE, 1 DISABLE

	if(dir==0)
	{
		direction_y_axis=true;
		 SET_DIR_2(1);
		 step_y_axis = step;
		//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	}
	else
	{
		step_y_axis = step *(-1);
		direction_y_axis=false;
		SET_DIR_2(0);
		//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	}





	htim2.Instance = TIM2;
	htim2.Init.Prescaler = speed-1 ; // 3-1
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 100;// speed-1
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(&htim2) ;

	 HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,50);// 40




}

//##############################################################################################################




void  get_dip_sw_setting()
{

	  if(!READ_SW2)
	  {
		  board_id='1';
	  }
	  else
	  {
		  board_id='2';
	  }



}





/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */




  HAL_UART_Receive_IT(&huart1,(uint8_t *)Rx_data,1);


  if(!pwm_mode)
  {
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Pin = TIM3_CH2_STEPOUT1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(TIM3_CH2_STEPOUT1_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = TIM2_CH2_STEPOUT2_Pin ;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(TIM2_CH2_STEPOUT2_GPIO_Port, &GPIO_InitStruct);
  }








  DWT_Delay_Init();

  uint16_t speed=600;


  ENABLE_M_1(0);//0 ENABLE, 1 DISABLE
  ENABLE_M_2(0);//0 ENABLE, 1 DISABLE



 printf("============system started============\n");


 get_dip_sw_setting();


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {

	  get_dip_sw_setting();

	 // printf("============\n");

	  LED_TGL;


	  HAL_Delay(700);


  if(!READ_SW1)
  {

		   if(!pwm_mode)
		   {
				send_set_step_dir_DLY_x_axis(1000  , CCW  , speed);
				send_set_step_dir_DLY_y_axis(1000  , CCW  , speed);
				HAL_Delay(2000);
				send_set_step_dir_DLY_x_axis(1000  , CW  , speed);
				send_set_step_dir_DLY_y_axis(1000  , CW  , speed);
				HAL_Delay(2000);
		   }
		   else
		   {
			   send_set_step_dir_PWM_X_axis(1000  , CCW , speed);
			   send_set_step_dir_PWM_Y_axis(1000  , CCW , speed);
			   HAL_Delay(2000);
			   send_set_step_dir_PWM_X_axis(1000  ,  CW , speed);
			   send_set_step_dir_PWM_Y_axis(1000  ,  CW , speed);
			   HAL_Delay(2000);
		   }

		   speed+=50;

  }




    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
