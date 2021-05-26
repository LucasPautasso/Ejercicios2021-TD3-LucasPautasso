#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/semaforo.h"
#include "../include/led.h"



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
    
	estadoActual = ROJO;
    contador = 0;
    // Resto de la inicializacion
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
			if(contador == 1000){
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
			if(contador == 200){
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
			if(contador == 1000){
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
			if(contador == 200){
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

