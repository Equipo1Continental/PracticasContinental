/*============================================================================*/
/*                                TEAM 1		                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         RGB_LEDs.c
* Instance:         RPL_1
* version:         	1
* created_by:      	Karen Anaid Ramirez Sánchez
* date_created:     Thu March 03 00:28:12 2014
*=============================================================================*/
/* DESCRIPTION : C source for RGB_LEDs functions file                         */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source for RGB LEDs functions */
/* according to FREEDOM board KL25Z128. 									  */
/*                  														  */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 03/04/2014  | Add description for every     | Karen Ramirez    */
/* 						   | function		               |                  */
/*============================================================================*/

/* Includes */
/* -------- */
#include "RGB.h"
#include "derivative.h" /* include peripheral declarations */

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */


/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 :
 *  Description          :
 *  Parameters           :
 *  Return               :
 *  Critical/explanation :
 **************************************************************/


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 :
 *  Description          :
 *  Parameters           :
 *  Return               :
 *  Critical/explanation :
 **************************************************************/

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	LED_Init
 *  Description          :	This function configures PORTB 18, PORTB 19
 *							and PORTD 1 as GPIO and outputs.
 *							The function sets every pin for clearing the respective LED
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void LED_Init(void)
 {
	/*
	SIM_SCGC5 |= (	SIM_SCGC5_PORTA_MASK | 		//Port A Clock Gate Control; Clock Enable
					SIM_SCGC5_PORTB_MASK | 		//Port B Clock Gate Control; Clock Enable
					SIM_SCGC5_PORTC_MASK | 		//Port C Clock Gate Control; Clock Enable
					SIM_SCGC5_PORTD_MASK | 		//Port D Clock Gate Control; Clock Enable
					SIM_SCGC5_PORTE_MASK	);	//Port E Clock Gate Control; Clock Enable
	*/

	PORTB_PCR18 = PORT_PCR_MUX(1);				//PIN configured as GPIO (RED LED)
	PORTB_PCR19 = PORT_PCR_MUX(1);				//PIN configured as GPIO (GREEN LED)
	PORTD_PCR1 = PORT_PCR_MUX(1);				//PIN configured as GPIO (BLUE LED)

	GPIOB_PSOR |= ( RED_LED | GREEN_LED);		//Sets pin 18 (RED OFF) and Sets pin 19 (GREEN OFF)
	GPIOB_PDDR |= ( RED_LED | GREEN_LED);		//Configures pin 18 and pin 19 as output
	GPIOD_PSOR |= ( BLUE_LED );					//Sets pin 1 (BLUE OFF)
	GPIOD_PDDR |= ( BLUE_LED );					//Configures pin 1 as output
}

/**************************************************************
 *  Name                 :	RED_ON
 *  Description          :	This function clears PORTB 18 for turning RED LED on
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void RED_ON(void)
{
	GPIOB_PCOR |= RED_LED;		//Clears pin 18 from PORTB (RED ON)
}

/**************************************************************
 *  Name                 :	RED_OFF
 *  Description          :	This function sets PORTB 18 for turning RED LED off
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void RED_OFF(void)
{
	GPIOB_PSOR |= RED_LED;		//Sets pin 18 from PORTB (RED OFF)
}

/**************************************************************
 *  Name                 :	GREEN_ON
 *  Description          :	This function clears PORTB 19 for turning GREEN LED on
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void GREEN_ON(void)
{
	GPIOB_PCOR |= GREEN_LED;	//Clears pin 19 from PORTB (GREEN ON)
}

/**************************************************************
 *  Name                 :	GREEN_OFF
 *  Description          :	This function sets PORTB 19 for turning GREEN LED off
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void GREEN_OFF(void)
{
	GPIOB_PSOR |= GREEN_LED;	//Sets pin 18 from PORTB (GREEN OFF)
}

/**************************************************************
 *  Name                 :	BLUE_ON
 *  Description          :	This function clears PORTD 1 for turning BLUE LED on
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void BLUE_ON(void)
{
	GPIOD_PCOR |= BLUE_LED;		//Clears pin 1 from PORTD (BLUE ON)
}

/**************************************************************
 *  Name                 :	BLUE_OFF
 *  Description          :	This function sets PORTD 1 for turning BLUE LED off
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void BLUE_OFF(void)
{
	GPIOD_PSOR |= BLUE_LED;		//Sets pin 1 from PORTD (BLUE OFF)
}

/**************************************************************
 *  Name                 :	ALL_ON
 *  Description          :	This function clears PORTB 18, PORTB 19 and PORTD 1 for turning RED,GREEN and BLUE LED on
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void ALL_ON(void)
{
	GPIOB_PCOR |= ( RED_LED | GREEN_LED | BLUE_LED);	//Clears pin 18 (RED ON) and pin 19 (GREEN ON)
	GPIOD_PCOR |= BLUE_LED;								//Clears pin 1 (BLUE ON)
}

/**************************************************************
 *  Name                 :	ALL_OFF
 *  Description          :	This function sets PORTB 18, PORTB 19 and PORTD 1 for turning RED,GREEN and BLUE LED off
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void ALL_OFF(void)
{
	GPIOB_PSOR |= ( RED_LED | GREEN_LED);	//Sets pin 18 (RED OFF) and pin 19 (GREEN OFF)
	GPIOD_PSOR |= BLUE_LED;					//Sets pin 1 (BLUE OFF)
}







