/*============================================================================*/
/*                                TEAM 1		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         UART.c
* Instance:         
* version:         	1
* created_by:      	Carlos Isaac Ávila Gutiérrez
* date_created:     Sat April 19 20:30:36 2014 
*=============================================================================*/
/* DESCRIPTION : C source for UART0 functions file                        	  */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source for UART0 functions 	  */
/* according to FREEDOM board KL25Z128. 									                    */
/*                  														                              */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 19/04/2014  | Add description for every     | Isaac Ávila      */
/* 						             | function		                   |                  */
/*============================================================================*/

/* Includes */
/* -------- */
#include "UART.h"
#include "stdtypedef.h"
#include "derivative.h"

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
 *  Name                 :	UART0_Init
 *  Description          :	This function initializes UART0 drivers
 *							            and calculate BR y OSR registers according to baud rate 
 *							            establish (9,600bps) . At the end of this function, 
 *                          the UART0 module is started.
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
void UART0_Init (void)
{
	
	T_ULONG br_value = 0;
	T_UWORD osr_value = 24;			                            //Sampling ratio for less error percent (9,600 bps)
	T_ULONG mcg_clk_hz = 21000000;	                        //Frequency for FEI mode (Reset Mode)
	
	PORTA_PCR1 = PORT_PCR_MUX(2);                           //Enable the UART_TXD function on PTA1 
	PORTA_PCR2 = PORT_PCR_MUX(2);                           //Enable the UART_TXD function on PTA2
	
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);                     //select the PLLFLLCLK as UART0 clock source 	 
	
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;                      //Enable Clock signal for UART0 
  
	UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);     //Disable UART0 before changing registers
	
	br_value = mcg_clk_hz / (baud_rate * (osr_value + 1));  //Calculate br value
	
	UART0_BDH |= UART0_BDH_SBR(((br_value & 0x1F00) >> 8)); //Setting BD dividers
	UART0_BDL = (T_UBYTE)(br_value & UART0_BDL_SBR_MASK);   //Setting BD dividers

	UART0_C4 = UART0_C4_OSR(osr_value);                     //Setting OSR for Sampling Ratio
	
	UART0_C1 &=~(UART0_C1_M_MASK | UART0_C1_PE_MASK);       //8 Bit for data, No parity Selected
	  
	UART0_BDH &= ~(UART0_BDH_SBNS_MASK);                    //Configure One Stop Bit: 0 One stop bit.
	
	UART0_C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK );	    //Enable receiver and transmitter
}

/**************************************************************
 *  Name                 :	UART0_SendChar
 *  Description          :	Send a character through UART0  
 *  Parameters           :  
 *  						            T_UBYTE ch: The character to be sent
 *  						
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
void UART0_SendChar(T_UBYTE ch)
{
      while(!(UART0_S1 & UART0_S1_TDRE_MASK));  //Wait until space is available in the FIFO 
    
      UART0_D = (T_UBYTE)ch;              //Send the character  
}


/**************************************************************
 *  Name                 :	UART0_Write
 *  Description          :	Send a string through UART0  
 *  Parameters           :  
 *  						            T_UBYTE *ptr: The string to be sent
 *  						
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
void UART0_Write(T_UBYTE *ptr)
{
	while(*ptr)
	{
		UART0_SendChar(*ptr);
		ptr++;
	}
}

/**************************************************************
 *  Name                 :	UART0_GetChar
 *  Description          :	Receive a character through UART0  
 *  Parameters           :  None
 *  						
 *  Return               :	
 *                          T_UBYTE UART0_D : Received data from UART0
 *  Critical/explanation :  No
 **************************************************************/

T_UBYTE UART0_GetChar(void)
{
      while (!(UART0_S1 & UART0_S1_RDRF_MASK));   //Wait until character has been received
    
      return UART0_D;   //Return the 8-bit data from the receiver
}
