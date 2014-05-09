/*============================================================================*/
/*                     AZOR - EMBEDDED SYSTEMS SOFTWARE                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        periodic_tasks_exec.c
* version:         1.0 
* created_by:      MDRR
* date_created:    July 31 2013 
*=============================================================================*/
/* DESCRIPTION :  This file contains the periodic tasks definition.           */
/*============================================================================*/
/* FUNCTION COMMENT : Add here the user functionality, inside a periodic task */
/* according to the desired execution period.                                 */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 31/jul/2013 |                               | MDRR             */
/* This file is created based on apptask module from the old version of this  */
/* scheduler.                                                                 */
/*============================================================================*/

/* Includes */
/* -------- */
#include "periodic_tasks_exec.h"
#include "periodic_tasks_modules.h"

T_BOOLEAN rbi_ResponseSent = TRUE;
T_BOOLEAN rbi_UARToff = FALSE;
T_BOOLEAN rbi_newData = TRUE;

volatile  T_ULONG rul_secondsCounter = 0;	//Counter for seconds, it must be 6,000 to count 30 seconds
	 
T_UBYTE rub_readData = 0;			//Variable to store the reading data
T_UBYTE rub_sentData = 0;			//Variable to store the reading data

volatile T_UBYTE rub_Info = 0;		//Data to make the response package (Info Field)
volatile T_UBYTE rub_Selector = 0;	//Data to make the response package (Selector Field)
volatile T_UBYTE rub_Light = 0;		//Data to make the response package (Light Field)
volatile T_UBYTE rub_Ignition = 0;	//Data to make the response package (Ignition Field)


/**************************************************************
 *  Name                 : periodic_tasks_exec_5tks
 *	ID					 : TASK_5TKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_5tks(void)
 {
	  if(!rbi_UARToff)				//UART is on?
	  {
		  if(rbi_ResponseSent)		//Has response been sent?
		  {
			  rub_readData = UART0_GetChar();				//Read New Data
			  if(rub_readData == 0)		//Data received is 0x00 (Value read as default)
			  {	
				  rbi_newData = FALSE;	//No new data received		
			  }
			  else
			  {
				  rbi_newData = TRUE;	//New data received
				  
				  rub_Info = GetInfo(rub_readData);				//Obtained Info Field
				  rub_Selector = SelectorValue(rub_readData);	//Obtained Selector Field
				  rub_Light = LightSensor(rub_readData);		//Obtained Light Field
				  rub_Ignition = IgnitionStatus(rub_readData);	//Obtained Ignition Field
				  
				  rbi_ResponseSent = FALSE;		//No response has been sent
				  //UART0_Write("New data received\r\n");
			  }
		  }
		  else		//Response has not been sent
		  {
			  if(rbi_newData == TRUE)	//Send response only if new data was received
			  {
				  //Make BYTE to respond
				  rub_sentData = MakeResponse(rub_Info,rub_Selector,rub_Light,rub_Ignition);
				  UART0_SendChar(rub_sentData);			//Send response byte
				  
				  rbi_ResponseSent = TRUE;				//Reponse has been sent
				  
				  if(rub_Info == UARTOff)				//if UART is OFF
				  {
					  //UART0_Write("UART will be off for 30 s\r\n");
					  rbi_UARToff = TRUE;				//Turn flag OFF
					  UART0_Stop();						//Stop UART
				  }
				  else
				  {
					  
				  }
			  }
			  else
			  {
				  
			  }
		  }
	  }
	  else
	  {
		  
	  }
 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_exec_10tks
 *	ID					 : TASK_10TKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_10tks(void)
 {	 

	  if(!rbi_UARToff)				//UART is on?
	  {
		  if(rbi_newData == TRUE)			//Change state only if correct data was received (except 0x00)
		  {
			  if(rub_Info == NoError)		//Is check sum correct and no stop bit present?
			  {  
				  Change_State(rub_Selector,rub_Light,rub_Ignition);	//Modify lamp status
			  }
			  /*
			  else if(rub_Info == CHKSError)	//if check sum error was detected
			  {
				  UART0_Write("Cheksum Error\r\n");
			  }
			  */
			  else
			  {
				  
			  }
		  }
		  else
		  {
			  
		  }
	  }
	  else
	  {
		  
	  }
 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_exec_20tks
 *	ID					 : TASK_20TKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_20tks(void)
 {
	 
	 
 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_exec_50tks
 *	ID					 : TASK_50TKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_50tks(void)
 {
	 
 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_exec_100tks
 *	ID					 : TASK_100TKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_100tks(void)
 { 
	 
	 if(rbi_UARToff)						//IF UARToff is TRUE
	 {
		 if(rul_secondsCounter >= Second30)	//30 seconds has expired?
		 {
			 rul_secondsCounter &= 0;		//Reset counter
			 
			 UART0_Start();					//UART is turn on
			 rbi_UARToff = FALSE;			//Flag is false again
			 
			 rub_Info &= 0;					//Clear variable
			 rub_Info |= TurnOnUART; 		//UART must to be on again (3)
			 
			 rbi_ResponseSent = FALSE;		//No response has been sent 
			 //UART0_Write("UART will be on\r\n");
		 }
		 else
		 {
			 rul_secondsCounter++;			//Increase counter (100 ms passed)
		 }
	 }
	 else
	 {
		 
	 }
	 
 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_exec_500tks
 *	ID					 : TASK_500TKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_500tks(void)
 {
	 
 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_exec_1Mtks
 *	ID					 : TASK_1MTKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_1Mtks(void)
 {
	 
 }
 
