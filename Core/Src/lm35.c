#include "lm35.h"

extern ADC_HandleTypeDef hadc1;

float LM35_ReadTemp(void)
{
    uint32_t adc_value;
    float voltage;
    float temperature;

    HAL_ADC_Start(&hadc1);

    HAL_ADC_PollForConversion(&hadc1, 100);

    adc_value = HAL_ADC_GetValue(&hadc1);

    HAL_ADC_Stop(&hadc1);

    voltage = ((float)adc_value * 3.3f) / 4095.0f;

    temperature = voltage * 100.0f;

    return temperature;
}
