#ifndef LED_H //chequea que otro archivo no llame a led.h
#define LED_H

#include "driver/gpio.h"

gpio_int_type_t LedR = 32;
gpio_int_type_t LedA = 26;
gpio_int_type_t LedV = 25;

//void configurarLed(int LedR, int LedA, int LedV);
void configurarLed(gpio_int_type_t ledR, gpio_int_type_t ledA, gpio_int_type_t ledV); //especifica en que pines conectar cada led: ROJO, AMARILLO, VERDE

void prenderLed(char led);

void apagarLed(char led);

#endif