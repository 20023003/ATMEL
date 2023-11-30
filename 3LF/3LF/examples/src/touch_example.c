
/*============================================================================
Filename : touch_example.c
Project : QTouch Modular Library
Purpose : Provides sample code snippet to demonstrate how to process and get status from
          touch library.

This file is part of QTouch Modular Library example application.

Important Note: Do not edit this file manually.
                Use QTouch Configurator within Atmel Start to apply any
                modifications to this file.

Usage License: Refer license.h file for license information
Support: Visit http://www.microchip.com/support/hottopics.aspx
               to create MySupport case.

------------------------------------------------------------------------------
Copyright (c) 2021 Microchip. All rights reserved.
------------------------------------------------------------------------------
============================================================================*/

/*----------------------------------------------------------------------------
 *     include files
 *----------------------------------------------------------------------------*/
#include <atmel_start.h>
#include "touch_example.h"
/*----------------------------------------------------------------------------
 *   Extern variables
 *----------------------------------------------------------------------------*/
extern volatile uint8_t measurement_done_touch;

/*----------------------------------------------------------------------------
 *   Global variables
 *----------------------------------------------------------------------------*/
uint8_t key_status = 0;

/*----------------------------------------------------------------------------
 *   prototypes
 *----------------------------------------------------------------------------*/
void touch_status_display(void);

/*----------------------------------------------------------------------------
 *   function definitions
 *----------------------------------------------------------------------------*/

/*============================================================================
void touch_example(void)
------------------------------------------------------------------------------
Purpose: This function provides sample code snippet to process and check the
         status of touch library
Input  : none
Output : none
Notes  : The content on this function has to be copied to the main() function
         on main.c file.
============================================================================*/

void touch_example(void)
{

	/*
	 * This touch example project demonstrates the usage of QTouch Library firmware for developing touch applications.
	 * To enable sensor tuning, the associated debug information can further be monitored using Atmel Data Visualizer
	 * GUI.
	 *
	 * The following Atmel Start peripheral drivers have been used in this example project along with QTouch Library
	 * middleware.
	 * 1. System Clock - To set CPU clock.
	 * 2. Timer/RTC - To provide periodic scan interval to initiate touch measurement.
	 * 3. USART - To relay touch debug information via EDBG or mEDBG USB bridge to Atmel Data Visualizer GUI.
	 * 4. Global system interrupt should be enabled.
	 *
	 * Note: This is a sample file to provide reference on using touch status in a user application. This file is not
	 * linked to a project build.
	 */

	cpu_irq_enable(); /* Global Interrupt Enable */

	touch_process();
	if (measurement_done_touch == 1) {
		measurement_done_touch = 0;
		touch_status_display();
	}
}

/*============================================================================
void touch_status_display(void)
------------------------------------------------------------------------------
Purpose: Sample code snippet to demonstrate how to check the status of the
         sensors
Input  : none
Output : none
Notes  : none
============================================================================*/
void touch_status_display(void)
{
	key_status = get_sensor_state(0) & KEY_TOUCHED_MASK;
	if (0u != key_status) {
		// LED_ON
	} else {
		// LED_OFF
	}
	key_status = get_sensor_state(1) & KEY_TOUCHED_MASK;
	if (0u != key_status) {
		// LED_ON
	} else {
		// LED_OFF
	}
	key_status = get_sensor_state(2) & KEY_TOUCHED_MASK;
	if (0u != key_status) {
		// LED_ON
	} else {
		// LED_OFF
	}
	key_status = get_sensor_state(3) & KEY_TOUCHED_MASK;
	if (0u != key_status) {
		// LED_ON
	} else {
		// LED_OFF
	}
}