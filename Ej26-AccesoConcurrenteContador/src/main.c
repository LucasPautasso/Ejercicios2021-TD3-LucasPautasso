#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"
#include "pulsador.h"

#define SALIDA1     GPIO_NUM_25
#define SALIDA2     GPIO_NUM_33
#define T_ESPERA_MS  40
#define T_ESPERA     pdMS_TO_TICKS(T_ESPERA_MS)
#define PROCESADORA 0
#define PROCESADORB 1
#define PERIODO_MS                    2000
#define PERIODO2          pdMS_TO_TICKS(PERIODO_MS)


extern int contador;

void tareaDestello( void* taskParmPtr ); //Prototipo de la función de la tarea
void tareaDestello2( void* taskParmPtr );


void app_main()
{
    // Crear tarea en freeRTOS
    // Devuelve pdPASS si la tarea fue creada y agregada a la lista ready
    // En caso contrario devuelve pdFAIL.
    inicializarPulsador();

    BaseType_t res = xTaskCreatePinnedToCore(
    	tareaDestello,                     	// Funcion de la tarea a ejecutar
        "tareaDestello",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE, 		    // Cantidad de stack de la tarea
        NULL,                          	    // Parametros de tarea
        tskIDLE_PRIORITY+1,         	    // Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL,                          		// Puntero a la tarea creada en el sistema
        PROCESADORA
    );

    BaseType_t res1 = xTaskCreatePinnedToCore(
    	tareaDestello2,                     // Funcion de la tarea a ejecutar
        "tareaDestello2",   	            // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE, 		    // Cantidad de stack de la tarea
        NULL,                          	    // Parametros de tarea
        tskIDLE_PRIORITY+1,         	    // Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL,                          		// Puntero a la tarea creada en el sistema
        PROCESADORA
    );

    // Gestion de errores
	if(res == pdFAIL)
	{
		printf( "Error al crear la tarea.\r\n" );
		while(true);					    // si no pudo crear la tarea queda en un bucle infinito
	}

    if(res1 == pdFAIL)
	{
		printf( "Error al crear la tarea.\r\n" );
		while(true);					    // si no pudo crear la tarea queda en un bucle infinito
	}
}

// Implementacion de funcion de la tarea
void tareaDestello( void* taskParmPtr )
{
    // ---------- Configuraciones ------------------------------
    gpio_pad_select_gpio(SALIDA1);
    gpio_set_direction(SALIDA1, GPIO_MODE_OUTPUT);

    TickType_t dif;
    
    //TickType_t xPeriodicity = PERIODO;                          // Tarea periodica cada 1000 ms
    TickType_t xLastWakeTime = xTaskGetTickCount();


    // ---------- Bucle infinito --------------------------
    while( true )
    {
        //dif = contador;
        dif = pdMS_TO_TICKS(contador);

        if( dif > 0 )
        {
            /*if ( dif > PERIODO )
            {
                dif = PERIODO;
            }*/
            gpio_set_level( SALIDA1, 1 );
            vTaskDelay( dif/2 );
            gpio_set_level( SALIDA1, 0 );
            vTaskDelayUntil( &xLastWakeTime, dif );
        }
        else
        {
            vTaskDelay( T_ESPERA );
        }

    }
}


void tareaDestello2( void* taskParmPtr )
{
    // ---------- Configuraciones ------------------------------
    gpio_pad_select_gpio(SALIDA2);
    gpio_set_direction(SALIDA2, GPIO_MODE_OUTPUT);

    TickType_t dif2;
    
    //TickType_t xPeriodicity = PERIODO2;                          // Tarea periodica cada 1000 ms
    TickType_t xLastWakeTime = xTaskGetTickCount();


    // ---------- Bucle infinito --------------------------
    while( true )
    {
        //dif = contador;
        dif2 = pdMS_TO_TICKS(contador);

        if( dif2 > 0 )
        {
            /*if ( dif2 > PERIODO2 )
            {
                dif = PERIODO;
            }*/
            gpio_set_level( SALIDA2, 1 );
            vTaskDelay( dif2*2 );
            gpio_set_level( SALIDA2, 0 );
            vTaskDelayUntil( &xLastWakeTime, PERIODO2 );
        }
        else
        {
            vTaskDelay( T_ESPERA );
        }

    }
}