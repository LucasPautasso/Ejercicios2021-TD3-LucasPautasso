#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/semaforo.h"
#include "../include/led.h"

// DEFINICIÓN DE PINES DE LA PLACA PARA CADA COLOR DE LED
#define LED_VERDE GPIO_NUM_25       //LED VERDE     --> PIN 25
#define LED_AMARILLO GPIO_NUM_33    //LED AMARILLO  --> PIN 33
#define LED_ROJO GPIO_NUM_32        //LED ROJO      --> PIN 32

// DEFINICIÓN DE TIEMPOS DE ESTADOS
#define T_ROJO 1000
#define T_AMARILLO 200
#define T_VERDE 1000

// Tipo de datos para la variable de estados
typedef enum{
    ROJO,
    ROJO_AMARILLO,
    AMARILLO,
    VERDE
} estadoMEF_t;

// Variable de estado (global)
estadoMEF_t estadoActual;
int contador;

// Función Inicializar MEF
void InicializarSemaforo(void)
{
    configurarLed(LED_ROJO, LED_AMARILLO, LED_VERDE);
	estadoActual = ROJO;
    contador = 0;
}



// Función Actualizar MEF
void ActualizarSemaforo(void)
{
	switch (estadoActual) 
    {
		case ROJO:
        {
            // Actualizar salida del estado
            prenderLed('R');
            apagarLed('A');
            apagarLed('V');
    		// Chequear condiciones de transición de estado
			if(contador == T_ROJO){
				// Cambiar a otro estado
				 estadoActual = ROJO_AMARILLO;
                 contador = 0;
			}
            contador ++;
		}
		break;
		
        case ROJO_AMARILLO:
        {
			// Actualizar salida del estado
            prenderLed('R');
            prenderLed('A');
            apagarLed('V');
    		// Chequear condiciones de transición de estado
			if(contador == T_AMARILLO){
				// Cambiar a otro estado
				 estadoActual = VERDE;
                 contador = 0;
			}
            contador ++;
		}
		break;

		case VERDE:
        {
			// Actualizar salida del estado
            apagarLed('R');
            apagarLed('A');
            prenderLed('V');
    		// Chequear condiciones de transición de estado
			if(contador == T_VERDE){
				// Cambiar a otro estado
				 estadoActual = AMARILLO;
                 contador = 0;
			}
            contador ++;
		}
		break;

        case AMARILLO:
        {
			// Actualizar salida del estado
            apagarLed('R');
            prenderLed('A');
            apagarLed('V');
    		// Chequear condiciones de transición de estado
			if(contador == T_AMARILLO){
				// Cambiar a otro estado
				 estadoActual = ROJO;
                 contador = 0;
			}
            contador ++;
		}
		break;

		default:
        {
			//Si cae en un estado no valido, reinicio
            InicializarSemaforo();
		}
		break;
	}	
}

