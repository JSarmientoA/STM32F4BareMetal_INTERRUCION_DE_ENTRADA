#include "stm32f4xx.h"

#define TMR2_ON		(1U<<0)
#define TMR3_ON		(1U<<1)
#define CR1_CEN		(1U<<0)
#define OC_TOGLE	((1U<<4)|(1U<<5)|(0U<<6))
#define CCER_CC1E	(1U<<0)
#define GPIOAEN		(1U<<0)
#define CC1S		(1U<<0)
#define CC1E		(1U<<0)


void ConfitGPIOA5y6EnModoAlternativos(void){

	//1. Habilitar el acceso a reloj al GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	/*Configure PA5 en modo alternativo*/
	GPIOA -> MODER &=  ~(1U<<10);
	GPIOA -> MODER |=	(1U<<11);

	/*Configura el tipo de funcion alternativo TIMER2_CH1 (AF01),registro AFRL*/
	GPIOA->AFR[0] |=  (1U<<20);
	GPIOA->AFR[0] &= (~(1U<<23)|~(1U<<22)|~(1U<<21));


	/*Configure PA6 en modo alternativo*/
	GPIOA -> MODER &=  ~(1U<<12);
	GPIOA -> MODER |=	(1U<<13);

	/*Configura el tipo de funcion alternativo TIMER3_CH1 (AF02),registro AFRL*/
	GPIOA->AFR[0] |=  (1U<<25);
	GPIOA->AFR[0] &= (~(1U<<27)|~(1U<<26)|~(1U<<24));

}


void tim2_1hz(void){

	/*Activar (Conectar) el reloj para el temporizador*/
	RCC->APB1ENR |= TMR2_ON;

	/*Estableser el valor del prescalador*/
	TIM2->PSC=1600-1;/// Es escribe de esta manera porque se cuenta desde cero.

	/*El registro PSC es un prescalizador del reloj principal por lo que cualquier freciencia
	 *a la que este trabajando el reloj del sistema sera dividida el valor cargado en este registro. Esto ese:
	 *
	 *                    CLK_SYS  (Reloj del sistema)
	 * Prescalizador  =  ---------
	 *                      PSC    (Valor cargado en el registro PSC*/

	/*Valor de la recarga automatica*/
	TIM2->ARR=10000-1;

	/*El registro ARR es un contador (Progresivo o Regresivo) previo su valor de carga.
	 * Cuando este termina de contar activa una bandera*/

	/*Borrar el contador del temporizacor*/
	TIM2->CNT=0;//Borrar el valor acual del contador

	/*Este registro muesta el valor acual del contador*/

	/*Habilita el temporizador*/
	TIM2->CR1 |= CR1_CEN;//El registro CR1 es un registro de control
}


void tim2_modo_comparacion(void){

	/*Activar (Conectar) el reloj para el temporizador*/
	RCC->APB1ENR |= TMR2_ON;

	/*Estableser el valor del prescalador*/
	TIM2->PSC=1600-1;/// Es escribe de esta manera porque se cuenta desde cero.

	/************************PRESCALIZADOR***********************
	 * El registro PSC es un prescalizador del reloj principal por lo que cualquier freciencia
	 *a la que este trabajando el reloj del sistema sera dividida el valor cargado en este registro. Esto ese:
	 *
	 *                    CLK_SYS  (Reloj del sistema)
	 * Prescalizador  =  ---------
	 *                      PSC    (Valor cargado en el registro PSC*/

	/*Valor de la recarga automatica*/
	TIM2->ARR=10000-1;

	/*El registro ARR es un contador (Progresivo o Regresivo) previo su valor de carga.
	 * Cuando este termina de contar activa una bandera*/

	/*Configuracion de la salida en modo comparación*/
	TIM2->CCMR1 |= OC_TOGLE;
	/*Esta habilitación se realiza en el registro CCMR1 bits 4 al seis segun el OCxM donde x
	 * correspnde al canal del timer*/

	/*Habilitación del canal uno del timer2 en modo comparación */
	TIM2->CCER |= CCER_CC1E;

	/*Borrar el contador del temporizacor*/
	TIM2->CNT=0;//Borrar el valor acual del contador

	/*Este registro muesta el valor actual del contador*/

	/*Habilita el temporizador*/
	TIM2->CR1 = CR1_CEN;//El registro CR1 es un registro de control
}

void Tim3ModoCapturaEntrada(void){

	/*Activar (Conectar) el reloj para el temporizador*/
	RCC->APB1ENR |= TMR3_ON;

	/*Estableser el valor del prescalador*/
	TIM3->PSC=160000-1;/// Es escribe de esta manera porque se cuenta desde cero.

	/************************PRESCALIZADOR***********************
	 * El registro PSC es un prescalizador del reloj principal por lo que cualquier freciencia
	 *a la que este trabajando el reloj del sistema sera dividida el valor cargado en este registro. Esto ese:
	 *
	 *                    CLK_SYS  (Reloj del sistema)
	 * Prescalizador  =  ---------
	 *                      PSC    (Valor cargado en el registro PSC*/

	/*Canal uno del TIMER3 en modo de entrada*/
	TIM3->CCMR1 = CC1S;

	/*Captura en el borde asendente*/
	TIM3->CCER |= CC1E;

	/*Activación del TIMER3*/

	TIM3->CR1 = CR1_CEN;//El registro CR1 es un registro de control

}




















