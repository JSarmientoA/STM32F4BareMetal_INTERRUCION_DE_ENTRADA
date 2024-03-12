#include "exit.h"
#define GPIOCEN		(1U<<2)
#define SYSCFGEN	(1U <<14)
/*
 * Se genrara una interrupción (Interrupcion extrna)cuando se presione el pulsador PC13.
 * La interrupcion se genra co un flanco asensdente o
 * desendente.
 */



int pc13_exitinti(void)
{
	/*0. Desactiva la interrución global (Paso opcional)*/
	__disable_irq();
    /*1. Habilitar el accero al reloj para el GPIO*/
	RCC->AHB1ENR |=  GPIOCEN; //Habilitacion del bit 2 (1) en el registro AHB1ENR para conectar el reloj al puerto C
	/*2. Esptablese el pin PC13 como entrada*/
	GPIOC->MODER &= ~((1U<<26)|(1U<<27));//Habilitacion de los bit 26(0) y 27(0) en el registro MODER del periferico GPIOC
	/*3. Habilitar el acceso al reloj para el modulo SYSCFG. Esete es el modlo donde se encuentra el exit (Interrupcion extrna)*/
	RCC->APB2ENR |= SYSCFGEN;// Habilitación del bit 2 (1) en el registro APB2ENR en el periferico RCC
	/*4. Seleccion del PORTC para conectarnos al PC13 conectar el exti13 (Interrupcion extrna)*/
	SYSCFG->EXTICR[3] |=(1U<<5);//El registro EXTICR4=EXTICR[3] devido a que la estructura donde esta contenido lo define
	                            // como una matriz por lo que la pocision 0 es igual a EXTICR1 y asi sicesivamente. El registro
	                            //EXTICR tiene todas sus posiciones = 0, por l que solo se afecto el bit requerido.
	/*5. Desenmascarar exit*/
	EXTI->IMR |=(1U<<13);//Habilitación del bit 13 (1) en el registro EMR en el periferico EXTI
	/*6. Activacion por flanco desendente*/
	EXTI->FTSR |=(1U<<13);//Habilitación del bit 13 (1) en el registro FTSR en el periferico EXTI
	/*7. Habilitacion de la línea exit13 en el controlador de interrupción (NVIC)*/
	NVIC_EnableIRQ(EXTI15_10_IRQn);  //;NVIC->IP[40]=2<<4;
	/*8. Activacción de la interrución global (solo si realizo el paso 0)*/
	__enable_irq();
}

