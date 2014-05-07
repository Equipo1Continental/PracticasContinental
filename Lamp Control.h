/*============================================================================*/
/*                              TEAM 1				                          */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        Lamp_Control.h
* Instance:         RPL_1
* version:          1
* Created_by:       Mario Alberto Rivera González
* Date_created:     Thu March 03 00:50:20 2014
*=============================================================================*/
/* DESCRIPTION : Header file for Lamp Control                                 */
/*============================================================================*/
/* FUNCTION COMMENT : The functions turn on/off the parklamp and headlamp     */
/* according to SELECTOR position. It uses FREEDOM KL25Z128				      */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 03/04/2014  | 							                 |   Mario Rivera   */
/*============================================================================*/

#ifndef LAMP_CONTROL_H          /* To avoid double inclusion */
#define LAMP_CONTROL_H

/* Includes */
/* -------- */
#include "stdtypedef.h"
#include "RGB.h"
#include "UART.h"

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */

/*==================================================*/
/* Declaration of exported constants                */
/*==================================================*/
/* BYTE constants */


/* WORD constants */



/* LONG and STRUCTURE constants */


/*======================================================*/
/* Definition of RAM variables                          */
/*======================================================*/
/* BYTES */

/* WORDS */

/* LONGS and STRUCTURES */

/*======================================================*/
/* close variable declaration sections                  */
/*======================================================*/

/* Exported functions prototypes and macros */
/* ---------------------------------------- */


/* Functions prototypes */
PUBLIC_FCT void Parklamp_On(void);
PUBLIC_FCT void Parklamp_Off(void);

PUBLIC_FCT void Headlamp_On(void);
PUBLIC_FCT void Headlamp_Off(void);

PUBLIC_FCT void Light_Off(void);
PUBLIC_FCT void Half_Light(void);
PUBLIC_FCT void Light_On(T_UBYTE);

PUBLIC_FCT void Change_State(T_UBYTE,T_UBYTE,T_UBYTE);
PUBLIC_FCT void AutomaticMode(T_UBYTE,T_UBYTE);

PUBLIC_FCT T_BOOLEAN VerifyCheckSum(T_UBYTE data);
PUBLIC_FCT T_UBYTE GetInfo(T_UBYTE data);
PUBLIC_FCT T_UBYTE SelectorValue(T_UBYTE data);
PUBLIC_FCT T_UBYTE LightSensor(T_UBYTE data);
PUBLIC_FCT T_UBYTE IgnitionStatus(T_UBYTE data);

PUBLIC_FCT T_UBYTE MakeResponse(T_UBYTE,T_UBYTE,T_UBYTE,T_UBYTE);

/* Functions macros */

/* Exported defines */

#define Parklamps		BLUE_LED
#define Headlamps		GREEN_LED

// Selector Field Value
#define OFF 	0
#define AUTO 	1
#define PARK	2
#define HEAD	3

//Light Sensor Field Value
#define INVALID			0
#define LESS_40			1
#define BETWEEN_60_80	2
#define MORE_80			3

//Info Field Value
#define NoError		0
#define CHKSError	1
#define UARTOff		2
#define TurnOnUART	3

#endif /* RGB_LEDS_H */
