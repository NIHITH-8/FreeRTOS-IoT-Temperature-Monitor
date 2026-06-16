  

  
#ifndef __STM32F4xx_ADC_EX_H
#define __STM32F4xx_ADC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

  
#include "stm32f4xx_hal_def.h"

  

  

  
  

  
typedef struct
{
  uint32_t InjectedChannel;                        
  uint32_t InjectedRank;                           
  uint32_t InjectedSamplingTime;                   
  uint32_t InjectedOffset;                         
  uint32_t InjectedNbrOfConversion;                
  FunctionalState InjectedDiscontinuousConvMode;   
  FunctionalState AutoInjectedConv;                
  uint32_t ExternalTrigInjecConv;                  
  uint32_t ExternalTrigInjecConvEdge;              
} ADC_InjectionConfTypeDef;

  
typedef struct
{
  uint32_t Mode;                
  uint32_t DMAAccessMode;       
  uint32_t TwoSamplingDelay;    
} ADC_MultiModeTypeDef;

  

  
  

  
#define ADC_MODE_INDEPENDENT                  0x00000000U
#define ADC_DUALMODE_REGSIMULT_INJECSIMULT    ((uint32_t)ADC_CCR_MULTI_0)
#define ADC_DUALMODE_REGSIMULT_ALTERTRIG      ((uint32_t)ADC_CCR_MULTI_1)
#define ADC_DUALMODE_INJECSIMULT              ((uint32_t)(ADC_CCR_MULTI_2 | ADC_CCR_MULTI_0))
#define ADC_DUALMODE_REGSIMULT                ((uint32_t)(ADC_CCR_MULTI_2 | ADC_CCR_MULTI_1))
#define ADC_DUALMODE_INTERL                   ((uint32_t)(ADC_CCR_MULTI_2 | ADC_CCR_MULTI_1 | ADC_CCR_MULTI_0))
#define ADC_DUALMODE_ALTERTRIG                ((uint32_t)(ADC_CCR_MULTI_3 | ADC_CCR_MULTI_0))
#define ADC_TRIPLEMODE_REGSIMULT_INJECSIMULT  ((uint32_t)(ADC_CCR_MULTI_4 | ADC_CCR_MULTI_0))
#define ADC_TRIPLEMODE_REGSIMULT_AlterTrig    ((uint32_t)(ADC_CCR_MULTI_4 | ADC_CCR_MULTI_1))
#define ADC_TRIPLEMODE_INJECSIMULT            ((uint32_t)(ADC_CCR_MULTI_4 | ADC_CCR_MULTI_2 | ADC_CCR_MULTI_0))
#define ADC_TRIPLEMODE_REGSIMULT              ((uint32_t)(ADC_CCR_MULTI_4 | ADC_CCR_MULTI_2 | ADC_CCR_MULTI_1))
#define ADC_TRIPLEMODE_INTERL                 ((uint32_t)(ADC_CCR_MULTI_4 | ADC_CCR_MULTI_2 | ADC_CCR_MULTI_1 | ADC_CCR_MULTI_0))
#define ADC_TRIPLEMODE_ALTERTRIG              ((uint32_t)(ADC_CCR_MULTI_4 | ADC_CCR_MULTI_3 | ADC_CCR_MULTI_0))
  

  
#define ADC_DMAACCESSMODE_DISABLED  0x00000000U                  
#define ADC_DMAACCESSMODE_1         ((uint32_t)ADC_CCR_DMA_0)    
#define ADC_DMAACCESSMODE_2         ((uint32_t)ADC_CCR_DMA_1)    
#define ADC_DMAACCESSMODE_3         ((uint32_t)ADC_CCR_DMA)      
  

  
#define ADC_EXTERNALTRIGINJECCONVEDGE_NONE           0x00000000U
#define ADC_EXTERNALTRIGINJECCONVEDGE_RISING         ((uint32_t)ADC_CR2_JEXTEN_0)
#define ADC_EXTERNALTRIGINJECCONVEDGE_FALLING        ((uint32_t)ADC_CR2_JEXTEN_1)
#define ADC_EXTERNALTRIGINJECCONVEDGE_RISINGFALLING  ((uint32_t)ADC_CR2_JEXTEN)
  

  
#define ADC_EXTERNALTRIGINJECCONV_T1_CC4           0x00000000U
#define ADC_EXTERNALTRIGINJECCONV_T1_TRGO          ((uint32_t)ADC_CR2_JEXTSEL_0)
#define ADC_EXTERNALTRIGINJECCONV_T2_CC1           ((uint32_t)ADC_CR2_JEXTSEL_1)
#define ADC_EXTERNALTRIGINJECCONV_T2_TRGO          ((uint32_t)(ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0))
#define ADC_EXTERNALTRIGINJECCONV_T3_CC2           ((uint32_t)ADC_CR2_JEXTSEL_2)
#define ADC_EXTERNALTRIGINJECCONV_T3_CC4           ((uint32_t)(ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_0))
#define ADC_EXTERNALTRIGINJECCONV_T4_CC1           ((uint32_t)(ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_1))
#define ADC_EXTERNALTRIGINJECCONV_T4_CC2           ((uint32_t)(ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0))
#define ADC_EXTERNALTRIGINJECCONV_T4_CC3           ((uint32_t)ADC_CR2_JEXTSEL_3)
#define ADC_EXTERNALTRIGINJECCONV_T4_TRGO          ((uint32_t)(ADC_CR2_JEXTSEL_3 | ADC_CR2_JEXTSEL_0))
#define ADC_EXTERNALTRIGINJECCONV_T5_CC4           ((uint32_t)(ADC_CR2_JEXTSEL_3 | ADC_CR2_JEXTSEL_1))
#define ADC_EXTERNALTRIGINJECCONV_T5_TRGO          ((uint32_t)(ADC_CR2_JEXTSEL_3 | ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0))
#define ADC_EXTERNALTRIGINJECCONV_T8_CC2           ((uint32_t)(ADC_CR2_JEXTSEL_3 | ADC_CR2_JEXTSEL_2))
#define ADC_EXTERNALTRIGINJECCONV_T8_CC3           ((uint32_t)(ADC_CR2_JEXTSEL_3 | ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_0))
#define ADC_EXTERNALTRIGINJECCONV_T8_CC4           ((uint32_t)(ADC_CR2_JEXTSEL_3 | ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_1))
#define ADC_EXTERNALTRIGINJECCONV_EXT_IT15         ((uint32_t)ADC_CR2_JEXTSEL)
#define ADC_INJECTED_SOFTWARE_START                ((uint32_t)ADC_CR2_JEXTSEL + 1U)
  

  
#define ADC_INJECTED_RANK_1    0x00000001U
#define ADC_INJECTED_RANK_2    0x00000002U
#define ADC_INJECTED_RANK_3    0x00000003U
#define ADC_INJECTED_RANK_4    0x00000004U
  

  
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || \
    defined(STM32F410Rx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || \
    defined(STM32F412Cx)
#define ADC_CHANNEL_TEMPSENSOR  ((uint32_t)ADC_CHANNEL_16)
#endif   

#if defined(STM32F411xE) || defined(STM32F413xx) || defined(STM32F423xx) || defined(STM32F427xx) || defined(STM32F437xx) ||\
    defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define ADC_CHANNEL_DIFFERENCIATION_TEMPSENSOR_VBAT 0x10000000U   
#define ADC_CHANNEL_TEMPSENSOR  ((uint32_t)ADC_CHANNEL_18 | ADC_CHANNEL_DIFFERENCIATION_TEMPSENSOR_VBAT)
#endif   
  


  

  
  
#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx)
  
#define __HAL_ADC_PATH_INTERNAL_VBAT_DISABLE() (ADC->CCR &= ~(ADC_CCR_VBATE))
#endif   
  

  
  

  

  
HAL_StatusTypeDef HAL_ADCEx_InjectedStart(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_InjectedStop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);
HAL_StatusTypeDef HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef *hadc);
uint32_t HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef *hadc, uint32_t InjectedRank);
HAL_StatusTypeDef HAL_ADCEx_MultiModeStart_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length);
HAL_StatusTypeDef HAL_ADCEx_MultiModeStop_DMA(ADC_HandleTypeDef *hadc);
uint32_t HAL_ADCEx_MultiModeGetValue(ADC_HandleTypeDef *hadc);
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc);

  
HAL_StatusTypeDef HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef *hadc, ADC_InjectionConfTypeDef *sConfigInjected);
HAL_StatusTypeDef HAL_ADCEx_MultiModeConfigChannel(ADC_HandleTypeDef *hadc, ADC_MultiModeTypeDef *multimode);

  

  
  
  
  
  

  

  
  
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || \
    defined(STM32F410Rx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || \
    defined(STM32F412Cx)
#define IS_ADC_CHANNEL(CHANNEL) ((CHANNEL) <= ADC_CHANNEL_18)
#endif   

#if defined(STM32F411xE) || defined(STM32F413xx) || defined(STM32F423xx) || defined(STM32F427xx) || \
    defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F446xx) || \
    defined(STM32F469xx) || defined(STM32F479xx)
#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) <= ADC_CHANNEL_18)  || \
                                 ((CHANNEL) == ADC_CHANNEL_TEMPSENSOR))
#endif   

#define IS_ADC_MODE(MODE) (((MODE) == ADC_MODE_INDEPENDENT)                 || \
                           ((MODE) == ADC_DUALMODE_REGSIMULT_INJECSIMULT)   || \
                           ((MODE) == ADC_DUALMODE_REGSIMULT_ALTERTRIG)     || \
                           ((MODE) == ADC_DUALMODE_INJECSIMULT)             || \
                           ((MODE) == ADC_DUALMODE_REGSIMULT)               || \
                           ((MODE) == ADC_DUALMODE_INTERL)                  || \
                           ((MODE) == ADC_DUALMODE_ALTERTRIG)               || \
                           ((MODE) == ADC_TRIPLEMODE_REGSIMULT_INJECSIMULT) || \
                           ((MODE) == ADC_TRIPLEMODE_REGSIMULT_AlterTrig)   || \
                           ((MODE) == ADC_TRIPLEMODE_INJECSIMULT)           || \
                           ((MODE) == ADC_TRIPLEMODE_REGSIMULT)             || \
                           ((MODE) == ADC_TRIPLEMODE_INTERL)                || \
                           ((MODE) == ADC_TRIPLEMODE_ALTERTRIG))
#define IS_ADC_DMA_ACCESS_MODE(MODE) (((MODE) == ADC_DMAACCESSMODE_DISABLED) || \
                                      ((MODE) == ADC_DMAACCESSMODE_1)        || \
                                      ((MODE) == ADC_DMAACCESSMODE_2)        || \
                                      ((MODE) == ADC_DMAACCESSMODE_3))
#define IS_ADC_EXT_INJEC_TRIG_EDGE(EDGE) (((EDGE) == ADC_EXTERNALTRIGINJECCONVEDGE_NONE)    || \
                                          ((EDGE) == ADC_EXTERNALTRIGINJECCONVEDGE_RISING)  || \
                                          ((EDGE) == ADC_EXTERNALTRIGINJECCONVEDGE_FALLING) || \
                                          ((EDGE) == ADC_EXTERNALTRIGINJECCONVEDGE_RISINGFALLING))
#define IS_ADC_EXT_INJEC_TRIG(INJTRIG) (((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_CC4)  || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T1_TRGO) || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_CC1)  || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T2_TRGO) || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC2)  || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T3_CC4)  || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_CC1)  || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_CC2)  || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_CC3)  || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T4_TRGO) || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T5_CC4)  || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T5_TRGO) || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_CC2)  || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_CC3)  || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_T8_CC4)  || \
                                        ((INJTRIG) == ADC_EXTERNALTRIGINJECCONV_EXT_IT15)|| \
                                        ((INJTRIG) == ADC_INJECTED_SOFTWARE_START))
#define IS_ADC_INJECTED_LENGTH(LENGTH) (((LENGTH) >= 1U) && ((LENGTH) <= 4U))
#define IS_ADC_INJECTED_RANK(RANK) (((RANK) >= 1U) && ((RANK) <= 4U))

  
#define   ADC_JSQR(_CHANNELNB_, _RANKNB_, _JSQR_JL_)  (((uint32_t)((uint16_t)(_CHANNELNB_))) << (5U * (uint8_t)(((_RANKNB_) + 3U) - (_JSQR_JL_))))

  
#if defined(STM32F405xx) || defined(STM32F407xx) || defined(STM32F415xx) || defined(STM32F417xx) || defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) || defined(STM32F439xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define ADC_COMMON_REGISTER(__HANDLE__)                ADC123_COMMON
#else
#define ADC_COMMON_REGISTER(__HANDLE__)                ADC1_COMMON
#endif   
  

  
  

  

  

  

#ifdef __cplusplus
}
#endif

#endif   


