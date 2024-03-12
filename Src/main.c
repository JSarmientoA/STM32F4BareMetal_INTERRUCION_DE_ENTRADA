#include <stdint.h>
#include <stdio.h> // Para poder usar printf()
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"
#include "exit.h"

#define GPIOAEN			(1U<<0)
#define PIN5			(1U<<5)//Poner un uno en la posicion 5
#define LED 			 PIN5


/*Este programa geera una interrupcion por el cambio de estado en el puerto PC13. Cuando se genra la interupcion se produce el encendido de un led*/
static void exit_callback(void);

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;
	//2. Configurar el PIN 5 como salida
	GPIOA -> MODER |=  (1U<<10);//poner un uno en la posicion dies |= es or igual
	GPIOA -> MODER &=~ (1U<<11);//poner un cero en la posicion once &=~ es and igual negado

	pc13_exitinti();
	uart2_rx_tx_init();
	printf("Estado inicial del led...\n\r");
	while(1){

	}
}

static void exit_callback(void){

	printf("Esatdo siguiente...\n\r");
	GPIOA ->ODR  ^= LED;

}

/*Codigo donde se genra la interrupcion*/
void EXTI15_10_IRQHandler(void){ // La funcion EXTI15_10_IRQHandler llama la interrupción
	if((EXTI->PR & LINEA13)!=0){//Validacion el estado del bit 13 del registro PR correpondiente al periferico EXTI  seccion de interrupciones y eventos
		/*Borrar la bandera del registro PR*/
		EXTI-> PR |=LINEA13; // Habilitacion del del bit 13 en uno (1) registro PR periferico EXTI
		/*Fragmento de codigo*/
		exit_callback();

	}
}













