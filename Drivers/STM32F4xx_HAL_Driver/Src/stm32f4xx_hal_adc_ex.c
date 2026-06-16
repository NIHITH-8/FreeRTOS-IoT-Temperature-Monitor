  

  
#include "stm32f4xx_hal.h"

  

  

#ifdef HAL_ADC_MODULE_ENABLED

  
  
  
  
  
  
static void ADC_MultiModeDMAConvCplt(DMA_HandleTypeDef *hdma);
static void ADC_MultiModeDMAError(DMA_HandleTypeDef *hdma);
static void ADC_MultiModeDMAHalfConvCplt(DMA_HandleTypeDef *hdma);
  

  
  

  

  
HAL_StatusTypeDef HAL_ADCEx_InjectedStart(ADC_HandleTypeDef *hadc)
{
  __IO uint32_t counter = 0U;
  uint32_t tmp1 = 0U, tmp2 = 0U;
  ADC_Common_TypeDef *tmpADC_Common;

    
  __HAL_LOCK(hadc);

    

    
  if ((hadc->Instance->CR2 & ADC_CR2_ADON) != ADC_CR2_ADON)
  {
      
    __HAL_ADC_ENABLE(hadc);

      
      
    counter = (ADC_STAB_DELAY_US * (SystemCoreClock / 1000000U));
    while (counter != 0U)
    {
      counter--;
    }
  }

    
  if (HAL_IS_BIT_SET(hadc->Instance->CR2, ADC_CR2_ADON))
  {
      
      
      
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_READY | HAL_ADC_STATE_INJ_EOC,
                      HAL_ADC_STATE_INJ_BUSY);

      
      
      
      
    if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_REG_BUSY))
    {
        
      ADC_CLEAR_ERRORCODE(hadc);
    }

      
      
      
    __HAL_UNLOCK(hadc);

      
      
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JEOC);

      
      
      
    tmpADC_Common = ADC_COMMON_REGISTER(hadc);

      
    if (HAL_IS_BIT_CLR(tmpADC_Common->CCR, ADC_CCR_MULTI))
    {
      tmp1 = HAL_IS_BIT_CLR(hadc->Instance->CR2, ADC_CR2_JEXTEN);
      tmp2 = HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO);
      if (tmp1 && tmp2)
      {
          
        hadc->Instance->CR2 |= ADC_CR2_JSWSTART;
      }
    }
    else
    {
      tmp1 = HAL_IS_BIT_CLR(hadc->Instance->CR2, ADC_CR2_JEXTEN);
      tmp2 = HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO);
      if ((hadc->Instance == ADC1) && tmp1 && tmp2)
      {
          
        hadc->Instance->CR2 |= ADC_CR2_JSWSTART;
      }
    }
  }
  else
  {
      
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);

      
    SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_INTERNAL);
  }

    
  return HAL_OK;
}

  
HAL_StatusTypeDef HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef *hadc)
{
  __IO uint32_t counter = 0U;
  uint32_t tmp1 = 0U, tmp2 = 0U;
  ADC_Common_TypeDef *tmpADC_Common;

    
  __HAL_LOCK(hadc);

    

    
  if ((hadc->Instance->CR2 & ADC_CR2_ADON) != ADC_CR2_ADON)
  {
      
    __HAL_ADC_ENABLE(hadc);

      
      
    counter = (ADC_STAB_DELAY_US * (SystemCoreClock / 1000000U));
    while (counter != 0U)
    {
      counter--;
    }
  }

    
  if (HAL_IS_BIT_SET(hadc->Instance->CR2, ADC_CR2_ADON))
  {
      
      
      
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_READY | HAL_ADC_STATE_INJ_EOC,
                      HAL_ADC_STATE_INJ_BUSY);

      
      
      
      
    if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_REG_BUSY))
    {
        
      ADC_CLEAR_ERRORCODE(hadc);
    }

      
      
      
    __HAL_UNLOCK(hadc);

      
      
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JEOC);

      
    __HAL_ADC_ENABLE_IT(hadc, ADC_IT_JEOC);

      
      
      
    tmpADC_Common = ADC_COMMON_REGISTER(hadc);

      
    if (HAL_IS_BIT_CLR(tmpADC_Common->CCR, ADC_CCR_MULTI))
    {
      tmp1 = HAL_IS_BIT_CLR(hadc->Instance->CR2, ADC_CR2_JEXTEN);
      tmp2 = HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO);
      if (tmp1 && tmp2)
      {
          
        hadc->Instance->CR2 |= ADC_CR2_JSWSTART;
      }
    }
    else
    {
      tmp1 = HAL_IS_BIT_CLR(hadc->Instance->CR2, ADC_CR2_JEXTEN);
      tmp2 = HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO);
      if ((hadc->Instance == ADC1) && tmp1 && tmp2)
      {
          
        hadc->Instance->CR2 |= ADC_CR2_JSWSTART;
      }
    }
  }
  else
  {
      
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);

      
    SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_INTERNAL);
  }

    
  return HAL_OK;
}

  
HAL_StatusTypeDef HAL_ADCEx_InjectedStop(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

    
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

    
  __HAL_LOCK(hadc);

    
    
    
    
    
    
  if (((hadc->State & HAL_ADC_STATE_REG_BUSY) == RESET)  &&
      HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO))
  {
      
      
    __HAL_ADC_DISABLE(hadc);

      
    if (HAL_IS_BIT_CLR(hadc->Instance->CR2, ADC_CR2_ADON))
    {
        
      ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_REG_BUSY | HAL_ADC_STATE_INJ_BUSY,
                        HAL_ADC_STATE_READY);
    }
  }
  else
  {
      
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_CONFIG);

    tmp_hal_status = HAL_ERROR;
  }

    
  __HAL_UNLOCK(hadc);

    
  return tmp_hal_status;
}

  
HAL_StatusTypeDef HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout)
{
  uint32_t tickstart = 0U;

    
  tickstart = HAL_GetTick();

    
  while (!(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_JEOC)))
  {
      
    if (Timeout != HAL_MAX_DELAY)
    {
      if ((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout))
      {
          
        if (!(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_JEOC)))
        {
          hadc->State = HAL_ADC_STATE_TIMEOUT;
            
          __HAL_UNLOCK(hadc);
          return HAL_TIMEOUT;
        }
      }
    }
  }

    
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JSTRT | ADC_FLAG_JEOC);

    
  SET_BIT(hadc->State, HAL_ADC_STATE_INJ_EOC);

    
    
    
    
    
    
  if (ADC_IS_SOFTWARE_START_INJECTED(hadc)                    &&
      (HAL_IS_BIT_CLR(hadc->Instance->JSQR, ADC_JSQR_JL)  ||
       HAL_IS_BIT_CLR(hadc->Instance->CR2, ADC_CR2_EOCS)) &&
      (HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO) &&
       (ADC_IS_SOFTWARE_START_REGULAR(hadc)       &&
        (hadc->Init.ContinuousConvMode == DISABLE))))
  {
      
    CLEAR_BIT(hadc->State, HAL_ADC_STATE_INJ_BUSY);

    if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_REG_BUSY))
    {
      SET_BIT(hadc->State, HAL_ADC_STATE_READY);
    }
  }

    
  return HAL_OK;
}

  
HAL_StatusTypeDef HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

    
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

    
  __HAL_LOCK(hadc);

    
    
    
    
    
    
  if (((hadc->State & HAL_ADC_STATE_REG_BUSY) == RESET)  &&
      HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO))
  {
      
      
    __HAL_ADC_DISABLE(hadc);

      
    if (HAL_IS_BIT_CLR(hadc->Instance->CR2, ADC_CR2_ADON))
    {
        
      __HAL_ADC_DISABLE_IT(hadc, ADC_IT_JEOC);

        
      ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_REG_BUSY | HAL_ADC_STATE_INJ_BUSY,
                        HAL_ADC_STATE_READY);
    }
  }
  else
  {
      
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_CONFIG);

    tmp_hal_status = HAL_ERROR;
  }

    
  __HAL_UNLOCK(hadc);

    
  return tmp_hal_status;
}

  
uint32_t HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef *hadc, uint32_t InjectedRank)
{
  __IO uint32_t tmp = 0U;

    
  assert_param(IS_ADC_INJECTED_RANK(InjectedRank));

    
    
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JEOC);

    
  switch (InjectedRank)
  {
    case ADC_INJECTED_RANK_4:
    {
      tmp =  hadc->Instance->JDR4;
    }
    break;
    case ADC_INJECTED_RANK_3:
    {
      tmp =  hadc->Instance->JDR3;
    }
    break;
    case ADC_INJECTED_RANK_2:
    {
      tmp =  hadc->Instance->JDR2;
    }
    break;
    case ADC_INJECTED_RANK_1:
    {
      tmp =  hadc->Instance->JDR1;
    }
    break;
    default:
      break;
  }
  return tmp;
}

  
HAL_StatusTypeDef HAL_ADCEx_MultiModeStart_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length)
{
  __IO uint32_t counter = 0U;
  ADC_Common_TypeDef *tmpADC_Common;
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
    
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ContinuousConvMode));
  assert_param(IS_ADC_EXT_TRIG_EDGE(hadc->Init.ExternalTrigConvEdge));
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.DMAContinuousRequests));

    
  __HAL_LOCK(hadc);

    
  if ((hadc->Instance->CR2 & ADC_CR2_ADON) != ADC_CR2_ADON)
  {
      
    __HAL_ADC_ENABLE(hadc);

      
      
    counter = (ADC_STAB_DELAY_US * (SystemCoreClock / 1000000U));
    while (counter != 0U)
    {
      counter--;
    }
  }

    
  if (HAL_IS_BIT_SET(hadc->Instance->CR2, ADC_CR2_ADON))
  {
      
      
      
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_READY | HAL_ADC_STATE_REG_EOC | HAL_ADC_STATE_REG_OVR,
                      HAL_ADC_STATE_REG_BUSY);

      
      
    if (READ_BIT(hadc->Instance->CR1, ADC_CR1_JAUTO) != RESET)
    {
      ADC_STATE_CLR_SET(hadc->State, HAL_ADC_STATE_INJ_EOC, HAL_ADC_STATE_INJ_BUSY);
    }

      
    if (HAL_IS_BIT_SET(hadc->State, HAL_ADC_STATE_INJ_BUSY))
    {
        
      CLEAR_BIT(hadc->ErrorCode, (HAL_ADC_ERROR_OVR | HAL_ADC_ERROR_DMA));
    }
    else
    {
        
      ADC_CLEAR_ERRORCODE(hadc);
    }

      
      
      
    __HAL_UNLOCK(hadc);

      
    hadc->DMA_Handle->XferCpltCallback = ADC_MultiModeDMAConvCplt;

      
    hadc->DMA_Handle->XferHalfCpltCallback = ADC_MultiModeDMAHalfConvCplt;

      
    hadc->DMA_Handle->XferErrorCallback = ADC_MultiModeDMAError ;

      
      

      
      
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_EOC);

      
    __HAL_ADC_ENABLE_IT(hadc, ADC_IT_OVR);

      
      
      
    tmpADC_Common = ADC_COMMON_REGISTER(hadc);

    if (hadc->Init.DMAContinuousRequests != DISABLE)
    {
        
      tmpADC_Common->CCR |= ADC_CCR_DDS;
    }
    else
    {
        
      tmpADC_Common->CCR &= ~ADC_CCR_DDS;
    }

      
    tmp_hal_status = HAL_DMA_Start_IT(hadc->DMA_Handle, (uint32_t)&tmpADC_Common->CDR, (uint32_t)pData, Length);

      
    if ((hadc->Instance->CR2 & ADC_CR2_EXTEN) == RESET)
    {
        
      hadc->Instance->CR2 |= (uint32_t)ADC_CR2_SWSTART;
    }
  }
  else
  {
      
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);

      
    SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_INTERNAL);
  }

    
  return tmp_hal_status;
}

  
HAL_StatusTypeDef HAL_ADCEx_MultiModeStop_DMA(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  ADC_Common_TypeDef *tmpADC_Common;

    
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

    
  __HAL_LOCK(hadc);

    
    
  __HAL_ADC_DISABLE(hadc);

    
    
    
  tmpADC_Common = ADC_COMMON_REGISTER(hadc);

    
  if (HAL_IS_BIT_CLR(hadc->Instance->CR2, ADC_CR2_ADON))
  {
      
    tmpADC_Common->CCR &= ~ADC_CCR_DDS;

      
      
    tmp_hal_status = HAL_DMA_Abort(hadc->DMA_Handle);

      
    __HAL_ADC_DISABLE_IT(hadc, ADC_IT_OVR);

      
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_REG_BUSY | HAL_ADC_STATE_INJ_BUSY,
                      HAL_ADC_STATE_READY);
  }

    
  __HAL_UNLOCK(hadc);

    
  return tmp_hal_status;
}

  
uint32_t HAL_ADCEx_MultiModeGetValue(ADC_HandleTypeDef *hadc)
{
  ADC_Common_TypeDef *tmpADC_Common;

    
  UNUSED(hadc);

    
    
    
  tmpADC_Common = ADC_COMMON_REGISTER(hadc);

    
  return tmpADC_Common->CDR;
}

  
__weak void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    
  UNUSED(hadc);
    
}

  
HAL_StatusTypeDef HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef *hadc, ADC_InjectionConfTypeDef *sConfigInjected)
{

#ifdef USE_FULL_ASSERT
  uint32_t tmp = 0U;

#endif   

  ADC_Common_TypeDef *tmpADC_Common;

    
  assert_param(IS_ADC_CHANNEL(sConfigInjected->InjectedChannel));
  assert_param(IS_ADC_INJECTED_RANK(sConfigInjected->InjectedRank));
  assert_param(IS_ADC_SAMPLE_TIME(sConfigInjected->InjectedSamplingTime));
  assert_param(IS_ADC_EXT_INJEC_TRIG(sConfigInjected->ExternalTrigInjecConv));
  assert_param(IS_ADC_INJECTED_LENGTH(sConfigInjected->InjectedNbrOfConversion));
  assert_param(IS_FUNCTIONAL_STATE(sConfigInjected->AutoInjectedConv));
  assert_param(IS_FUNCTIONAL_STATE(sConfigInjected->InjectedDiscontinuousConvMode));

#ifdef USE_FULL_ASSERT
  tmp = ADC_GET_RESOLUTION(hadc);
  assert_param(IS_ADC_RANGE(tmp, sConfigInjected->InjectedOffset));
#endif   

  if (sConfigInjected->ExternalTrigInjecConv != ADC_INJECTED_SOFTWARE_START)
  {
    assert_param(IS_ADC_EXT_INJEC_TRIG_EDGE(sConfigInjected->ExternalTrigInjecConvEdge));
  }

    
  __HAL_LOCK(hadc);

    
  if (sConfigInjected->InjectedChannel > ADC_CHANNEL_9)
  {
      
    hadc->Instance->SMPR1 &= ~ADC_SMPR1(ADC_SMPR1_SMP10, sConfigInjected->InjectedChannel);

      
    hadc->Instance->SMPR1 |= ADC_SMPR1(sConfigInjected->InjectedSamplingTime, sConfigInjected->InjectedChannel);
  }
  else   
  {
      
    hadc->Instance->SMPR2 &= ~ADC_SMPR2(ADC_SMPR2_SMP0, sConfigInjected->InjectedChannel);

      
    hadc->Instance->SMPR2 |= ADC_SMPR2(sConfigInjected->InjectedSamplingTime, sConfigInjected->InjectedChannel);
  }

    
  hadc->Instance->JSQR &= ~(ADC_JSQR_JL);
  hadc->Instance->JSQR |=  ADC_SQR1(sConfigInjected->InjectedNbrOfConversion);

    

    
  hadc->Instance->JSQR &= ~ADC_JSQR(ADC_JSQR_JSQ1, sConfigInjected->InjectedRank, sConfigInjected->InjectedNbrOfConversion);

    
  hadc->Instance->JSQR |= ADC_JSQR(sConfigInjected->InjectedChannel, sConfigInjected->InjectedRank, sConfigInjected->InjectedNbrOfConversion);

    
    
    
    
    
  if (sConfigInjected->ExternalTrigInjecConv != ADC_INJECTED_SOFTWARE_START)
  {
      
    hadc->Instance->CR2 &= ~(ADC_CR2_JEXTSEL);
    hadc->Instance->CR2 |=  sConfigInjected->ExternalTrigInjecConv;

      
    hadc->Instance->CR2 &= ~(ADC_CR2_JEXTEN);
    hadc->Instance->CR2 |= sConfigInjected->ExternalTrigInjecConvEdge;
  }
  else
  {
      
    hadc->Instance->CR2 &= ~(ADC_CR2_JEXTSEL);
    hadc->Instance->CR2 &= ~(ADC_CR2_JEXTEN);
  }

  if (sConfigInjected->AutoInjectedConv != DISABLE)
  {
      
    hadc->Instance->CR1 |= ADC_CR1_JAUTO;
  }
  else
  {
      
    hadc->Instance->CR1 &= ~(ADC_CR1_JAUTO);
  }

  if (sConfigInjected->InjectedDiscontinuousConvMode != DISABLE)
  {
      
    hadc->Instance->CR1 |= ADC_CR1_JDISCEN;
  }
  else
  {
      
    hadc->Instance->CR1 &= ~(ADC_CR1_JDISCEN);
  }

  switch (sConfigInjected->InjectedRank)
  {
    case 1U:
        
      hadc->Instance->JOFR1 &= ~(ADC_JOFR1_JOFFSET1);
      hadc->Instance->JOFR1 |= sConfigInjected->InjectedOffset;
      break;
    case 2U:
        
      hadc->Instance->JOFR2 &= ~(ADC_JOFR2_JOFFSET2);
      hadc->Instance->JOFR2 |= sConfigInjected->InjectedOffset;
      break;
    case 3U:
        
      hadc->Instance->JOFR3 &= ~(ADC_JOFR3_JOFFSET3);
      hadc->Instance->JOFR3 |= sConfigInjected->InjectedOffset;
      break;
    default:
        
      hadc->Instance->JOFR4 &= ~(ADC_JOFR4_JOFFSET4);
      hadc->Instance->JOFR4 |= sConfigInjected->InjectedOffset;
      break;
  }

    
    
    
  tmpADC_Common = ADC_COMMON_REGISTER(hadc);

    
  if ((hadc->Instance == ADC1) && (sConfigInjected->InjectedChannel == ADC_CHANNEL_VBAT))
  {
      
    tmpADC_Common->CCR |= ADC_CCR_VBATE;
  }

    
  if ((hadc->Instance == ADC1) && ((sConfigInjected->InjectedChannel == ADC_CHANNEL_TEMPSENSOR) || (sConfigInjected->InjectedChannel == ADC_CHANNEL_VREFINT)))
  {
      
    tmpADC_Common->CCR |= ADC_CCR_TSVREFE;
  }

    
  __HAL_UNLOCK(hadc);

    
  return HAL_OK;
}

  
HAL_StatusTypeDef HAL_ADCEx_MultiModeConfigChannel(ADC_HandleTypeDef *hadc, ADC_MultiModeTypeDef *multimode)
{

  ADC_Common_TypeDef *tmpADC_Common;

    
  assert_param(IS_ADC_MODE(multimode->Mode));
  assert_param(IS_ADC_DMA_ACCESS_MODE(multimode->DMAAccessMode));
  assert_param(IS_ADC_SAMPLING_DELAY(multimode->TwoSamplingDelay));

    
  __HAL_LOCK(hadc);

    
    
    
  tmpADC_Common = ADC_COMMON_REGISTER(hadc);

    
  tmpADC_Common->CCR &= ~(ADC_CCR_MULTI);
  tmpADC_Common->CCR |= multimode->Mode;

    
  tmpADC_Common->CCR &= ~(ADC_CCR_DMA);
  tmpADC_Common->CCR |= multimode->DMAAccessMode;

    
  tmpADC_Common->CCR &= ~(ADC_CCR_DELAY);
  tmpADC_Common->CCR |= multimode->TwoSamplingDelay;

    
  __HAL_UNLOCK(hadc);

    
  return HAL_OK;
}

  

  
static void ADC_MultiModeDMAConvCplt(DMA_HandleTypeDef *hdma)
{
    
  ADC_HandleTypeDef *hadc = (ADC_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

    
  if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL | HAL_ADC_STATE_ERROR_DMA))
  {
      
    SET_BIT(hadc->State, HAL_ADC_STATE_REG_EOC);

      
      
      
      
      
      
    if (ADC_IS_SOFTWARE_START_REGULAR(hadc)                   &&
        (hadc->Init.ContinuousConvMode == DISABLE)            &&
        (HAL_IS_BIT_CLR(hadc->Instance->SQR1, ADC_SQR1_L) ||
         HAL_IS_BIT_CLR(hadc->Instance->CR2, ADC_CR2_EOCS)))
    {
        
        
        
        
      __HAL_ADC_DISABLE_IT(hadc, ADC_IT_EOC);

        
      CLEAR_BIT(hadc->State, HAL_ADC_STATE_REG_BUSY);

      if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_INJ_BUSY))
      {
        SET_BIT(hadc->State, HAL_ADC_STATE_READY);
      }
    }

      
    HAL_ADC_ConvCpltCallback(hadc);
  }
  else
  {
      
    hadc->DMA_Handle->XferErrorCallback(hdma);
  }
}

  
static void ADC_MultiModeDMAHalfConvCplt(DMA_HandleTypeDef *hdma)
{
  ADC_HandleTypeDef *hadc = (ADC_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;
    
  HAL_ADC_ConvHalfCpltCallback(hadc);
}

  
static void ADC_MultiModeDMAError(DMA_HandleTypeDef *hdma)
{
  ADC_HandleTypeDef *hadc = (ADC_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;
  hadc->State = HAL_ADC_STATE_ERROR_DMA;
    
  hadc->ErrorCode |= HAL_ADC_ERROR_DMA;
  HAL_ADC_ErrorCallback(hadc);
}

  

#endif   
  

  

