#ifndef LED_H //chequea que otro archivo no llame a led.h
#define LED_H

#define VERDE GPIO_NUM_25
#define AMARILLO 1
#define ROJO 2

int LedR = 32;
int LedA = 26;
int LedV = 25;

void configurarLed(int LedR, int LedA, int LedV);

void prenderLed();
void apagarLed();

#endif