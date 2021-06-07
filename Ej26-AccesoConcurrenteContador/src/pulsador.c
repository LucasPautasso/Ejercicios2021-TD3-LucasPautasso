/*==================[ Inclusiones ]============================================*/
#include "pulsador.h"

/*==================[ Definiciones ]===================================*/

#define T_REBOTE_MS   40
#define T_REBOTE pdMS_TO_TICKS(T_REBOTE_MS)
#define SALIDA_P1   GPIO_NUM_32
//#define SALIDA_P2   GPIO_NUM_32

/*==================[Prototipos de funciones]======================*/

static void errorPulsador( void );
//static void errorPulsador1( void );
static void boton0Presionado( void );
static void boton1Presionado( void );
//static void botonLiberado( void );

void tareaPulsador( void* taskParmPtr );

/*==================[Variables]==============================*/
gpio_int_type_t pulsadorPines[2] = {GPIO_NUM_27, GPIO_NUM_26};

pulsadorInfo pulsador0;
pulsadorInfo pulsador1;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;        //Inicializa el spinlock desbloqueado

int contador = 100;
int lim_inferior = 100;
int lim_superior = 900;

/*==================[Implementaciones]=================================*/

/*TickType_t obtenerDiferencia()
{
    TickType_t tiempo;
    portENTER_CRITICAL(&mux);
    tiempo = pulsadorA.diferenciaTiempo;
    portEXIT_CRITICAL(&mux);
    return tiempo;
}

void borrarDiferencia( void )
{
    portENTER_CRITICAL(&mux);
    pulsadorA.diferenciaTiempo = TIEMPO_NO_VALIDO;
    portEXIT_CRITICAL(&mux);
}
*/

void inicializarPulsador( void )
{
    pulsador0.tecla             = pulsadorPines[0];
    pulsador0.estado            = ALTO;                     //Estado inicial
    //pulsadorA.tiempoBajo        = TIEMPO_NO_VALIDO;
    //pulsadorA.tiempoAlto        = TIEMPO_NO_VALIDO;
    //pulsadorA.diferenciaTiempo  = TIEMPO_NO_VALIDO;
    pulsador1.tecla             = pulsadorPines[1];
    pulsador1.estado            = ALTO;

//--------------CONFIGURACIÓN DE PIN DEL PULSADOR------------------------

    gpio_pad_select_gpio(pulsador0.tecla);
    gpio_set_direction(pulsador0.tecla, GPIO_MODE_INPUT);
    gpio_set_pull_mode(pulsador0.tecla, GPIO_PULLDOWN_ONLY); //Habilita resistencia de PULLDOWN interna

    gpio_pad_select_gpio(pulsador1.tecla);
    gpio_set_direction(pulsador1.tecla, GPIO_MODE_INPUT);
    gpio_set_pull_mode(pulsador1.tecla, GPIO_PULLDOWN_ONLY);

    gpio_pad_select_gpio(SALIDA_P1);
    gpio_set_direction(SALIDA_P1, GPIO_MODE_OUTPUT);

    /*gpio_pad_select_gpio(SALIDA_P2);
    gpio_set_direction(SALIDA_P2, GPIO_MODE_OUTPUT);
    */

    // Crear tareas en freeRTOS
    BaseType_t res = xTaskCreatePinnedToCore(
    	tareaPulsador,                     	// Funcion de la tarea a ejecutar
        "tareaPulsador",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE*2, 		// Cantidad de stack de la tarea
        NULL,                          	    // Parametros de tarea
        tskIDLE_PRIORITY+1,         	    // Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL,                          		// Puntero a la tarea creada en el sistema
        1
    );

    // Gestion de errores
	if(res == pdFAIL)
	{
		printf( "Error al crear la tarea.\r\n" );
		while(true);					    // si no pudo crear la tarea queda en un bucle infinito
	}
}


static void errorPulsador( void )
{
    portENTER_CRITICAL(&mux);
    pulsador0.estado = ALTO;
    pulsador1.estado = ALTO;
    portEXIT_CRITICAL(&mux);
}

// pulsador Update State Function
void actualizarPulsador0()
{
    switch( pulsador0.estado )          // Consulta estado de pulsador 0
    {
        case BAJO:
            if( gpio_get_level( pulsador0.tecla ) ){
                pulsador0.estado = ASCENDENTE;
            }
            break;

        case ASCENDENTE:
            if( gpio_get_level( pulsador0.tecla ) ){
                pulsador0.estado = ALTO;
                boton0Presionado();
            }
            else{
                pulsador0.estado = BAJO;
            }
            break;

        case ALTO:
            if( !gpio_get_level( pulsador0.tecla ) ){
                pulsador0.estado = DESCENDENTE;
            }
            break;

        case DESCENDENTE:
            if( !gpio_get_level( pulsador0.tecla ) ){
                pulsador0.estado = BAJO;
                //botonLiberado();
            }
            else{
                pulsador0.estado = ALTO;
            }
            break;

        default:
            errorPulsador();
            break;
    }
}

void actualizarPulsador1()
{
    switch( pulsador1.estado )              //Consulta estado de pulsador 1
    {
        case BAJO:
            if( gpio_get_level( pulsador1.tecla ) ){
                pulsador1.estado = ASCENDENTE;
            }
            break;

        case ASCENDENTE:
            if( gpio_get_level( pulsador1.tecla ) ){
                pulsador1.estado = ALTO;
                boton1Presionado();
            }
            else{
                pulsador1.estado = BAJO;
            }
            break;

        case ALTO:
            if( !gpio_get_level( pulsador1.tecla ) ){
                pulsador1.estado = DESCENDENTE;
            }
            break;

        case DESCENDENTE:
            if( !gpio_get_level( pulsador1.tecla ) ){
                pulsador1.estado = BAJO;
                //botonLiberado();
            }
            else{
                pulsador1.estado = ALTO;
            }
            break;

        default:
            errorPulsador();
            break;
    }
}

/* accion del evento tecla pulsada */
static void boton0Presionado()
{
    //TickType_t conteoTicksActuales = xTaskGetTickCount();   //Medimos el tiempo en ticks desde que inició el scheduler
    if (lim_inferior <= contador << lim_superior )
    {
        portENTER_CRITICAL(&mux);
        contador = contador + 100;
        if (contador > lim_superior)
        {
            contador = lim_superior;
        }
        portEXIT_CRITICAL(&mux);
        gpio_set_level( SALIDA_P1, 1 );
        vTaskDelay(T_REBOTE*5);
        gpio_set_level( SALIDA_P1, 0 );
    }
}

static void boton1Presionado()
{
    //TickType_t conteoTicksActuales = xTaskGetTickCount();   //Medimos el tiempo en ticks desde que inició el scheduler
    if (lim_inferior << contador <= lim_superior)
    {
        portENTER_CRITICAL(&mux);
        contador = contador - 100;
        if (contador < lim_inferior)
        {
            contador = lim_inferior;
        }
        portEXIT_CRITICAL(&mux);
        gpio_set_level( SALIDA_P1, 1 );
        vTaskDelay(T_REBOTE*5);
        gpio_set_level( SALIDA_P1, 0 );
    }
}

/* accion de el evento de tecla liberada 
static void botonLiberado()
{
    TickType_t conteoTicksActuales = xTaskGetTickCount();   //Medimos el tiempo en ticks desde que inició el scheduler
    gpio_set_level( SALIDA_PRUEBA, 0 );         //para tener una referencia en el debug
    portENTER_CRITICAL(&mux);
    pulsadorA.tiempoAlto    = conteoTicksActuales;
    pulsadorA.diferenciaTiempo  = pulsadorA.tiempoAlto - pulsadorA.tiempoBajo; //Da el tiempo que el pulsador estuvo en estado alto
    portEXIT_CRITICAL(&mux);
}
*/

void tareaPulsador( void* taskParmPtr )
{
    while( true )
    {
        actualizarPulsador0();
        vTaskDelay( T_REBOTE );
        actualizarPulsador1();
        vTaskDelay( T_REBOTE );
    }
}