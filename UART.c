/*============================================================================*/
/*                                TEAM 1		                              */
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
/* according to FREEDOM board KL25Z128. 									  */
/*                  														  */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 19/04/2014  | Add description for every     | Isaac Ávila      */
/* 						   | function		               |      			  */
/*----------------------------------------------------------------------------*/
/*  2.0      | 24/04/2014  | Add functions start() and 	   | Isaac Ávila      */
/* 			 |			   | stop(), modify init() for     |                  */
/*			 |             | autocalculate BR registers    |                  */	
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
 *							and calculate BR y OSR registers according to baud rate 
 *							establish (9,600bps) . At the end of this function, 
 *                          the UART0 module is started.
 *                          
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
void UART0_Init (T_ULONG bd_value)
{
	T_ULONG baud_rate = 0;					//Variable to store baud rate
	T_ULONG br_value = 0;					//Variable to store BD dividers
	float br_float = 0;						//Auxiliar variable to save the result of division
	float residue = 0;						//Variable to store the minimun residue
	T_UBYTE temp = 4;						//Auxiliar Variable
	T_UWORD osr_value = 4;					//Variable to store OSR dividers
	const T_ULONG mcg_clk_hz = 21000000;	//FEI mode Frequency to UART0
	T_UBYTE i = 0;							//Auxiliar Variable
	
	PORTA_PCR1 = PORT_PCR_MUX(2);       //Enable the UART_TXD function on PTA1 
	PORTA_PCR2 = PORT_PCR_MUX(2);       //Enable the UART_TXD function on PTA2
	
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); //Select the PLLFLLCLK as UART0 clock source 	 
	
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;  //Enable Clock signal for UART0 
  
	UART0_Stop();		//Disable UART0 before changing registers
	
	baud_rate = bd_value;	//Baud rate desired	
	
	/*
	 * Calculate BR registers depends on Baud Rate = Baud Clock / (BR * (OSR + 1)) according to datasheet
	 */
	br_value = mcg_clk_hz / (baud_rate * (osr_value + 1));
	br_float = (float)mcg_clk_hz / ((float)baud_rate * ((float)osr_value + 1));
	residue = br_float - (float)br_value;
	
	/*
	 * Calculate it for all OSR possible values to find the minimum error
	 */
	for(i=5; i<=32;i++)
	{
		br_value = mcg_clk_hz / (baud_rate * (i + 1));
		br_float = (float)mcg_clk_hz / ((float)baud_rate * ((float)i + 1));
		br_float -= (float)br_value;
		if(br_float < residue)		//If a new "minimum error" is found
		{
			residue = br_float;		//Store new minimum error
			temp = i;				//Store OSR value for this minimum error
		}
	}
	
	osr_value = temp;				//Assign the OSR value founded to calculate the minimum error
	br_value = mcg_clk_hz / (baud_rate * (osr_value + 1));	//Calculate BR value
	
	UART0_BDH |= UART0_BDH_SBR(((br_value & 0x1F00) >> 8)); //Setting BD dividers
	UART0_BDL = (T_UBYTE)(br_value & UART0_BDL_SBR_MASK);   //Setting BD dividers

	UART0_C4 = UART0_C4_OSR(osr_value);                     //Setting OSR for Sampling Ratio
	
	/*
	 * If Sampling Ratio is less than 8
	 */
	if(osr_value < 8)
	{
		/*
		 * Enable both edges of baud clock for receiving data
		 */
		UART0_C5|= UART0_C5_BOTHEDGE_MASK;	
	}
	else
	{
		
	}
	
	UART0_C1 &=~(UART0_C1_M_MASK | UART0_C1_PE_MASK);       //8 Bit for data, No parity Selected
	  
	UART0_BDH &= ~(UART0_BDH_SBNS_MASK);                    //Configure One Stop Bit: 0 One stop bit.
	
	/*
	 * Enable receiver and transmitter
	 */
	UART0_Start();
}

/**************************************************************
 *  Name                 :	UART0_Start
 *  Description          :	Enables UART0's Receiver and Transmitter  
 *  Parameters           :      None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
void UART0_Start()
{
	UART0_C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK );	//Enable receiver and transmitter	
}

/**************************************************************
 *  Name                 :	UART0_Stop
 *  Description          :	Enables UART0's Receiver and Transmitter  
 *  Parameters           :      None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
void UART0_Stop()
{
	UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);	//Disable transmitter and Receiver	
}

/**************************************************************
 *  Name                 :	UART0_SendChar
 *  Description          :	Send a character through UART0  
 *  Parameters           :  
 *  						T_UBYTE ch: The character to be sent
 *  						
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
void UART0_SendChar(T_UBYTE ch)
{
      while(!(UART0_S1 & UART0_S1_TDRE_MASK));  //Wait until space is available in the FIFO 
    
      UART0_D = (T_UBYTE)ch;              		//Send the character  
}


/**************************************************************
 *  Name                 :	UART0_Write
 *  Description          :	Send a string through UART0  
 *  Parameters           :  
 *  						T_UBYTE *ptr: The string to be sent
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
      while (!(UART0_S1 & UART0_S1_RDRF_MASK));		//Wait until character has been received
    
      return UART0_D;   							//Return the 8-bit data from the receiver
}
