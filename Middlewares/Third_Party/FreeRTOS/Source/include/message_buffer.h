  


  

#ifndef FREERTOS_MESSAGE_BUFFER_H
#define FREERTOS_MESSAGE_BUFFER_H

#ifndef INC_FREERTOS_H
	#error "include FreeRTOS.h must appear in source files before include message_buffer.h"
#endif

  
#include "stream_buffer.h"

#if defined( __cplusplus )
extern "C" {
#endif

  
typedef void * MessageBufferHandle_t;

  

  
#define xMessageBufferCreate( xBufferSizeBytes ) ( MessageBufferHandle_t ) xStreamBufferGenericCreate( xBufferSizeBytes, ( size_t ) 0, pdTRUE )

  
#define xMessageBufferCreateStatic( xBufferSizeBytes, pucMessageBufferStorageArea, pxStaticMessageBuffer ) ( MessageBufferHandle_t ) xStreamBufferGenericCreateStatic( xBufferSizeBytes, 0, pdTRUE, pucMessageBufferStorageArea, pxStaticMessageBuffer )

  
#define xMessageBufferSend( xMessageBuffer, pvTxData, xDataLengthBytes, xTicksToWait ) xStreamBufferSend( ( StreamBufferHandle_t ) xMessageBuffer, pvTxData, xDataLengthBytes, xTicksToWait )

  
#define xMessageBufferSendFromISR( xMessageBuffer, pvTxData, xDataLengthBytes, pxHigherPriorityTaskWoken ) xStreamBufferSendFromISR( ( StreamBufferHandle_t ) xMessageBuffer, pvTxData, xDataLengthBytes, pxHigherPriorityTaskWoken )

  
#define xMessageBufferReceive( xMessageBuffer, pvRxData, xBufferLengthBytes, xTicksToWait ) xStreamBufferReceive( ( StreamBufferHandle_t ) xMessageBuffer, pvRxData, xBufferLengthBytes, xTicksToWait )


  
#define xMessageBufferReceiveFromISR( xMessageBuffer, pvRxData, xBufferLengthBytes, pxHigherPriorityTaskWoken ) xStreamBufferReceiveFromISR( ( StreamBufferHandle_t ) xMessageBuffer, pvRxData, xBufferLengthBytes, pxHigherPriorityTaskWoken )

  
#define vMessageBufferDelete( xMessageBuffer ) vStreamBufferDelete( ( StreamBufferHandle_t ) xMessageBuffer )

  
#define xMessageBufferIsFull( xMessageBuffer ) xStreamBufferIsFull( ( StreamBufferHandle_t ) xMessageBuffer )

  
#define xMessageBufferIsEmpty( xMessageBuffer ) xStreamBufferIsEmpty( ( StreamBufferHandle_t ) xMessageBuffer )

  
#define xMessageBufferReset( xMessageBuffer ) xStreamBufferReset( ( StreamBufferHandle_t ) xMessageBuffer )


  
#define xMessageBufferSpaceAvailable( xMessageBuffer ) xStreamBufferSpacesAvailable( ( StreamBufferHandle_t ) xMessageBuffer )
#define xMessageBufferSpacesAvailable( xMessageBuffer ) xStreamBufferSpacesAvailable( ( StreamBufferHandle_t ) xMessageBuffer )   

  
#define xMessageBufferNextLengthBytes( xMessageBuffer ) xStreamBufferNextMessageLengthBytes( ( StreamBufferHandle_t ) xMessageBuffer ) PRIVILEGED_FUNCTION;

  
#define xMessageBufferSendCompletedFromISR( xMessageBuffer, pxHigherPriorityTaskWoken ) xStreamBufferSendCompletedFromISR( ( StreamBufferHandle_t ) xMessageBuffer, pxHigherPriorityTaskWoken )

  
#define xMessageBufferReceiveCompletedFromISR( xMessageBuffer, pxHigherPriorityTaskWoken ) xStreamBufferReceiveCompletedFromISR( ( StreamBufferHandle_t ) xMessageBuffer, pxHigherPriorityTaskWoken )

#if defined( __cplusplus )
}   
#endif

#endif	  
