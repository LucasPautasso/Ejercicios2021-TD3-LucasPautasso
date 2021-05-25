#include "../include/led.h"
#include "../include/semasforo.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define T_VERDE		300
#define T_AMARILLO	100
#define T_ROJO		500

void iniciarSemasforo()
{
    configurarLed(LED_ROJO, LED_AMARILLO, LED_VERDE);
}

void actualizarSemasforo()
{
    prenderLed ('R');
    vTaskDelay(T_ROJO);
    prenderLed ('A');
    vTaskDelay(T_AMARILLO);
    apagarLed ('R');
    apagarLed ('A');
    prenderLed ('V');
    vTaskDelay(T_VERDE);
    apagarLed ('V');
    prenderLed ('A');
    vTaskDelay(T_AMARILLO);
    apagarLed ('A');

}