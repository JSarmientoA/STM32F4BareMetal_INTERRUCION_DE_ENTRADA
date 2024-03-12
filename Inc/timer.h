/*
 * timer.h
 *
 *  Created on: Jul 12, 2023
 *      Author: juan
 */

#ifndef TIMER_H_
#define TIMER_H_
void tim2_1hz(void);
void tim2_modo_comparacion(void);
void ConfitGPIOA5y6EnModoAlternativos(void);
void Tim3ModoCapturaEntrada(void);
#define SR_UIF 	(1U<<0)
#define CC1IF	(1U<<1)
#endif /* TIMER_H_ */
