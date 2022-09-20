/*
 * API_debounce.c
 *
 *  Created on: 13 sep. 2022
 *      Author: lucas
 */

#include "API_debounce.h"
#include "API_delay.h"

typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
} debounceState_t;


static debounceState_t FSM_state;
static bool btnPressed = false;
static delay_t debounceDelay;
static void Debouncer_Error_Handler(void);
static void buttonPressed();
static void buttonReleased();

/**
 * @brief  Initializes FSM
 * @param  None
 * @retval None
 */
void debounceFSM_init()
{
	delayInit(&debounceDelay, DEB_DELAY);
	FSM_state = BUTTON_UP;
}

/**
 * @brief  Updates FSM
 * @param  None
 * @retval None
 */
void debounceFSM_update()
{
	switch(FSM_state)
	{
		case BUTTON_UP:
		{
			if(BSP_PB_GetState(BUTTON_USER))
			{
				FSM_state = BUTTON_FALLING;
				delayRead(&debounceDelay);
			}
			break;
		}
		case BUTTON_FALLING:
		{
			if(delayRead(&debounceDelay))
			{
				if(BSP_PB_GetState(BUTTON_USER))
				{
					FSM_state = BUTTON_DOWN;
					buttonPressed();
				}
				else FSM_state = BUTTON_UP;
			}
			break;
		}
		case BUTTON_DOWN:
		{
			if(!BSP_PB_GetState(BUTTON_USER))
			{
				FSM_state = BUTTON_RAISING;
				delayRead(&debounceDelay);
			}
			break;
		}
		case BUTTON_RAISING:
		{
			if(delayRead(&debounceDelay))
			{
				if(!BSP_PB_GetState(BUTTON_USER))
				{
					FSM_state = BUTTON_UP;
					buttonReleased();
				}
				else FSM_state = BUTTON_DOWN;
			}
			break;
		}
		default:
		{
			Debouncer_Error_Handler();
			break;
		}
	}


}

/**
 * @brief  Callback when a button pressed event has been confirmed
 * @param  None
 * @retval None
 */
static void buttonPressed()
{
	btnPressed = true;
	return;
}

/**
 * @brief  Callback when a button released event has been confirmed
 * @param  None
 * @retval None
 */
static void buttonReleased()
{
	return;
}

/**
 * @brief  Function that tells if there is a "button pressed" event that hasn't been recognized yet
 * @param  None
 * @retval True if there has been an event or false if not
 */
bool readKey()
{
	if(btnPressed)
	{
		btnPressed = false;
		return true;
	}
	else return false;

}

/**
 * @brief  Private error handler
 * @param  None
 * @retval none
 */
static void Debouncer_Error_Handler(void)
{
	while (1)
	{
	}
}
