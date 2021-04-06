#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/semasforo.h"
#include "../include/led.h"



void app_main()
{
    configurarLed (LedR, LedA, LedV);
    iniciarSemasforo ();

    while(1)
    {
        actualizarSemasforo();
    }

}