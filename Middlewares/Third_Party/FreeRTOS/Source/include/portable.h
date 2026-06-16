  

  

#ifndef PORTABLE_H
#define PORTABLE_H

  
#include "deprecated_definitions.h"

  
#ifndef portENTER_CRITICAL
	#include "portmacro.h"
#endif

#if portBYTE_ALIGNMENT == 32
	#define portBYTE_ALIGNMENT_MASK ( 0x001f )
#endif

#if portBYTE_ALIGNMENT == 16
	#define portBYTE_ALIGNMENT_MASK ( 0x000f )
#endif

#if portBYTE_ALIGNMENT == 8
	#define portBYTE_ALIGNMENT_MASK ( 0x0007 )
#endif

#if portBYTE_ALIGNMENT == 4
	#define portBYTE_ALIGNMENT_MASK	( 0x0003 )
#endif

#if portBYTE_ALIGNMENT == 2
	#define portBYTE_ALIGNMENT_MASK	( 0x0001 )
#endif

#if portBYTE_ALIGNMENT == 1
	#define portBYTE_ALIGNMENT_MASK	( 0x0000 )
#endif

#ifndef portBYTE_ALIGNMENT_MASK
	#error "Invalid portBYTE_ALIGNMENT definition"
#endif

#ifndef portNUM_CONFIGURABLE_REGIONS
	#define portNUM_CONFIGURABLE_REGIONS 1
#endif

#ifndef portHAS_STACK_OVERFLOW_CHECKING
	#define portHAS_STACK_OVERFLOW_CHECKING 0
#endif

#ifndef portARCH_NAME
	#define portARCH_NAME NULL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "mpu_wrappers.h"

  
#if( portUSING_MPU_WRAPPERS == 1 )
	#if( portHAS_STACK_OVERFLOW_CHECKING == 1 )
		StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, StackType_t *pxEndOfStack, TaskFunction_t pxCode, void *pvParameters, BaseType_t xRunPrivileged ) PRIVILEGED_FUNCTION;
	#else
		StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters, BaseType_t xRunPrivileged ) PRIVILEGED_FUNCTION;
	#endif
#else
	#if( portHAS_STACK_OVERFLOW_CHECKING == 1 )
		StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, StackType_t *pxEndOfStack, TaskFunction_t pxCode, void *pvParameters ) PRIVILEGED_FUNCTION;
	#else
		StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters ) PRIVILEGED_FUNCTION;
	#endif
#endif

  
typedef struct HeapRegion
{
	uint8_t *pucStartAddress;
	size_t xSizeInBytes;
} HeapRegion_t;

  
typedef struct xHeapStats
{
	size_t xAvailableHeapSpaceInBytes;		  
	size_t xSizeOfLargestFreeBlockInBytes; 	  
	size_t xSizeOfSmallestFreeBlockInBytes;   
	size_t xNumberOfFreeBlocks;				  
	size_t xMinimumEverFreeBytesRemaining;	  
	size_t xNumberOfSuccessfulAllocations;	  
	size_t xNumberOfSuccessfulFrees;		  
} HeapStats_t;

  
void vPortDefineHeapRegions( const HeapRegion_t * const pxHeapRegions ) PRIVILEGED_FUNCTION;

  
void vPortGetHeapStats( HeapStats_t *pxHeapStats );

  
void *pvPortMalloc( size_t xSize ) PRIVILEGED_FUNCTION;
void vPortFree( void *pv ) PRIVILEGED_FUNCTION;
void vPortInitialiseBlocks( void ) PRIVILEGED_FUNCTION;
size_t xPortGetFreeHeapSize( void ) PRIVILEGED_FUNCTION;
size_t xPortGetMinimumEverFreeHeapSize( void ) PRIVILEGED_FUNCTION;

  
BaseType_t xPortStartScheduler( void ) PRIVILEGED_FUNCTION;

  
void vPortEndScheduler( void ) PRIVILEGED_FUNCTION;

  
#if( portUSING_MPU_WRAPPERS == 1 )
	struct xMEMORY_REGION;
	void vPortStoreTaskMPUSettings( xMPU_SETTINGS *xMPUSettings, const struct xMEMORY_REGION * const xRegions, StackType_t *pxBottomOfStack, uint32_t ulStackDepth ) PRIVILEGED_FUNCTION;
#endif

#ifdef __cplusplus
}
#endif

#endif   

