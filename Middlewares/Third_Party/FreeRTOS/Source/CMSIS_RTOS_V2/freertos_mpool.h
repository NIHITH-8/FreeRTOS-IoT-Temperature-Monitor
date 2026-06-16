  

#ifndef FREERTOS_MPOOL_H_
#define FREERTOS_MPOOL_H_

#include <stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"

  
#define MPOOL_STATUS              0x5EED0000U

  
typedef struct {
  void *next;                     
} MemPoolBlock_t;

  
typedef struct MemPoolDef_t {
  MemPoolBlock_t    *head;        
  SemaphoreHandle_t  sem;         
  uint8_t           *mem_arr;     
  uint32_t           mem_sz;      
  const char        *name;        
  uint32_t           bl_sz;       
  uint32_t           bl_cnt;      
  uint32_t           n;           
  volatile uint32_t  status;      
#if (configSUPPORT_STATIC_ALLOCATION == 1)
  StaticSemaphore_t  mem_sem;     
#endif
} MemPool_t;

  
#define StaticMemPool_t         MemPool_t

  
#define MEMPOOL_CB_SIZE         (sizeof(StaticMemPool_t))

  
#define MEMPOOL_ARR_SIZE(bl_count, bl_size) (((((bl_size) + (4 - 1)) / 4) * 4)*(bl_count))

#endif   
