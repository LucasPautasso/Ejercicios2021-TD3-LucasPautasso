#ifndef LED_H //chequea que otro archivo no llame a led.h
#define LED_H

#include "driver/gpio.h"    // se incluye para utilizar las funciones de la librería gpio

// DECLARACÍON DE FUNCIONES
void configurarLed(gpio_int_type_t ledR, gpio_int_type_t ledA, gpio_int_type_t ledV);

void prenderLed(char led);

void apagarLed(char led);

#endif