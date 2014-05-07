/*============================================================================*/
/*                              TEAM 1				                          */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        RGB_LEDs.h
* Instance:         RPL_1
* version:          1
* Created_by:       Karen Anaid Ramirez Sánchez
* Date_created:     Thu March 03 00:10:34 2014
*=============================================================================*/
/* DESCRIPTION : Header file for RGB LEDs	                                  */
/*============================================================================*/
/* FUNCTION COMMENT : The functions showed below allow users to configure     */
/* RGB LEDs embebed on FREEDOM KL25Z128							              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 03/04/2014  | Add LED_Init, RED_ON, RED_OFF |   Karen Ramirez   */
/* 						   | GREEN_ON, GREEN_OFF, BLUE_ON  |				  */
/*  					   | BLUE_OFF, ALL_ON AND ALL_OFF  |                  */
/*============================================================================*/

#ifndef RGB_LEDS_H          /* To avoid double inclusion */
#define RGB_LEDS_H

/* Includes */
/* -------- */
#include "stdtypedef.h"

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
PUBLIC_FCT void LED_Init(void);

PUBLIC_FCT void RED_ON(void);
PUBLIC_FCT void RED_OFF(void);

PUBLIC_FCT void GREEN_ON(void);
PUBLIC_FCT void GREEN_OFF(void);

PUBLIC_FCT void BLUE_ON(void);
PUBLIC_FCT void BLUE_OFF(void);

PUBLIC_FCT void ALL_OFF(void);
PUBLIC_FCT void ALL_ON(void);

/* Functions macros */

/* Exported defines */

#define RED_LED			(0x40000u)
#define GREEN_LED		(0x80000u)
#define BLUE_LED	    (2u)

#endif /* RGB_LEDS_H */
