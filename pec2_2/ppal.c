#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

typedef enum {NUM,OP,OPAR,CPAR} statetype;

static void RecibirCola( void * pvParameters );
static void EnviarCola( void * pvParameters );
static void UpdateFSM( void * pvParameters );
static void MoveForward(uint32_t n);
static double genrandomd(void);
static int genrandomi(void);

/* cola */
static QueueHandle_t xQueue = NULL;

/* contador */
static uint32_t cnt;

/* estado */
static statetype state=NUM;

/* parentesis */
static uint32_t npars=0;

/* finished */
static uint32_t finished=0;

void ppal( void ){
  FILE *fid;

  /* crear cola */
  xQueue = xQueueCreate( 2, sizeof( uint32_t ) );

  /* reiniciar generador de numeros aleatorios */
  srand(time(NULL));

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

    xTaskCreate( UpdateFSM,
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

static void MoveForward(uint32_t n){
  printf("\033[%uC",n);
}

static void UpdateFSM( void * pvParameters ){
  FILE *fid;

  while(1){
    fid=fopen("output.txt","a");

    double r;

    switch(state){
    case NUM:
      fprintf(fid,"%d",genrandomi());

      if(npars==0){
        state=OP;
      }else{
        if(genrandomd()<.7){
          state=OP;
        }else{
          state=CPAR;
        }
      }

      break;
    case OP:
      r=genrandomd();

      if(r<.5){
        if(r<.25){
          fprintf(fid,"+");
        }else{
          fprintf(fid,"-");
        }
      }else{
        if(r<.75){
          fprintf(fid,"*");
        }else{
          fprintf(fid,"/");
        }
      }

      if(genrandomd()<.7){
        state=NUM;
      }else{
        state=OPAR;
      }

      break;
    case OPAR:
      npars++;
      fprintf(fid,"(");

      if(genrandomd()<.8){
        state=NUM;
      }else{
        state=OPAR;
      }

      break;
    case CPAR:
      npars--;
      fprintf(fid,")");

      if(npars==0){
        state=OP;
      }else{
        if(genrandomd()<.8){
          state=OP;
        }else{
          state=CPAR;
        }
      }

      break;
    }

    fclose(fid);

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static double genrandomd(void){
  return (double)rand()/RAND_MAX;
}

static int genrandomi(void){
  return (int)20*genrandomd();
}
