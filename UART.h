/*============================================================================*/
/*                              TEAM 1				                          */
/*============================================================================*/
/*                           UART0 Functions                                  */
/*============================================================================*
* C Include:        UART0.h
* Instance:         
* version:          1
* Created_by:       Carlos Isaac Ávila Gutiérrez
* Date_created:     Sat April 19 20:10:15 2014 
*=============================================================================*/
/* DESCRIPTION : Header file for UART0 drivers                                */
/*============================================================================*/
/* FUNCTION COMMENT : The functions showed below allow users to configure     */
/* UART0 on FREEDOM KL25Z128									              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 19/04/2014  | Add all functions for UART0   |   Isaac Avila	  */
/* 						   | such as: Init, 			   |				  */
/*  					   | SendChar, Write and GetChar   |                  */
/*----------------------------------------------------------------------------*/
/*  2.0      | 24/04/2014  | Add GetString function.       |   Isaac Avila	  */
/* 						   | Modify UART0_GetChar changing |				  */
/*  					   | while loop					   |                  */
/*============================================================================*/

#ifndef UART_H_			/* To avoid double inclusion */
#define UART_H_

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
PUBLIC_FCT void UART0_Init (T_ULONG bd_value);

PUBLIC_FCT void UART0_Start(void);
PUBLIC_FCT void UART0_Stop(void);

PUBLIC_FCT void UART0_SendChar(T_UBYTE lub_character);
PUBLIC_FCT void UART0_Write(PTR_UBYTE lpub_ptr);

PUBLIC_FCT T_UBYTE UART0_GetChar(void);
PUBLIC_FCT PTR_UBYTE UART0_GetString(void);

/* Functions macros */

/* Exported defines */
#define UART_STRING_LENGTH 	32u		//Length of received string
#define NewPage 			0x0C	//Command for sending a new page (clear screen)
#define CR					0x0D	//Carriage Return (Return to the initial position)
#define LF					0x0A	//Linefeed (New Line)

#endif /* UART_H_ */
