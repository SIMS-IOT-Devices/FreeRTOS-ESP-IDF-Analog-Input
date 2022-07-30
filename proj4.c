// Receive analog input

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

void app_main(void)
{
    uint32_t voltage;

    // Configure ADC1 capture width
    // 12 bit decimal value from 0 to 4095
    adc1_config_width(ADC_WIDTH_BIT_12); 
    // Configure the ADC1 channel (ADC1_CHANNEL_6 - pin 34), and setting attenuation (ADC_ATTEN_DB_11)
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);

    while (1) 
    {
        // Take an ADC1 reading on a single channel (ADC1_CHANNEL_6 pin 34)
        // 11dB attenuation (ADC_ATTEN_DB_11) gives full-scale voltage 0 - 3.9V
        // 4053 ~ 3.86V
        voltage = adc1_get_raw(ADC1_CHANNEL_6); 
        printf("%d\n", voltage);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
