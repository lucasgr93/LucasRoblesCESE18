/*
 * API_debounce.h
 *
 *  Created on: 13 sep. 2022
 *      Author: lucas
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#define DEB_DELAY 40 //Debouncing time in ms

void debounceFSM_init();
void debounceFSM_update();
void buttonPressed();
void buttonReleased();
bool readKey();


#endif /* API_INC_API_DEBOUNCE_H_ */
