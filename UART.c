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
/*----------------------------------------------------------------------------*/
/*  3.0      | 25/04/2014  | Use naming convention on      | Isaac Ávila      */
/* 						   | variables		               |                  */
/*============================================================================*/

/* Includes */
/* -------- */
#include "UART.h"
#include "stdtypedef.h"
#include "derivative.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
volatile T_UBYTE rub_UART_String[UART_STRING_LENGTH];

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
 *							desired. At the end of this function, the UART0 module is 
 *							Started.
 *  Parameters           :  
 *  						bd_value : Baud Rate desired for UART communication
 *  						
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/

PUBLIC_FCT void UART0_Init (T_ULONG bd_value)
{
	const T_ULONG cul_mcg_clk_hz = 24000000;	//PLL/2 Source Clock for UART 
	
	T_ULONG lul_baud_rate = 0;					//Variable to store baud rate
	T_ULONG lul_br_value = 0;					//Variable to store BD dividers
	float lf_br_float = 0;						//Auxiliary variable to save the result of division
	float lf_residue = 0;						//Variable to store the minimum residue
	T_UBYTE lub_temp = 4;						//Auxiliary Variable
	T_UWORD luw_osr_value = 4;					//Variable to store OSR dividers
	register T_UBYTE lub_i = 0;					//Auxiliary Variable
	
	
	PORTA_PCR1 = PORT_PCR_MUX(2);			//Enable the UART_TXD function on PTA1 
	PORTA_PCR2 = PORT_PCR_MUX(2);			//Enable the UART_TXD function on PTA2 
	
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); 	//Select the PLLFLLCLK as UART0 clock source	 
	 
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;		//Enable Clock signal for UART0 
	
	UART0_Stop();							//Disable UART0 before changing registers
	
	lul_baud_rate = bd_value;				//Store Baud rate desired
	
	/*
	 * Calculate BR registers depends on Baud Rate = Baud Clock / (BR * (OSR + 1)) according to datasheet
	 */
	lul_br_value = cul_mcg_clk_hz / (lul_baud_rate * (luw_osr_value + 1));
	lf_br_float = (float)cul_mcg_clk_hz / ((float)lul_baud_rate * ((float)luw_osr_value + 1));
	lf_residue = lf_br_float - (float)lul_br_value;
	
	/*
	 * Calculate it for all OSR possible values to find the minimum error
	 */
	for(lub_i = 5; lub_i <= 32; lub_i++)
	{
		lul_br_value = cul_mcg_clk_hz / (lul_baud_rate * (lub_i + 1));
		lf_br_float = (float)cul_mcg_clk_hz / ((float)lul_baud_rate * ((float)lub_i + 1));
		lf_br_float -= (float)lul_br_value;
		if(lf_br_float <= lf_residue)		//If a new "minimum error" is found
		{
			lf_residue = lf_br_float;		//Store new minimum error
			lub_temp = lub_i;				//Store OSR value for this minimum error
		}
	}
	
	luw_osr_value = lub_temp;				//Assign the found OSR value to calculate the minimum error
	lul_br_value = cul_mcg_clk_hz / (lul_baud_rate * (luw_osr_value + 1));	//Calculate BR value
	
	UART0_BDH |= UART0_BDH_SBR(((lul_br_value & 0x1F00) >> 8));	//Setting BD dividers
	UART0_BDL = (T_UBYTE)(lul_br_value & UART0_BDL_SBR_MASK);	//Setting BD dividers
	
	UART0_C4 = UART0_C4_OSR(luw_osr_value);		//Setting OSR for Sampling Ratio
	
	if(luw_osr_value < 8)						//If Sampling Ratio is less than 8
	{
		UART0_C5|= UART0_C5_BOTHEDGE_MASK;		//Enable both edges of baud clock for receiving data
	}
	else
	{
		
	}
	
	UART0_C1 &=~(UART0_C1_M_MASK | UART0_C1_PE_MASK);	//8 Bit for data, No parity Selected
	
	UART0_BDH &= ~(UART0_BDH_SBNS_MASK);				//Configure One Stop Bit: 0 One stop bit.
	
	UART0_Start();			//Enable receiver and transmitter
}

/**************************************************************
 *  Name                 :	UART0_Start
 *  Description          :	Enable Receiver and Transmitter  
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void UART0_Start(void)
{
	UART0_C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK );		//Enable receiver and transmitter
}

/**************************************************************
 *  Name                 :	UART0_Stop
 *  Description          :	Disable Receiver and Transmitter after buffer is empty 
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void UART0_Stop(void)
{
	while(!(UART0_S1 & UART0_S1_TDRE_MASK));				//Wait until buffer is empty 
	UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);		//Disable transmitter and Receiver
}


/**************************************************************
 *  Name                 :	UART0_SendChar
 *  Description          :	Send a character through UART0  
 *  Parameters           :  
 *  						T_SBYTE lub_character: The character to be sent
 *  						
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void UART0_SendChar(T_UBYTE lub_character)
{
	while(!(UART0_S1 & UART0_S1_TDRE_MASK));	//Wait until buffer is empty 
	UART0_D = (T_UBYTE)lub_character;  			//Send the character 
}


/**************************************************************
 *  Name                 :	UART0_Write
 *  Description          :	Send a string through UART0  
 *  Parameters           :  
 *  						T_SBYTE *lpub_ptr: The string to be sent
 *  						
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void UART0_Write(PTR_UBYTE lpub_ptr)
{
	while(*lpub_ptr)				//While string isn't end		
	{
		UART0_SendChar(*lpub_ptr);	//Send every character of the string	
		lpub_ptr++;					//Point to next character
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
PUBLIC_FCT T_UBYTE UART0_GetChar(void)
{
	T_UBYTE lub_readData = 0;
	//while (!(UART0_S1 & UART0_S1_RDRF_MASK));	//Wait until character has been received 
	if(UART0_S1 & UART0_S1_RDRF_MASK)
	{
		lub_readData &= 0;
		lub_readData |= UART0_D;
	}
	else
	{
		
	}
	
    return lub_readData;								//Return the 8-bit data from the receiver
}

/**************************************************************
 *  Name                 :	UART0_GetString
 *  Description          :	Receive a string through UART0 and
 *  						store it in array rub_UART_String. 
 *  						Print the string read character by
 *  						character (echo).
 *  						
 *  Parameters           :  None
 *  						
 *  Return               :	
 *                          T_UBYTE *rub_UART_String : Locality of array where the string was stored
 *                          
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT PTR_UBYTE UART0_GetString(void)
{
	T_UBYTE lub_Data = 0;						//Temporarily variable to every character
	T_BOOLEAN lbi_StringComplete = FALSE;		//Flag to indicate finished reading
	T_UBYTE lub_index = 0;

	while(!lbi_StringComplete)
	{
		lub_Data = UART0_GetChar();					//Read character
		if((lub_Data != '\r') && (lub_Data != 0))
		{
			rub_UART_String[lub_index] = lub_Data;	//Store read character
			lub_index++;							//Point to next location
			UART0_SendChar(lub_Data);				//Echo data
		}	
		else
		{
			rub_UART_String[lub_index] = 0;			//Finish the string
			UART0_SendChar(CR);						//Print escape sequence
			UART0_SendChar(LF);						//Print escape sequence
			lbi_StringComplete = TRUE;				//Finish the reading
		}
	}
    return (PTR_UBYTE)rub_UART_String;				//Return the pointer where string is stored
}
