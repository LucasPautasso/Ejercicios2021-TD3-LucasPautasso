#ifndef LED_H //chequea que otro archivo no llame a led.h
#define LED_H

#include "driver/gpio.h"    // se incluye para utilizar las funciones de la librería gpio

// DEFINICIÓN DE PINES DE LA PLACA PARA CADA COLOR DE LED
#define LED_VERDE GPIO_NUM_25       //LED VERDE     --> PIN 25
#define LED_AMARILLO GPIO_NUM_33    //LED AMARILLO  --> PIN 33
#define LED_ROJO GPIO_NUM_32        //LED ROJO      --> PIN 32


// DECLARACÍON DE FUNCIONES
void configurarLed(gpio_int_type_t ledR, gpio_int_type_t ledA, gpio_int_type_t ledV);

void prenderLed(char led);

void apagarLed(char led);

#endif