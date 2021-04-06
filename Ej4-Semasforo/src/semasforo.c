#include "../include/led.h"
#include "../include/semasforo.h"

void iniciarSemasforo()
{

}

void actualizarSemasforo()
{
    prenderLed (ROJO);
    vTaskDelay(50);
    prenderLed (AMARILLO);
    vTaskDelay(50);
    apagarLed (ROJO);
    apagarLed (AMARILLO);
    prenderLed (VERDE);
    vTaskDelay(50);
    apagarLed (VERDE);
    prenderLed (AMARILLO);
    vTaskDelay(50);
    apagarLed (AMARILLO);

}