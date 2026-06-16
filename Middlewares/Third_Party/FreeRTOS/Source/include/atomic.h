  

  

#ifndef ATOMIC_H
#define ATOMIC_H

#ifndef INC_FREERTOS_H
	#error "include FreeRTOS.h must appear in source files before include atomic.h"
#endif

  
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

  
#if defined( portSET_INTERRUPT_MASK_FROM_ISR )

	  
	#define ATOMIC_ENTER_CRITICAL()	 \
		UBaseType_t uxCriticalSectionType = portSET_INTERRUPT_MASK_FROM_ISR()

	#define ATOMIC_EXIT_CRITICAL()	  \
		portCLEAR_INTERRUPT_MASK_FROM_ISR( uxCriticalSectionType )

#else

	  
	#define ATOMIC_ENTER_CRITICAL()	 portENTER_CRITICAL()
	#define ATOMIC_EXIT_CRITICAL()	  portEXIT_CRITICAL()

#endif   

  
#ifndef portFORCE_INLINE
	#define portFORCE_INLINE
#endif

#define ATOMIC_COMPARE_AND_SWAP_SUCCESS	 0x1U		  
#define ATOMIC_COMPARE_AND_SWAP_FAILURE	 0x0U		  

  

  
static portFORCE_INLINE uint32_t Atomic_CompareAndSwap_u32( uint32_t volatile * pulDestination,
															uint32_t ulExchange,
															uint32_t ulComparand )
{
uint32_t ulReturnValue;

	ATOMIC_ENTER_CRITICAL();
	{
		if( *pulDestination == ulComparand )
		{
			*pulDestination = ulExchange;
			ulReturnValue = ATOMIC_COMPARE_AND_SWAP_SUCCESS;
		}
		else
		{
			ulReturnValue = ATOMIC_COMPARE_AND_SWAP_FAILURE;
		}
	}
	ATOMIC_EXIT_CRITICAL();

	return ulReturnValue;
}
  

  
static portFORCE_INLINE void * Atomic_SwapPointers_p32( void * volatile * ppvDestination,
														void * pvExchange )
{
void * pReturnValue;

	ATOMIC_ENTER_CRITICAL();
	{
		pReturnValue = *ppvDestination;
		*ppvDestination = pvExchange;
	}
	ATOMIC_EXIT_CRITICAL();

	return pReturnValue;
}
  

  
static portFORCE_INLINE uint32_t Atomic_CompareAndSwapPointers_p32( void * volatile * ppvDestination,
																	void * pvExchange,
																	void * pvComparand )
{
uint32_t ulReturnValue = ATOMIC_COMPARE_AND_SWAP_FAILURE;

	ATOMIC_ENTER_CRITICAL();
	{
		if( *ppvDestination == pvComparand )
		{
			*ppvDestination = pvExchange;
			ulReturnValue = ATOMIC_COMPARE_AND_SWAP_SUCCESS;
		}
	}
	ATOMIC_EXIT_CRITICAL();

	return ulReturnValue;
}


  

  
static portFORCE_INLINE uint32_t Atomic_Add_u32( uint32_t volatile * pulAddend,
												 uint32_t ulCount )
{
	uint32_t ulCurrent;

	ATOMIC_ENTER_CRITICAL();
	{
		ulCurrent = *pulAddend;
		*pulAddend += ulCount;
	}
	ATOMIC_EXIT_CRITICAL();

	return ulCurrent;
}
  

  
static portFORCE_INLINE uint32_t Atomic_Subtract_u32( uint32_t volatile * pulAddend,
													  uint32_t ulCount )
{
	uint32_t ulCurrent;

	ATOMIC_ENTER_CRITICAL();
	{
		ulCurrent = *pulAddend;
		*pulAddend -= ulCount;
	}
	ATOMIC_EXIT_CRITICAL();

	return ulCurrent;
}
  

  
static portFORCE_INLINE uint32_t Atomic_Increment_u32( uint32_t volatile * pulAddend )
{
uint32_t ulCurrent;

	ATOMIC_ENTER_CRITICAL();
	{
		ulCurrent = *pulAddend;
		*pulAddend += 1;
	}
	ATOMIC_EXIT_CRITICAL();

	return ulCurrent;
}
  

  
static portFORCE_INLINE uint32_t Atomic_Decrement_u32( uint32_t volatile * pulAddend )
{
uint32_t ulCurrent;

	ATOMIC_ENTER_CRITICAL();
	{
		ulCurrent = *pulAddend;
		*pulAddend -= 1;
	}
	ATOMIC_EXIT_CRITICAL();

	return ulCurrent;
}

  

  
static portFORCE_INLINE uint32_t Atomic_OR_u32( uint32_t volatile * pulDestination,
												uint32_t ulValue )
{
uint32_t ulCurrent;

	ATOMIC_ENTER_CRITICAL();
	{
		ulCurrent = *pulDestination;
		*pulDestination |= ulValue;
	}
	ATOMIC_EXIT_CRITICAL();

	return ulCurrent;
}
  

  
static portFORCE_INLINE uint32_t Atomic_AND_u32( uint32_t volatile * pulDestination,
												 uint32_t ulValue )
{
uint32_t ulCurrent;

	ATOMIC_ENTER_CRITICAL();
	{
		ulCurrent = *pulDestination;
		*pulDestination &= ulValue;
	}
	ATOMIC_EXIT_CRITICAL();

	return ulCurrent;
}
  

  
static portFORCE_INLINE uint32_t Atomic_NAND_u32( uint32_t volatile * pulDestination,
												  uint32_t ulValue )
{
uint32_t ulCurrent;

	ATOMIC_ENTER_CRITICAL();
	{
		ulCurrent = *pulDestination;
		*pulDestination = ~( ulCurrent & ulValue );
	}
	ATOMIC_EXIT_CRITICAL();

	return ulCurrent;
}
  

  
static portFORCE_INLINE uint32_t Atomic_XOR_u32( uint32_t volatile * pulDestination,
												 uint32_t ulValue )
{
uint32_t ulCurrent;

	ATOMIC_ENTER_CRITICAL();
	{
		ulCurrent = *pulDestination;
		*pulDestination ^= ulValue;
	}
	ATOMIC_EXIT_CRITICAL();

	return ulCurrent;
}

#ifdef __cplusplus
}
#endif

#endif   
