/*============================================================================*/
/*                                TEAM 1		                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         Lamp_Control.c
* Instance:         RPL_1
* version:         	1
* created_by:      	Mario Alberto Rivera González
* date_created:     Thu March 03 01:20:50 2014
*=============================================================================*/
/* DESCRIPTION : C source for Lamp Control functions file                     */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source for Lamp Control 	  */
/* functions according to FREEDOM board KL25Z128. 							  */
/*                  														  */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 03/04/2014  | 						                   | Mario Rivera     */
/*============================================================================*/

/* Includes */
/* -------- */
#include "Lamp Control.h"
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
 *  Name                 :	Headlamp_On
 *  Description          :	This function turns blue LED on
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void Headlamp_On(void)
{
	BLUE_ON();
}

/**************************************************************
 *  Name                 :	Headlamp_Off
 *  Description          :	This function turns blue LED off
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void Headlamp_Off(void)
{
	BLUE_OFF();
}

/**************************************************************
 *  Name                 :	Parklamp_On
 *  Description          :	This function turns green LED on
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void Parklamp_On(void)
{
	GREEN_ON();
}

/**************************************************************
 *  Name                 :	Parklamp_Off
 *  Description          :	This function turns green LED off
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void Parklamp_Off(void)
{
	GREEN_OFF();
}

/**************************************************************
 *  Name                 :	Light_Off
 *  Description          :	This function turns Parklamp and Headlamp off
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void Light_Off(void)
{
	Parklamp_Off();
	Headlamp_Off();
}

/**************************************************************
 *  Name                 :	Half_Light
 *  Description          :	This function turns Parklamp on and Headlamp off
 *  Parameters           :  None
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void Half_Light(void)
{
	Parklamp_On();
	Headlamp_Off();
}

/**************************************************************
 *  Name                 :	Light_On
 *  Description          :	This function turns Parklamp and Headlamp on depending on Ignition value
 *  Parameters           :
 *  						T_UBYTE IgnitionValue: Indicate the way lamps will be on
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void Light_On(T_UBYTE IgnitionValue)
{
	if(IgnitionValue >= 2)
	{
		Parklamp_On();
		Headlamp_On();
		//UART0_Write("\r\nRUN,START RECIBIDO.\r\n");
	}
	else
	{
		Parklamp_On();
		Headlamp_Off();
		//UART0_Write("\r\nOFF, ACC RECIBIDO.\r\n");
	}
}

/**************************************************************
 *  Name                 :	Change_State
 *  Description          :	This function modifies lamp control depending on Selector, Light and Ignition values
 *  Parameters           :
 *  						T_UBYTE Selector:
 *  						T_UBYTE light:
 *  						T_UBYTE IgnitionStatus:
 *
 *  Return               :	None
 *  Critical/explanation :  No
 **************************************************************/
PUBLIC_FCT void Change_State(T_UBYTE Selector, T_UBYTE light,T_UBYTE IgnitionStatus)
{
	switch(Selector)
	{
		case OFF:
			Light_Off();
			//UART0_Write("\r\nComando de Luces apagadas (OFF).\r\n");
			break;

		case AUTO:
			AutomaticMode(light,IgnitionStatus);
			//UART0_Write("\r\nComando de Luces en modo automático (AUTO).\r\n");
			break;

		case PARK:
			Half_Light();
			//UART0_Write("\r\nComando de Parklamps encendidas (PARK).\r\n");
			break;

		case HEAD:
			Light_On(IgnitionStatus);
			//UART0_Write("\r\nComando de Luces encendidas (HEAD).\r\n");
			break;

		default:
			break;
	}
}

/**************************************************************
 *  Name                 :	AutomaticMode
 *  Description          :	This function change the lighting depending on light value
 *
 *  Parameters           :  T_UBYTE light: Darkness percentage
 *  						T_UBYTE IgnitionStatus: Command required for Light_On Mode
 *
 *  Return               :	Nothing
 *  Critical/explanation :  No
 ***************************************************************/
PUBLIC_FCT void AutomaticMode(T_UBYTE light, T_UBYTE IgnitionStatus)
{
	switch(light)
	{
		case INVALID:
				Light_Off();	//Turns parklamps and headlamps off
			break;

		case LESS_40:
				Light_On(IgnitionStatus);	//Turns parklamps and headlamps on
			break;

		case BETWEEN_60_80:
				Half_Light();	//Turns parklamps on and turns headlamps off
			break;

		case MORE_80:
				Light_Off();	//Turns parklamps and headlamps off
			break;

		default:
			break;
	}
}

/**************************************************************
 *  Name                 :	VerifyCheckSum
 *  Description          :	This function verifies the checksum of the data received, The checksum will be correct
 *   						if 8th bit is 1 when the quantity of 1's is odd or if 8th bit is 0 when the quantity of 1's is even
 *   						The checksum will be incorrect if 8th bit is 0 when the quantity of 1's is odd or if 8th bit is 1
 *   						when quantity of 1's is even.
 *
 *  Parameters           :  T_UBYTE data: The data for calculating checksum
 *  Return               :	T_BOOLEAN lbi_Correct: TRUE if checksum is correct
 *  Critical/explanation :  No
 ***************************************************************/
PUBLIC_FCT T_BOOLEAN VerifyCheckSum(T_UBYTE data)
{
	T_UBYTE lub_Mask = 1u;			//Mask for every bit position
	T_UBYTE lub_Sum = 0;			//Variable to store the add of all bits
	T_BOOLEAN lbi_Correct = FALSE;	//Variable to return data
	register T_UBYTE lub_i = 0;		//Variable to control for loop

	for(lub_i = 0; lub_i < 7; lub_i++)			//Loop for making all the 6 masks (0XXX XXX1)
	{
		if(lub_Mask & data)			//if data in lub_mask position is 1
		{
			lub_Sum++;				//Increase the counter
		}
		else						//Data in lub_mask position is 0
		{
									//Does not increase the counter
		}
		lub_Mask = lub_Mask<<1;		//Move to next bit position
	}

	if(!(lub_Sum % 2))			//If sum is even
	{
		lub_Mask &= 0;			//7th Bit on data must be 0, data's checksum is even
	}
	else						//Sum is odd
	{
		lub_Mask &= 0;			//Clear mask
		lub_Mask |= 0x80u;		//7th Bit on data must be 1, data's checksum is odd
	}

	data &= 0x80;				//Do a mask for the 7th bit

	if(!(lub_Mask ^ data))		//Do a XOR for knowing if they're equal, result will be zero if checksum is correct
	{
		lbi_Correct = TRUE;		//Checksum is correct
	}
	else
	{
		lbi_Correct = FALSE;	//Checksum is incorrect
	}

	return lbi_Correct;			//Return the checksum flag
}


/**************************************************************
 *  Name                 :	GetInfo
 *  Description          :	This function verifies the value of 7th bit.
 *
 *  Parameters           :  T_UBYTE data: The data from which 7th bit will be verified
 *  Return               :	T_UBYTE lub_Info: The value of INFO bits.
 *  Critical/explanation :  No
 ***************************************************************/
PUBLIC_FCT T_UBYTE GetInfo(T_UBYTE data)
{

	const T_UBYTE cub_StopMask = 0x40u;	//Mask for 7th bit position
	T_UBYTE lub_Info = 0;				//Flag to indicate 7h bit's value
	T_BOOLEAN lbi_CheckSum = FALSE;		//Flag to indicate checksum value

	lbi_CheckSum = VerifyCheckSum(data);	//Verify Checksum value

	if(lbi_CheckSum)					//If checksum is correct...
	{
		if(data & cub_StopMask)			//Verify Stop bit
		{
			lub_Info &= 0;				//Clear value on lub_Info
			lub_Info |= 0x02;			//Set 0x02 value to lub_Info (UART will be off for 30 seconds)
		}
		else							//If no stop bit received
		{
			lub_Info &= 0;				//lub_Info is zero (Checksum correct and performs a changing lamp)
		}
	}
	else								//If checksum is incorrect
	{
		lub_Info &= 0;					//Clear value on lub_Info
		lub_Info |= 0x01;				//Set 0x01 value to lub_Info (Checksum was incorrect, no action will be perform)
	}

	return lub_Info;					//Return value
}

/**************************************************************
 *  Name                 :	SelectorValue
 *  Description          :	This function verifies the value of 3th and 4th bits from data.
 *
 *  Parameters           :  T_UBYTE data: The data to verify 3th and 4th bits.
 *  Return               :	T_UBYTE lub_Selector: Value (0 - 3) depending on data value
 *  Critical/explanation :  No
 ***************************************************************/
PUBLIC_FCT T_UBYTE SelectorValue(T_UBYTE data)
{
	T_UBYTE lub_SelectorMask = 0x04u;	//Mask for 3th bit position
	T_UBYTE lub_Selector = 0u;			//Obtained Result from data

	if(data & lub_SelectorMask)			//If 3th bit is 1...
	{
		lub_Selector += 1;				//bit position value is 1
	}
	else
	{
										//No action is done (lub_Selector is still 0)
	}

	lub_SelectorMask = lub_SelectorMask << 1;	//Mask for 4th bit position

	if(data & lub_SelectorMask)			//If 3th bit is 1...
	{
		lub_Selector += 2;				//Bit position value is 2
	}
	else
	{

	}

	return lub_Selector;				//Return value
}

/**************************************************************
 *  Name                 :	LightSensor
 *  Description          :	This function verifies the value from 5th bit and 6th bit.
 *
 *  Parameters           :  T_UBYTE data: The data to verify 5th and 6th bits
 *  Return               :	T_UBYTE lub_Light: Darkness percentage
 *  Critical/explanation :  No
 ***************************************************************/
PUBLIC_FCT T_UBYTE LightSensor(T_UBYTE data)
{
	T_UBYTE lub_LightMask = 0x10u;		//Mask for 5th bit position
	T_UBYTE lub_Light = 0u;				//Darkness percentage

	if(data & lub_LightMask)			//If 5th bit is 1...
	{
		lub_Light += 1;					//bit position value is 1
	}
	else
	{

	}

	lub_LightMask = lub_LightMask << 1;	//Mask for 6th bit position

	if(data & lub_LightMask)			//If 6th bit is 1...
	{
		lub_Light += 2;					//Bit position value is 2
	}
	else
	{

	}

	return lub_Light;					//Return value
}

/**************************************************************
 *  Name                 :	IgnitionStatus
 *  Description          :	This function verifies the value from 1st bit and 2nd bit.
 *
 *  Parameters           :  T_UBYTE data: The data from which 7-bit will be verified
 *  Return               :	T_BOOLEAN lbi_Stop: TRUE if 7-bit value is 1.
 *  Critical/explanation :  No
 ***************************************************************/
PUBLIC_FCT T_UBYTE IgnitionStatus(T_UBYTE data)
{
	T_UBYTE lub_IgnitionMask = 0x01u;	//Mask for 1-bit position
	T_UBYTE lub_Ignition = 0u;			//Obtained Result from data

	if(data & lub_IgnitionMask)			//If 1st bit is 1...
	{
		lub_Ignition += 1;				//bit position value is 1
	}
	else
	{

	}

	lub_IgnitionMask = lub_IgnitionMask << 1;	//Mask for 2-bit position

	if(data & lub_IgnitionMask)			//If 2nd bit is 1...
	{
		lub_Ignition += 2;				//Bit position value is 2
	}
	else
	{

	}

	return lub_Ignition;
}

/**************************************************************
 *  Name                 :	MakeResponse
 *  Description          :	This function makes the data package to send depending on data received.
 *
 *  Parameters           :
 *  						T_UBYTE Info: Variable of last status data received
 *  						T_UBYTE Selector: The last Selector value received
 *  						T_UBYTE Light: The last light value received
 *  						T_UBYTE Ignition: The last Ignition value received
 *
 *  Return               :
 *  						T_UBYTE SentData: The final data to be sent
 *  Critical/explanation :  No
 ***************************************************************/

/* 			       Sent Data Structure
 *        Info      Selector   Ignition     Light
 *   |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
 *                  Bit Position
 */
PUBLIC_FCT T_UBYTE MakeResponse(T_UBYTE Info,T_UBYTE Selector, T_UBYTE Light,T_UBYTE Ignition)
{
	T_UBYTE SentData = 0;			//Clear the data
	T_UBYTE DataMask = 0xC0;		//Mask for 7th and 8th bit (Info Field)

	switch(Info)
	{
		case NoError:
				SentData &= ~(DataMask);	//Write 0 to 8th bit and 0 to 7th bit	(0 - Checksum correct and no UART stop was Received)
			break;

		case CHKSError:
			SentData |= 0x40;			//Write 0 to 8th bit and 1 to 7th bit
			break;

		case UARTOff:
				SentData |= (DataMask & 0x80);	//Write 1 to 8th bit and 0 to 7th bit (2 - Stop bit received correctly, UART wil be disabled for 30 seconds)
			break;

		case TurnOnUART:
				SentData |= DataMask;	//Write 1 to 8th bit and 1 to 7th bit (3 - 30 Seconds has expired)
			break;

		default:
			break;
	}

	Selector = Selector << 4;		//Selector field is composed of 5th and 6th bit
	Ignition = Ignition << 2;		//Ignition field is composed of 3th and 4th bit

	SentData |= ( Selector | Ignition | Light );	//Do an OR of Selector, Ignition and Light fields

	return SentData;
}
