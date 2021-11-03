#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <math.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

static void RecibirCola( void * pvParameters );
static void EnviarCola( void * pvParameters );
static void AccionImportante( void * pvParameters );
static void MoveForward(uint32_t n);

/* cola */
static QueueHandle_t xQueue = NULL;

/* contador */
static uint32_t cnt;

void ppal( void ){
  /* crear cola */
  xQueue = xQueueCreate( 2, sizeof( uint32_t ) );

  /* contador */
  cnt=0;

  if( xQueue != NULL ){
    /* tres tareas */
    xTaskCreate( RecibirCola,
                 "RX",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 tskIDLE_PRIORITY + 3,
                 NULL );

    xTaskCreate( EnviarCola,
                 "TX",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 tskIDLE_PRIORITY + 2,
                 NULL );

    xTaskCreate( AccionImportante,
                 "Action",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 tskIDLE_PRIORITY + 1,
                 NULL );

    /* arrancamos scheduler */
    vTaskStartScheduler();
  }

  for( ; ; ){
  }
}

static void EnviarCola( void * pvParameters ){
  TickType_t xNextWakeTime;

  xNextWakeTime = xTaskGetTickCount();

  for( ; ; ){
    vTaskDelayUntil( &xNextWakeTime, pdMS_TO_TICKS( 200UL ) );
    xQueueSend( xQueue, &cnt, 0U );

    cnt++;
  }
}

static void RecibirCola( void * pvParameters ){
  uint32_t val;

  for( ; ; ){
    xQueueReceive( xQueue, &val, portMAX_DELAY );

    MoveForward((uint32_t)(40+35*sin((double)cnt/6)));
    printf("*\n",val);
  }
}

static void AccionImportante( void * pvParameters ){
  while(1){
    printf("[Action here!]\r");
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

static void MoveForward(uint32_t n){
  printf("\033[%uC",n);
}
