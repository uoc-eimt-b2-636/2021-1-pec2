#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>
#include <sys/select.h>

#include "FreeRTOS.h"
#include "task.h"

extern void ppal( void );

void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask,
                                    char * pcTaskName );
void vApplicationTickHook( void );
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize );
void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize );

StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

/* ============================================================ */
/* ============================================================ */
/* ============================================================ */
/* ============================================================ */

int main( void )
{
  printf("PEC2\n");
  printf("B2.636\n");
  printf("Diseno de sistemas ciberfisicos\n");
  printf("==============================\n\n");

  ppal();

  return 0;
}

/* ============================================================ */
/* ============================================================ */
/* ============================================================ */
/* ============================================================ */

void vApplicationMallocFailedHook( void )
{
  vAssertCalled( __FILE__, __LINE__ );
}

void vApplicationIdleHook( void )
{
  usleep( 15000 );
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask,
                                    char * pcTaskName )
{
  vAssertCalled( __FILE__, __LINE__ );
}

void vApplicationTickHook( void )
{
  /* nothing */
}

void vApplicationDaemonTaskStartupHook( void )
{
  /* nothing */
}

void vAssertCalled( const char * const pcFileName,
                    unsigned long ulLine )
{
  /* nothing */
}

void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
  static StaticTask_t xIdleTaskTCB;
  static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

  *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
  *ppxIdleTaskStackBuffer = uxIdleTaskStack;
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize )
{
  static StaticTask_t xTimerTaskTCB;

  *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
  *ppxTimerTaskStackBuffer = uxTimerTaskStack;
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
