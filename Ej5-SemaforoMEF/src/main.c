/*
=========================================================================================
Autor: Lucas Pautasso - eMail: lucaspaut@gmail.com
Fecha: 25/05/2021
=========================================================================================
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/semaforo.h"
#include "../include/led.h"

#define T 10/portTICK_PERIOD_MS


// Programa principal
void app_main ()
{
	InicializarSemaforo();

	while(1)
    {
		ActualizarSemaforo();
        vTaskDelay(T);
	}
	//return 0;
}