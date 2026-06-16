  

#ifndef FREERTOS_OS2_H_
#define FREERTOS_OS2_H_

#include <string.h>
#include <stdint.h>

#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core

#include CMSIS_device_header

  

  
#ifndef configUSE_OS2_THREAD_SUSPEND_RESUME
#define configUSE_OS2_THREAD_SUSPEND_RESUME   1
#endif

  
#ifndef configUSE_OS2_THREAD_ENUMERATE
#define configUSE_OS2_THREAD_ENUMERATE        1
#endif

  
#ifndef configUSE_OS2_EVENTFLAGS_FROM_ISR
#define configUSE_OS2_EVENTFLAGS_FROM_ISR     1
#endif

  
#ifndef configUSE_OS2_THREAD_FLAGS
#define configUSE_OS2_THREAD_FLAGS            configUSE_TASK_NOTIFICATIONS
#endif

  
#ifndef configUSE_OS2_TIMER
#define configUSE_OS2_TIMER                   configUSE_TIMERS
#endif

  
#ifndef configUSE_OS2_MUTEX
#define configUSE_OS2_MUTEX                   configUSE_MUTEXES
#endif


  
#if (INCLUDE_xSemaphoreGetMutexHolder == 0)
    
  #error "Definition INCLUDE_xSemaphoreGetMutexHolder must equal 1 to implement Mutex Management API."
#endif
#if (INCLUDE_vTaskDelay == 0)
    
  #error "Definition INCLUDE_vTaskDelay must equal 1 to implement Generic Wait Functions API."
#endif
#if (INCLUDE_vTaskDelayUntil == 0)
    
  #error "Definition INCLUDE_vTaskDelayUntil must equal 1 to implement Generic Wait Functions API."
#endif
#if (INCLUDE_vTaskDelete == 0)
    
  #error "Definition INCLUDE_vTaskDelete must equal 1 to implement Thread Management API."
#endif
#if (INCLUDE_xTaskGetCurrentTaskHandle == 0)
    
  #error "Definition INCLUDE_xTaskGetCurrentTaskHandle must equal 1 to implement Thread Management API."
#endif
#if (INCLUDE_xTaskGetSchedulerState == 0)
    
  #error "Definition INCLUDE_xTaskGetSchedulerState must equal 1 to implement Kernel Information and Control API."
#endif
#if (INCLUDE_uxTaskGetStackHighWaterMark == 0)
    
  #error "Definition INCLUDE_uxTaskGetStackHighWaterMark must equal 1 to implement Thread Management API."
#endif
#if (INCLUDE_uxTaskPriorityGet == 0)
    
  #error "Definition INCLUDE_uxTaskPriorityGet must equal 1 to implement Thread Management API."
#endif
#if (INCLUDE_vTaskPrioritySet == 0)
    
  #error "Definition INCLUDE_vTaskPrioritySet must equal 1 to implement Thread Management API."
#endif
#if (INCLUDE_eTaskGetState == 0)
    
  #error "Definition INCLUDE_eTaskGetState must equal 1 to implement Thread Management API."
#endif
#if (INCLUDE_vTaskSuspend == 0)
    
  #if (configUSE_OS2_THREAD_SUSPEND_RESUME == 1)
    #error "Definition INCLUDE_vTaskSuspend must equal 1 to implement Kernel Information and Control API."
  #endif
#endif
#if (INCLUDE_xTimerPendFunctionCall == 0)
    
  #if (configUSE_OS2_EVENTFLAGS_FROM_ISR == 1)
    #error "Definition INCLUDE_xTimerPendFunctionCall must equal 1 to implement Event Flags API."
  #endif
#endif

#if (configUSE_TIMERS == 0)
    
  #if (configUSE_OS2_TIMER == 1)
    #error "Definition configUSE_TIMERS must equal 1 to implement Timer Management API."
  #endif
#endif

#if (configUSE_MUTEXES == 0)
    
  #if (configUSE_OS2_MUTEX == 1)
    #error "Definition configUSE_MUTEXES must equal 1 to implement Mutex Management API."
  #endif
#endif

#if (configUSE_COUNTING_SEMAPHORES == 0)
    
  #error "Definition configUSE_COUNTING_SEMAPHORES must equal 1 to implement Memory Pool API."
#endif
#if (configUSE_TASK_NOTIFICATIONS == 0)
    
  #if (configUSE_OS2_THREAD_FLAGS == 1)
    #error "Definition configUSE_TASK_NOTIFICATIONS must equal 1 to implement Thread Flags API."
  #endif
#endif

#if (configUSE_TRACE_FACILITY == 0)
    
  #if (configUSE_OS2_THREAD_ENUMERATE == 1)
    #error "Definition configUSE_TRACE_FACILITY must equal 1 to implement osThreadEnumerate."
  #endif
#endif

#if (configUSE_16_BIT_TICKS == 1)
    
  #error "Definition configUSE_16_BIT_TICKS must be zero to implement CMSIS-RTOS2 API."
#endif

#if (configMAX_PRIORITIES != 56)
    
  #error "Definition configMAX_PRIORITIES must equal 56 to implement Thread Management API."
#endif
#if (configUSE_PORT_OPTIMISED_TASK_SELECTION != 0)
    
  #error "Definition configUSE_PORT_OPTIMISED_TASK_SELECTION must be zero to implement Thread Management API."
#endif

#endif   
