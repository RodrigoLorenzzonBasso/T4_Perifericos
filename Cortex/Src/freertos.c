/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

#include "gpio.h"
#include "usart.h"

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
/* USER CODE BEGIN Variables */

struct Control{
	
	float temp;
	float umid;
	
	unsigned char conectado;
	
	char str[50];
	
}c;

/* USER CODE END Variables */
osThreadId PrintaDisplayHandle;
osThreadId MonitoraTouchHandle;
osSemaphoreId sensoresHandle;
osSemaphoreId touchHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//osThreadResume(myTask02Handle); //desbloqueia a TASK2
	//osSemaphoreRelease(myBinarySem01Handle); // Libera o Semaforo 1
}

/* USER CODE END FunctionPrototypes */

void StartPrintaDisplay(void const * argument);
void StartMonitoraTouch(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	
	c.temp = 0.0;
	c.umid = 0.0;
	c.conectado = 0;
	
	// inicializa uart
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of sensores */
  osSemaphoreDef(sensores);
  sensoresHandle = osSemaphoreCreate(osSemaphore(sensores), 1);

  /* definition and creation of touch */
  osSemaphoreDef(touch);
  touchHandle = osSemaphoreCreate(osSemaphore(touch), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of PrintaDisplay */
  osThreadDef(PrintaDisplay, StartPrintaDisplay, osPriorityNormal, 0, 128);
  PrintaDisplayHandle = osThreadCreate(osThread(PrintaDisplay), NULL);

  /* definition and creation of MonitoraTouch */
  osThreadDef(MonitoraTouch, StartMonitoraTouch, osPriorityNormal, 0, 128);
  MonitoraTouchHandle = osThreadCreate(osThread(MonitoraTouch), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  //osThreadSuspend(myTask02Handle);//suspender para não executar a primeira vez
	//osThreadSuspend(myTask03Handle);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* USER CODE BEGIN Header_StartPrintaDisplay */
/**
  * @brief  Function implementing the PrintaDisplay thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartPrintaDisplay */
void StartPrintaDisplay(void const * argument)
{

  /* USER CODE BEGIN StartPrintaDisplay */
  /* Infinite loop */
  for(;;)
  {
		osSemaphoreWait(sensoresHandle, osWaitForever);
		int temperatura = c.temp;
		int umidade = c.umid;
		unsigned char conectado = c.conectado;
		osSemaphoreRelease(sensoresHandle);
		
		// DESENHA A TELA DO DISPLAY
		
    osDelay(1);
  }
  /* USER CODE END StartPrintaDisplay */
}

/* USER CODE BEGIN Header_StartMonitoraTouch */
/**
* @brief Function implementing the MonitoraTouch thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMonitoraTouch */
void StartMonitoraTouch(void const * argument)
{
  /* USER CODE BEGIN StartMonitoraTouch */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartMonitoraTouch */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
