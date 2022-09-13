/*
 * API_delay.c
 *
 *  Created on: 6 sep. 2022
 *      Author: lucas
 */



#include "API_delay.h"

/**
 * @brief  Initialize Non-blocking delay structure
 * @param  delay: pointer to a defined delay structure
 * @param  duration: duration of the delay in ms
 * @retval None
 */
void delayInit( delay_t * delay, tick_t duration)
{
	if(delay == NULL || duration > MAX_DELAY) Error_Handler();
	delay->duration = duration;
	delay->running = false;
	delay->startTime = 0;
	return;
}

/**
 * @brief  Reads the status of the delay timer
 * @param  delay: pointer to a defined delay structure
 * @retval delay ended
 */
bool_t delayRead( delay_t * delay )
{
	if(delay == NULL) Error_Handler();
	if(!delay->running)
	{
		delay->running = true;
		delay->startTime = HAL_GetTick();
		return false;
	}
	else if(delay->startTime + delay->duration <= HAL_GetTick() && delay->duration < HAL_GetTick())
	{
		delay->startTime = HAL_GetTick();
		return true;
	}
	else return false;
}

/**
 * @brief  Overwrites the current delay duration
 * @param  delay: pointer to a defined delay structure
 * @param  duration: duration of the delay in ms
 * @retval None
 */
void delayWrite( delay_t * delay, tick_t duration )
{
	if(delay == NULL || duration > MAX_DELAY) Error_Handler();
	if(delay == NULL) Error_Handler();
	delay->duration = duration;
	return;
}


/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void)
{
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1)
	{
	}
}
