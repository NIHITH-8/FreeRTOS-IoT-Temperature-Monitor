  

  

#ifndef STREAM_BUFFER_H
#define STREAM_BUFFER_H

#ifndef INC_FREERTOS_H
	#error "include FreeRTOS.h must appear in source files before include stream_buffer.h"
#endif

#if defined( __cplusplus )
extern "C" {
#endif

  
struct StreamBufferDef_t;
typedef struct StreamBufferDef_t * StreamBufferHandle_t;


  
#define xStreamBufferCreate( xBufferSizeBytes, xTriggerLevelBytes ) xStreamBufferGenericCreate( xBufferSizeBytes, xTriggerLevelBytes, pdFALSE )

  
#define xStreamBufferCreateStatic( xBufferSizeBytes, xTriggerLevelBytes, pucStreamBufferStorageArea, pxStaticStreamBuffer ) xStreamBufferGenericCreateStatic( xBufferSizeBytes, xTriggerLevelBytes, pdFALSE, pucStreamBufferStorageArea, pxStaticStreamBuffer )

  
size_t xStreamBufferSend( StreamBufferHandle_t xStreamBuffer,
						  const void *pvTxData,
						  size_t xDataLengthBytes,
						  TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

  
size_t xStreamBufferSendFromISR( StreamBufferHandle_t xStreamBuffer,
								 const void *pvTxData,
								 size_t xDataLengthBytes,
								 BaseType_t * const pxHigherPriorityTaskWoken ) PRIVILEGED_FUNCTION;

  
size_t xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
							 void *pvRxData,
							 size_t xBufferLengthBytes,
							 TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

  
size_t xStreamBufferReceiveFromISR( StreamBufferHandle_t xStreamBuffer,
									void *pvRxData,
									size_t xBufferLengthBytes,
									BaseType_t * const pxHigherPriorityTaskWoken ) PRIVILEGED_FUNCTION;

  
void vStreamBufferDelete( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

  
BaseType_t xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

  
BaseType_t xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

  
BaseType_t xStreamBufferReset( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

  
size_t xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

  
size_t xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

  
BaseType_t xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer, size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

  
BaseType_t xStreamBufferSendCompletedFromISR( StreamBufferHandle_t xStreamBuffer, BaseType_t *pxHigherPriorityTaskWoken ) PRIVILEGED_FUNCTION;

  
BaseType_t xStreamBufferReceiveCompletedFromISR( StreamBufferHandle_t xStreamBuffer, BaseType_t *pxHigherPriorityTaskWoken ) PRIVILEGED_FUNCTION;

  
StreamBufferHandle_t xStreamBufferGenericCreate( size_t xBufferSizeBytes,
												 size_t xTriggerLevelBytes,
												 BaseType_t xIsMessageBuffer ) PRIVILEGED_FUNCTION;

StreamBufferHandle_t xStreamBufferGenericCreateStatic( size_t xBufferSizeBytes,
													   size_t xTriggerLevelBytes,
													   BaseType_t xIsMessageBuffer,
													   uint8_t * const pucStreamBufferStorageArea,
													   StaticStreamBuffer_t * const pxStaticStreamBuffer ) PRIVILEGED_FUNCTION;

size_t xStreamBufferNextMessageLengthBytes( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

#if( configUSE_TRACE_FACILITY == 1 )
	void vStreamBufferSetStreamBufferNumber( StreamBufferHandle_t xStreamBuffer, UBaseType_t uxStreamBufferNumber ) PRIVILEGED_FUNCTION;
	UBaseType_t uxStreamBufferGetStreamBufferNumber( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;
	uint8_t ucStreamBufferGetStreamBufferType( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;
#endif

#if defined( __cplusplus )
}
#endif

#endif	  
