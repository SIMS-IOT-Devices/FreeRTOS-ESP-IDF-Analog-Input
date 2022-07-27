// Resive analog input

#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

// The ADC Characteristics structure stores the gain and offset factors of an ESP32 module’s ADC
static esp_adc_cal_characteristics_t adc1_chars;

void app_main(void)
{
    uint32_t voltage;

    // Call esp_adc_cal_characterize() to initialize the structure defined in esp_adc_cal_characteristics_t
    // ADC_ATTEN_DB_11 = 3 The input voltage of ADC will be reduced to about 1/3.6
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
    // Configure ADC1 capture width
    adc1_config_width(ADC_WIDTH_BIT_DEFAULT);
    // Configure the ADC1 channel (ADC1_CHANNEL_6 - pin 34), and setting attenuation (ADC_ATTEN_DB_11)
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);

    while (1) 
    {
        // Take an ADC1 reading on a single channel (ADC1_CHANNEL_6 pin 34)
        voltage = adc1_get_raw(ADC1_CHANNEL_6); 
        printf("%d\n", voltage);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}