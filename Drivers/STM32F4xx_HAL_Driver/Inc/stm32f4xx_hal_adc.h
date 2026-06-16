  

  
#ifndef __STM32F4xx_ADC_H
#define __STM32F4xx_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

  
#include "stm32f4xx_hal_def.h"

  
#include "stm32f4xx_ll_adc.h"

  

  

  
  

  
typedef struct
{
  uint32_t ClockPrescaler;                 
  uint32_t Resolution;                     
  uint32_t DataAlign;                      
  uint32_t ScanConvMode;                   
  uint32_t EOCSelection;                   
  FunctionalState ContinuousConvMode;      
  uint32_t NbrOfConversion;                
  FunctionalState DiscontinuousConvMode;   
  uint32_t NbrOfDiscConversion;            
  uint32_t ExternalTrigConv;               
  uint32_t ExternalTrigConvEdge;           
  FunctionalState DMAContinuousRequests;   
} ADC_InitTypeDef;



  
typedef struct
{
  uint32_t Channel;                  
  uint32_t Rank;                     
  uint32_t SamplingTime;             
  uint32_t Offset;                   
} ADC_ChannelConfTypeDef;

  
typedef struct
{
  uint32_t WatchdogMode;        
  uint32_t HighThreshold;       
  uint32_t LowThreshold;        
  uint32_t Channel;             
  FunctionalState ITMode;       
  uint32_t WatchdogNumber;      
} ADC_AnalogWDGConfTypeDef;

  
  
#define HAL_ADC_STATE_RESET             0x00000000U      
#define HAL_ADC_STATE_READY             0x00000001U      
#define HAL_ADC_STATE_BUSY_INTERNAL     0x00000002U      
#define HAL_ADC_STATE_TIMEOUT           0x00000004U      

  
#define HAL_ADC_STATE_ERROR_INTERNAL    0x00000010U      
#define HAL_ADC_STATE_ERROR_CONFIG      0x00000020U      
#define HAL_ADC_STATE_ERROR_DMA         0x00000040U      

  
#define HAL_ADC_STATE_REG_BUSY          0x00000100U      
#define HAL_ADC_STATE_REG_EOC           0x00000200U      
#define HAL_ADC_STATE_REG_OVR           0x00000400U      

  
#define HAL_ADC_STATE_INJ_BUSY          0x00001000U      
#define HAL_ADC_STATE_INJ_EOC           0x00002000U      

  
#define HAL_ADC_STATE_AWD1              0x00010000U      
#define HAL_ADC_STATE_AWD2              0x00020000U      
#define HAL_ADC_STATE_AWD3              0x00040000U      

  
#define HAL_ADC_STATE_MULTIMODE_SLAVE   0x00100000U      


  
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
typedef struct __ADC_HandleTypeDef
#else
typedef struct
#endif
{
  ADC_TypeDef                   *Instance;                     

  ADC_InitTypeDef               Init;                          

  __IO uint32_t                 NbrOfCurrentConversionRank;    

  DMA_HandleTypeDef             *DMA_Handle;                   

  HAL_LockTypeDef               Lock;                          

  __IO uint32_t                 State;                         

  __IO uint32_t                 ErrorCode;                     
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
  void (* ConvCpltCallback)(struct __ADC_HandleTypeDef *hadc);                
  void (* ConvHalfCpltCallback)(struct __ADC_HandleTypeDef *hadc);            
  void (* LevelOutOfWindowCallback)(struct __ADC_HandleTypeDef *hadc);        
  void (* ErrorCallback)(struct __ADC_HandleTypeDef *hadc);                   
  void (* InjectedConvCpltCallback)(struct __ADC_HandleTypeDef *hadc);        
  void (* MspInitCallback)(struct __ADC_HandleTypeDef *hadc);                 
  void (* MspDeInitCallback)(struct __ADC_HandleTypeDef *hadc);               
#endif   
} ADC_HandleTypeDef;

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
  
typedef enum
{
  HAL_ADC_CONVERSION_COMPLETE_CB_ID     = 0x00U,    
  HAL_ADC_CONVERSION_HALF_CB_ID         = 0x01U,    
  HAL_ADC_LEVEL_OUT_OF_WINDOW_1_CB_ID   = 0x02U,    
  HAL_ADC_ERROR_CB_ID                   = 0x03U,    
  HAL_ADC_INJ_CONVERSION_COMPLETE_CB_ID = 0x04U,    
  HAL_ADC_MSPINIT_CB_ID                 = 0x05U,    
  HAL_ADC_MSPDEINIT_CB_ID               = 0x06U     
} HAL_ADC_CallbackIDTypeDef;

  
typedef  void (*pADC_CallbackTypeDef)(ADC_HandleTypeDef *hadc);   

#endif   

  

  
  

  
#define HAL_ADC_ERROR_NONE        0x00U     
#define HAL_ADC_ERROR_INTERNAL    0x01U     
#define HAL_ADC_ERROR_OVR         0x02U     
#define HAL_ADC_ERROR_DMA         0x04U     
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
#define HAL_ADC_ERROR_INVALID_CALLBACK  (0x10U)     
#endif   
  


  
#define ADC_CLOCK_SYNC_PCLK_DIV2    0x00000000U
#define ADC_CLOCK_SYNC_PCLK_DIV4    ((uint32_t)ADC_CCR_ADCPRE_0)
#define ADC_CLOCK_SYNC_PCLK_DIV6    ((uint32_t)ADC_CCR_ADCPRE_1)
#define ADC_CLOCK_SYNC_PCLK_DIV8    ((uint32_t)ADC_CCR_ADCPRE)
  

  
#define ADC_TWOSAMPLINGDELAY_5CYCLES    0x00000000U
#define ADC_TWOSAMPLINGDELAY_6CYCLES    ((uint32_t)ADC_CCR_DELAY_0)
#define ADC_TWOSAMPLINGDELAY_7CYCLES    ((uint32_t)ADC_CCR_DELAY_1)
#define ADC_TWOSAMPLINGDELAY_8CYCLES    ((uint32_t)(ADC_CCR_DELAY_1 | ADC_CCR_DELAY_0))
#define ADC_TWOSAMPLINGDELAY_9CYCLES    ((uint32_t)ADC_CCR_DELAY_2)
#define ADC_TWOSAMPLINGDELAY_10CYCLES   ((uint32_t)(ADC_CCR_DELAY_2 | ADC_CCR_DELAY_0))
#define ADC_TWOSAMPLINGDELAY_11CYCLES   ((uint32_t)(ADC_CCR_DELAY_2 | ADC_CCR_DELAY_1))
#define ADC_TWOSAMPLINGDELAY_12CYCLES   ((uint32_t)(ADC_CCR_DELAY_2 | ADC_CCR_DELAY_1 | ADC_CCR_DELAY_0))
#define ADC_TWOSAMPLINGDELAY_13CYCLES   ((uint32_t)ADC_CCR_DELAY_3)
#define ADC_TWOSAMPLINGDELAY_14CYCLES   ((uint32_t)(ADC_CCR_DELAY_3 | ADC_CCR_DELAY_0))
#define ADC_TWOSAMPLINGDELAY_15CYCLES   ((uint32_t)(ADC_CCR_DELAY_3 | ADC_CCR_DELAY_1))
#define ADC_TWOSAMPLINGDELAY_16CYCLES   ((uint32_t)(ADC_CCR_DELAY_3 | ADC_CCR_DELAY_1 | ADC_CCR_DELAY_0))
#define ADC_TWOSAMPLINGDELAY_17CYCLES   ((uint32_t)(ADC_CCR_DELAY_3 | ADC_CCR_DELAY_2))
#define ADC_TWOSAMPLINGDELAY_18CYCLES   ((uint32_t)(ADC_CCR_DELAY_3 | ADC_CCR_DELAY_2 | ADC_CCR_DELAY_0))
#define ADC_TWOSAMPLINGDELAY_19CYCLES   ((uint32_t)(ADC_CCR_DELAY_3 | ADC_CCR_DELAY_2 | ADC_CCR_DELAY_1))
#define ADC_TWOSAMPLINGDELAY_20CYCLES   ((uint32_t)ADC_CCR_DELAY)
  

  
#define ADC_RESOLUTION_12B  0x00000000U
#define ADC_RESOLUTION_10B  ((uint32_t)ADC_CR1_RES_0)
#define ADC_RESOLUTION_8B   ((uint32_t)ADC_CR1_RES_1)
#define ADC_RESOLUTION_6B   ((uint32_t)ADC_CR1_RES)
  

  
#define ADC_EXTERNALTRIGCONVEDGE_NONE           0x00000000U
#define ADC_EXTERNALTRIGCONVEDGE_RISING         ((uint32_t)ADC_CR2_EXTEN_0)
#define ADC_EXTERNALTRIGCONVEDGE_FALLING        ((uint32_t)ADC_CR2_EXTEN_1)
#define ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING  ((uint32_t)ADC_CR2_EXTEN)
  

  
  
  
#define ADC_EXTERNALTRIGCONV_T1_CC1    0x00000000U
#define ADC_EXTERNALTRIGCONV_T1_CC2    ((uint32_t)ADC_CR2_EXTSEL_0)
#define ADC_EXTERNALTRIGCONV_T1_CC3    ((uint32_t)ADC_CR2_EXTSEL_1)
#define ADC_EXTERNALTRIGCONV_T2_CC2    ((uint32_t)(ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0))
#define ADC_EXTERNALTRIGCONV_T2_CC3    ((uint32_t)ADC_CR2_EXTSEL_2)
#define ADC_EXTERNALTRIGCONV_T2_CC4    ((uint32_t)(ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_0))
#define ADC_EXTERNALTRIGCONV_T2_TRGO   ((uint32_t)(ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1))
#define ADC_EXTERNALTRIGCONV_T3_CC1    ((uint32_t)(ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0))
#define ADC_EXTERNALTRIGCONV_T3_TRGO   ((uint32_t)ADC_CR2_EXTSEL_3)
#define ADC_EXTERNALTRIGCONV_T4_CC4    ((uint32_t)(ADC_CR2_EXTSEL_3 | ADC_CR2_EXTSEL_0))
#define ADC_EXTERNALTRIGCONV_T5_CC1    ((uint32_t)(ADC_CR2_EXTSEL_3 | ADC_CR2_EXTSEL_1))
#define ADC_EXTERNALTRIGCONV_T5_CC2    ((uint32_t)(ADC_CR2_EXTSEL_3 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0))
#define ADC_EXTERNALTRIGCONV_T5_CC3    ((uint32_t)(ADC_CR2_EXTSEL_3 | ADC_CR2_EXTSEL_2))
#define ADC_EXTERNALTRIGCONV_T8_CC1    ((uint32_t)(ADC_CR2_EXTSEL_3 | ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_0))
#define ADC_EXTERNALTRIGCONV_T8_TRGO   ((uint32_t)(ADC_CR2_EXTSEL_3 | ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1))
#define ADC_EXTERNALTRIGCONV_Ext_IT11  ((uint32_t)ADC_CR2_EXTSEL)
#define ADC_SOFTWARE_START             ((uint32_t)ADC_CR2_EXTSEL + 1U)
  

  
#define ADC_DATAALIGN_RIGHT      0x00000000U
#define ADC_DATAALIGN_LEFT       ((uint32_t)ADC_CR2_ALIGN)
  

  
#define ADC_CHANNEL_0           0x00000000U
#define ADC_CHANNEL_1           ((uint32_t)ADC_CR1_AWDCH_0)
#define ADC_CHANNEL_2           ((uint32_t)ADC_CR1_AWDCH_1)
#define ADC_CHANNEL_3           ((uint32_t)(ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_4           ((uint32_t)ADC_CR1_AWDCH_2)
#define ADC_CHANNEL_5           ((uint32_t)(ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_6           ((uint32_t)(ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_1))
#define ADC_CHANNEL_7           ((uint32_t)(ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_8           ((uint32_t)ADC_CR1_AWDCH_3)
#define ADC_CHANNEL_9           ((uint32_t)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_10          ((uint32_t)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_1))
#define ADC_CHANNEL_11          ((uint32_t)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_12          ((uint32_t)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_2))
#define ADC_CHANNEL_13          ((uint32_t)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_14          ((uint32_t)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_1))
#define ADC_CHANNEL_15          ((uint32_t)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_16          ((uint32_t)ADC_CR1_AWDCH_4)
#define ADC_CHANNEL_17          ((uint32_t)(ADC_CR1_AWDCH_4 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_18          ((uint32_t)(ADC_CR1_AWDCH_4 | ADC_CR1_AWDCH_1))

#define ADC_CHANNEL_VREFINT     ((uint32_t)ADC_CHANNEL_17)
#define ADC_CHANNEL_VBAT        ((uint32_t)ADC_CHANNEL_18)
  

  
#define ADC_SAMPLETIME_3CYCLES    0x00000000U
#define ADC_SAMPLETIME_15CYCLES   ((uint32_t)ADC_SMPR1_SMP10_0)
#define ADC_SAMPLETIME_28CYCLES   ((uint32_t)ADC_SMPR1_SMP10_1)
#define ADC_SAMPLETIME_56CYCLES   ((uint32_t)(ADC_SMPR1_SMP10_1 | ADC_SMPR1_SMP10_0))
#define ADC_SAMPLETIME_84CYCLES   ((uint32_t)ADC_SMPR1_SMP10_2)
#define ADC_SAMPLETIME_112CYCLES  ((uint32_t)(ADC_SMPR1_SMP10_2 | ADC_SMPR1_SMP10_0))
#define ADC_SAMPLETIME_144CYCLES  ((uint32_t)(ADC_SMPR1_SMP10_2 | ADC_SMPR1_SMP10_1))
#define ADC_SAMPLETIME_480CYCLES  ((uint32_t)ADC_SMPR1_SMP10)
  

  
#define ADC_EOC_SEQ_CONV              0x00000000U
#define ADC_EOC_SINGLE_CONV           0x00000001U
#define ADC_EOC_SINGLE_SEQ_CONV       0x00000002U    
  

  
#define ADC_AWD_EVENT             ((uint32_t)ADC_FLAG_AWD)
#define ADC_OVR_EVENT             ((uint32_t)ADC_FLAG_OVR)
  

  
#define ADC_ANALOGWATCHDOG_SINGLE_REG         ((uint32_t)(ADC_CR1_AWDSGL | ADC_CR1_AWDEN))
#define ADC_ANALOGWATCHDOG_SINGLE_INJEC       ((uint32_t)(ADC_CR1_AWDSGL | ADC_CR1_JAWDEN))
#define ADC_ANALOGWATCHDOG_SINGLE_REGINJEC    ((uint32_t)(ADC_CR1_AWDSGL | ADC_CR1_AWDEN | ADC_CR1_JAWDEN))
#define ADC_ANALOGWATCHDOG_ALL_REG            ((uint32_t)ADC_CR1_AWDEN)
#define ADC_ANALOGWATCHDOG_ALL_INJEC          ((uint32_t)ADC_CR1_JAWDEN)
#define ADC_ANALOGWATCHDOG_ALL_REGINJEC       ((uint32_t)(ADC_CR1_AWDEN | ADC_CR1_JAWDEN))
#define ADC_ANALOGWATCHDOG_NONE               0x00000000U
  

  
#define ADC_IT_EOC      ((uint32_t)ADC_CR1_EOCIE)
#define ADC_IT_AWD      ((uint32_t)ADC_CR1_AWDIE)
#define ADC_IT_JEOC     ((uint32_t)ADC_CR1_JEOCIE)
#define ADC_IT_OVR      ((uint32_t)ADC_CR1_OVRIE)
  

  
#define ADC_FLAG_AWD    ((uint32_t)ADC_SR_AWD)
#define ADC_FLAG_EOC    ((uint32_t)ADC_SR_EOC)
#define ADC_FLAG_JEOC   ((uint32_t)ADC_SR_JEOC)
#define ADC_FLAG_JSTRT  ((uint32_t)ADC_SR_JSTRT)
#define ADC_FLAG_STRT   ((uint32_t)ADC_SR_STRT)
#define ADC_FLAG_OVR    ((uint32_t)ADC_SR_OVR)
  

  
#define ADC_ALL_CHANNELS      0x00000001U
#define ADC_REGULAR_CHANNELS  0x00000002U   
#define ADC_INJECTED_CHANNELS 0x00000003U   
  

  

  
  

  
#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__)                               \
  do{                                                                          \
     (__HANDLE__)->State = HAL_ADC_STATE_RESET;                               \
     (__HANDLE__)->MspInitCallback = NULL;                                     \
     (__HANDLE__)->MspDeInitCallback = NULL;                                   \
    } while(0)
#else
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__)                               \
  ((__HANDLE__)->State = HAL_ADC_STATE_RESET)
#endif

  
#define __HAL_ADC_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR2 |=  ADC_CR2_ADON)

  
#define __HAL_ADC_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR2 &=  ~ADC_CR2_ADON)

  
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->CR1) |= (__INTERRUPT__))

  
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->CR1) &= ~(__INTERRUPT__))

  
#define __HAL_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  (((__HANDLE__)->Instance->CR1 & (__INTERRUPT__)) == (__INTERRUPT__))

  
#define __HAL_ADC_CLEAR_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->SR) = ~(__FLAG__))

  
#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__) ((((__HANDLE__)->Instance->SR) & (__FLAG__)) == (__FLAG__))

  

  
#include "stm32f4xx_hal_adc_ex.h"

  
  

  
  
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc);
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc);

#if (USE_HAL_ADC_REGISTER_CALLBACKS == 1)
  
HAL_StatusTypeDef HAL_ADC_RegisterCallback(ADC_HandleTypeDef *hadc, HAL_ADC_CallbackIDTypeDef CallbackID, pADC_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_ADC_UnRegisterCallback(ADC_HandleTypeDef *hadc, HAL_ADC_CallbackIDTypeDef CallbackID);
#endif   
  

  
  
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);

HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef *hadc, uint32_t EventType, uint32_t Timeout);

HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef *hadc);

void HAL_ADC_IRQHandler(ADC_HandleTypeDef *hadc);

HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length);
HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef *hadc);

uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc);

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);
  

  
  
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig);
HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef *hadc, ADC_AnalogWDGConfTypeDef *AnalogWDGConfig);
  

  
  
uint32_t HAL_ADC_GetState(ADC_HandleTypeDef *hadc);
uint32_t HAL_ADC_GetError(ADC_HandleTypeDef *hadc);
  

  
  
  
  
  
  
  
  
#define ADC_STAB_DELAY_US               3U
  
  
  
#define ADC_TEMPSENSOR_DELAY_US         10U
  

  

  
  

  
#define ADC_IS_ENABLE(__HANDLE__)                                              \
  ((( ((__HANDLE__)->Instance->SR & ADC_SR_ADONS) == ADC_SR_ADONS )            \
  ) ? SET : RESET)

  
#define ADC_IS_SOFTWARE_START_REGULAR(__HANDLE__)                              \
  (((__HANDLE__)->Instance->CR2 & ADC_CR2_EXTEN) == RESET)

  
#define ADC_IS_SOFTWARE_START_INJECTED(__HANDLE__)                             \
  (((__HANDLE__)->Instance->CR2 & ADC_CR2_JEXTEN) == RESET)

  
#define ADC_STATE_CLR_SET MODIFY_REG

  
#define ADC_CLEAR_ERRORCODE(__HANDLE__)                                        \
  ((__HANDLE__)->ErrorCode = HAL_ADC_ERROR_NONE)


#define IS_ADC_CLOCKPRESCALER(ADC_CLOCK)     (((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV2) || \
                                              ((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV4) || \
                                              ((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV6) || \
                                              ((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV8))
#define IS_ADC_SAMPLING_DELAY(DELAY) (((DELAY) == ADC_TWOSAMPLINGDELAY_5CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_6CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_7CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_8CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_9CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_10CYCLES) || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_11CYCLES) || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_12CYCLES) || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_13CYCLES) || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_14CYCLES) || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_15CYCLES) || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_16CYCLES) || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_17CYCLES) || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_18CYCLES) || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_19CYCLES) || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_20CYCLES))
#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_RESOLUTION_12B) || \
                                       ((RESOLUTION) == ADC_RESOLUTION_10B) || \
                                       ((RESOLUTION) == ADC_RESOLUTION_8B)  || \
                                       ((RESOLUTION) == ADC_RESOLUTION_6B))
#define IS_ADC_EXT_TRIG_EDGE(EDGE) (((EDGE) == ADC_EXTERNALTRIGCONVEDGE_NONE)    || \
                                    ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISING)  || \
                                    ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_FALLING) || \
                                    ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING))
#define IS_ADC_EXT_TRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC1)  || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC2)  || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_T1_CC3)  || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC2)  || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC3)  || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_CC4)  || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_T2_TRGO) || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_CC1)  || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_T3_TRGO) || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_T4_CC4)  || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_T5_CC1)  || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_T5_CC2)  || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_T5_CC3)  || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_T8_CC1)  || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_T8_TRGO) || \
                                  ((REGTRIG) == ADC_EXTERNALTRIGCONV_Ext_IT11)|| \
                                  ((REGTRIG) == ADC_SOFTWARE_START))
#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DATAALIGN_RIGHT) || \
                                  ((ALIGN) == ADC_DATAALIGN_LEFT))
#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SAMPLETIME_3CYCLES)   || \
                                  ((TIME) == ADC_SAMPLETIME_15CYCLES)  || \
                                  ((TIME) == ADC_SAMPLETIME_28CYCLES)  || \
                                  ((TIME) == ADC_SAMPLETIME_56CYCLES)  || \
                                  ((TIME) == ADC_SAMPLETIME_84CYCLES)  || \
                                  ((TIME) == ADC_SAMPLETIME_112CYCLES) || \
                                  ((TIME) == ADC_SAMPLETIME_144CYCLES) || \
                                  ((TIME) == ADC_SAMPLETIME_480CYCLES))
#define IS_ADC_EOCSelection(EOCSelection) (((EOCSelection) == ADC_EOC_SINGLE_CONV)   || \
                                           ((EOCSelection) == ADC_EOC_SEQ_CONV)  || \
                                           ((EOCSelection) == ADC_EOC_SINGLE_SEQ_CONV))
#define IS_ADC_EVENT_TYPE(EVENT) (((EVENT) == ADC_AWD_EVENT) || \
                                  ((EVENT) == ADC_OVR_EVENT))
#define IS_ADC_ANALOG_WATCHDOG(WATCHDOG) (((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_REG)        || \
                                          ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_INJEC)      || \
                                          ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_REGINJEC)   || \
                                          ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_REG)           || \
                                          ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_INJEC)         || \
                                          ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_REGINJEC)      || \
                                          ((WATCHDOG) == ADC_ANALOGWATCHDOG_NONE))
#define IS_ADC_CHANNELS_TYPE(CHANNEL_TYPE) (((CHANNEL_TYPE) == ADC_ALL_CHANNELS) || \
                                            ((CHANNEL_TYPE) == ADC_REGULAR_CHANNELS) || \
                                            ((CHANNEL_TYPE) == ADC_INJECTED_CHANNELS))
#define IS_ADC_THRESHOLD(THRESHOLD) ((THRESHOLD) <= 0xFFFU)

#define IS_ADC_REGULAR_LENGTH(LENGTH) (((LENGTH) >= 1U) && ((LENGTH) <= 16U))
#define IS_ADC_REGULAR_RANK(RANK) (((RANK) >= 1U) && ((RANK) <= (16U)))
#define IS_ADC_REGULAR_DISC_NUMBER(NUMBER) (((NUMBER) >= 1U) && ((NUMBER) <= 8U))
#define IS_ADC_RANGE(RESOLUTION, ADC_VALUE)                                     \
   ((((RESOLUTION) == ADC_RESOLUTION_12B) && ((ADC_VALUE) <= 0x0FFFU)) || \
    (((RESOLUTION) == ADC_RESOLUTION_10B) && ((ADC_VALUE) <= 0x03FFU)) || \
    (((RESOLUTION) == ADC_RESOLUTION_8B)  && ((ADC_VALUE) <= 0x00FFU)) || \
    (((RESOLUTION) == ADC_RESOLUTION_6B)  && ((ADC_VALUE) <= 0x003FU)))

  
#define ADC_SQR1(_NbrOfConversion_) (((_NbrOfConversion_) - (uint8_t)1U) << 20U)

  
#define ADC_SMPR1(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3U * (((uint32_t)((uint16_t)(_CHANNELNB_))) - 10U)))

  
#define ADC_SMPR2(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3U * ((uint32_t)((uint16_t)(_CHANNELNB_)))))

  
#define ADC_SQR3_RK(_CHANNELNB_, _RANKNB_) (((uint32_t)((uint16_t)(_CHANNELNB_))) << (5U * ((_RANKNB_) - 1U)))

  
#define ADC_SQR2_RK(_CHANNELNB_, _RANKNB_) (((uint32_t)((uint16_t)(_CHANNELNB_))) << (5U * ((_RANKNB_) - 7U)))

  
#define ADC_SQR1_RK(_CHANNELNB_, _RANKNB_) (((uint32_t)((uint16_t)(_CHANNELNB_))) << (5U * ((_RANKNB_) - 13U)))

  
#define ADC_CR2_CONTINUOUS(_CONTINUOUS_MODE_) ((_CONTINUOUS_MODE_) << 1U)

  
#define ADC_CR1_DISCONTINUOUS(_NBR_DISCONTINUOUSCONV_) (((_NBR_DISCONTINUOUSCONV_) - 1U) << ADC_CR1_DISCNUM_Pos)

  
#define ADC_CR1_SCANCONV(_SCANCONV_MODE_) ((_SCANCONV_MODE_) << 8U)

  
#define ADC_CR2_EOCSelection(_EOCSelection_MODE_) ((_EOCSelection_MODE_) << 10U)

  
#define ADC_CR2_DMAContReq(_DMAContReq_MODE_) ((_DMAContReq_MODE_) << 9U)

  
#define ADC_GET_RESOLUTION(__HANDLE__) (((__HANDLE__)->Instance->CR1) & ADC_CR1_RES)

  

  
  

  

  

  

#ifdef __cplusplus
}
#endif

#endif   


