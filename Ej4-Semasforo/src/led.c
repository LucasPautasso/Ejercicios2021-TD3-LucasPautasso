#include "../include/led.h"
#include "driver/gpio.h"

static int ledRojo, ledAmarillo, ledVerde; //variables solamente accesibles en este archivo

// IMPLEMENTACIÓN DE FUNCIÓN
void configurarLed(gpio_int_type_t ledR, gpio_int_type_t ledA, gpio_int_type_t ledV)    //ESTABLECE LOS PINES COMO SALIDA
{
    ledRojo = ledR;
    ledAmarillo = ledA;
    ledVerde = ledV;
    gpio_pad_select_gpio(ledRojo);
    gpio_set_direction(ledRojo, GPIO_MODE_OUTPUT);      //CONFIGURA COMO SALIDA PIN DONDE ESTA LED ROJO
    gpio_pad_select_gpio(ledAmarillo);
    gpio_set_direction(ledAmarillo, GPIO_MODE_OUTPUT);
    gpio_pad_select_gpio(ledVerde);
    gpio_set_direction(ledVerde, GPIO_MODE_OUTPUT);
}

void prenderLed(char led)       //ENCIENDE LED SEGUN ARGUMENTO
{
    switch (led)
    {
    case 'R':
        gpio_set_level(ledRojo,1);
        break;
    case 'A':
        gpio_set_level(ledAmarillo,1);
        break;
    case 'V':
        gpio_set_level(ledVerde,1);
        break;
    default:
        break;
    }
}

void apagarLed(char led)        //APAGA LED SEGUN ARGUMENTO
{
    switch (led)
    {
    case 'R':
        gpio_set_level(ledRojo,0);
        break;
    case 'A':
        gpio_set_level(ledAmarillo,0);
        break;
    case 'V':
        gpio_set_level(ledVerde,0);
        break;
    default:
        break;
    }
}