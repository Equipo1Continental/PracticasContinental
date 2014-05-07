/*============================================================================*/
/*                              TEAM 1				                          */
/*============================================================================*/
/*                           System Functions                                 */
/*============================================================================*
* C Include:        System.h
* Instance:
* version:          1
* Created_by:       Mario Alberto Rivera González
* Date_created:     Thu April 10 16:15:51 2014
*=============================================================================*/
/* DESCRIPTION : C Source file for System Configuration                       */
/*============================================================================*/
/* FUNCTION COMMENT : The functions showed below allow users to configure     */
/* System on FREEDOM KL25Z128									              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 10/04/2014  | Configure all clock signals   |   Mario Rivera	  */
/*============================================================================*/


/* Includes */
/* -------- */

#include "System.h"
#include "derivative.h"
#include "stdtypedef.h"

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
 *  Name                 :	SystemInit
 *  Description          :	Enable all port clocks and configure Clock signal
 *  						to use PLL/2 source clock for peripherals
 *
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/

PUBLIC_FCT void SystemInit(void)
{
	//SIM_COPC |= SIM_COPC_COPT(0);			//Disable watchdog timer

	SIM_SCGC5 |= (  SIM_SCGC5_PORTA_MASK	//Enable all port clocks.
				  | SIM_SCGC5_PORTB_MASK
				  | SIM_SCGC5_PORTC_MASK
				  | SIM_SCGC5_PORTD_MASK
				  | SIM_SCGC5_PORTE_MASK );

	SIM_CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(0) | SIM_CLKDIV1_OUTDIV4(1) );	//Set Clock dividers to obtained 48MHz

	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; 	//Set PLLFLLSEL to select the PLL / 2 for this clock source (UART)
}
