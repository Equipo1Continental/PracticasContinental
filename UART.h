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
void UART0_Init (void);

void UART0_SendChar(T_UBYTE);
void UART0_Write(T_UBYTE *);

T_UBYTE UART0_GetChar(void);


/* Functions macros */

/* Exported defines */

#endif /* UART_H_ */
