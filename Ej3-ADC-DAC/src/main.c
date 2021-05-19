#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <driver/adc.h>
#include <driver/dac.h>
#include "../driver/include/driver/gpio.h"

#define N_LED  3
int led [N_LED] = {GPIO_NUM_25, GPIO_NUM_33, GPIO_NUM_32};

void app_main()
{
    adc1_config_width(ADC_WIDTH_12Bit);                         // configura la resolución 
    adc1_config_channel_atten (ADC1_CHANNEL_6 ,ADC_ATTEN_11db); // configura la atenuación del ADC1
   
    adc2_config_channel_atten (ADC2_CHANNEL_4, ADC_ATTEN_11db); // configura la atenuación del ADC2
    
    for (int i=0; i<N_LED; i++)
    {
        gpio_pad_select_gpio(led[i]);
	    gpio_set_direction(led[i], GPIO_MODE_OUTPUT);
    }
    
    dac_output_enable(DAC_CHANNEL_2);

    while(true)
    {
        int lectura = adc1_get_raw(ADC1_CHANNEL_6);     // Obtiene el valor de señal en la entrada
        //printf("El valor del ADC1 es %d\n",lectura);    // Muestra el valor en la terminal    

        // VÚMETRO
        if (lectura > 1024)
        {
            gpio_set_level (led[0], 1);
        }
        else         
        {
            gpio_set_level (led[0], 0);
        }

        if (lectura > 2048)
        {
            gpio_set_level (led[1], 1);
        }
        else         
        {
            gpio_set_level (led[1], 0);
        }

        if (lectura > 3096)
        {
            gpio_set_level (led[2], 1);
        }
        else         
        {
            gpio_set_level (led[2], 0);
        }

        // Control de brillo
        dac_output_voltage(DAC_CHANNEL_2,(lectura*255/4095));     //0 y 255 DAC -- 8 bit -- va de 0 V a VDA (pin de alimentacion analogico) 
                                                                    //0 y 4095 ADC

        //int lectura2 = 0;
        //adc2_get_raw(ADC2_CHANNEL_4, ADC_WIDTH_12Bit, &lectura2);
        //printf("El valor del ADC2 es %d\n", lectura2);

        vTaskDelay(500/portTICK_PERIOD_MS);             // Tiempo entre mediciones
    }

}