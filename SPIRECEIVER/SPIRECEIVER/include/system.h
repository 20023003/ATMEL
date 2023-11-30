

/**
 * \file
 *
 * \brief Tinymega System related support
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 */

/**
 * \addtogroup doc_driver_system
 *
 * \section doc_driver_system_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

#ifndef SYSTEM_INCLUDED
#define SYSTEM_INCLUDED

#include "port.h"
#include <protected_io.h>
#ifdef __cplusplus
extern "C" {
#endif

#define MCU_RESET_CAUSE_POR (1 << PORF)
#define MCU_RESET_CAUSE_EXT (1 << EXTRF)
#define MCU_RESET_CAUSE_BOR (1 << BORF)
#define MCU_RESET_CAUSE_WDT (1 << WDRF)

static inline void mcu_init(void)
{

	/* Set all pins to low power mode */
	PORTA_set_port_dir(0xff, PORT_DIR_OFF);
	PORTB_set_port_dir(0xff, PORT_DIR_OFF);
	PORTC_set_port_dir(0xff, PORT_DIR_OFF);
	PORTD_set_port_dir(0xff, PORT_DIR_OFF);
	PORTE_set_port_dir(0xff, PORT_DIR_OFF);
	PORTF_set_port_dir(0xff, PORT_DIR_OFF);
	PORTG_set_port_dir(0x1f, PORT_DIR_OFF);
}

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_INCLUDED */
