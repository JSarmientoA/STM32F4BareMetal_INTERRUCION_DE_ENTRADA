/*
 * exit.h
 *
 *  Created on: Feb 13, 2024
 *      Author: juan
 */

#ifndef EXIT_H_
#define EXIT_H_
#include "stm32f4xx.h"// Inclusion de la familia stm32f4xx
int pc13_exitinti(void);
#define LINEA13		(1U<<13)

#endif /* EXIT_H_ */
