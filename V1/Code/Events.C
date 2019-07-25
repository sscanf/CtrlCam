/*
** ###################################################################
**
**     Filename  : Events.C
**
**     Project   : CtrlCam
** 
**     Processor : MC68HC908GP32CFB
**
**     Beantype  : Events
**
**     Version   : Driver 01.00
**
**     Compiler  : Metrowerks HC08 C Compiler V-5.0.13
**
**     Date/Time : 1/20/martes, 13:05
**
**     Abstract  :
**
**         This is user's event module.
**         Put your event handler code here.
**
**     Settings  :
**
**
**     Contents  :
**
**         Teclado_OnKeyDown - void Teclado_OnKeyDown(void);
**         Cpu_OnSwINT       - void Cpu_OnSwINT(void);
**
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2002
**
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
**
** ###################################################################
*/
/* MODULE Events */

#pragma MESSAGE DISABLE C1420 /* WARNING C1420: Result of function-call is ignored */


/*Including used modules for compilling procedure*/
#include "Cpu.h"
#include "Events.h"
#include "LED_VAL.h"
#include "SERIE.h"
#include "ENABLE_LED1.h"
#include "ENABLE_LED2.h"
#include "Timer.h"
#include "Flash.h"
#include "Seleccion.h"
#include "DERECHA.h"
#include "IZQUIERDA.h"
#include "ARRIBA.h"
#include "ABAJO.h"
#include "FOCOMAS.h"
#include "FOCOMENOS.h"
#include "ZOOMMAS.h"
#include "ZOOMMENOS.h"
#include "Teclado.h"
#include "Inhr2.h"
#include "Inhr3.h"
#include "Inhr4.h"
#include "Inhr5.h"
#include "Inhr6.h"
#include "Inhr7.h"
#include "Inhr8.h"
#include "Inhr9.h"
#include "JoistickAction.h"
#include "CtrlCam.h"

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/*
** ===================================================================
**     Event       :  Teclado_OnKeyDown (module Events)
**
**     From bean   :  Teclado [KeyboardMatrix]
**     Description :
**         Event is called when key is pressed
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Teclado_OnKeyDown(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Cpu_OnSwINT (module Events)
**
**     From bean   :  Cpu [MC68HC908GP32_44]
**     Description :
**         This software event is called after software reset.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Cpu_OnSwINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  SERIE_OnError (module Events)
**
**     From bean   :  SERIE [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be
**         read using GetError method.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  SERIE_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  SERIE_OnRxChar (module Events)
**
**     From bean   :  SERIE [AsynchroSerial]
**     Description :
**         This event is called after a correct character is
**         received. This
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  SERIE_OnRxChar(void)
{
	 OnRxChar();
}

/*
** ===================================================================
**     Event       :  SERIE_OnTxChar (module Events)
**
**     From bean   :  SERIE [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  SERIE_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  SERIE_OnFullRxBuf (module Events)
**
**     From bean   :  SERIE [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  SERIE_OnFullRxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  SERIE_OnFreeTxBuf (module Events)
**
**     From bean   :  SERIE [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  SERIE_OnFreeTxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Bean1_OnKeyDown (module Events)
**
**     From bean   :  Teclado [KeyboardMatrix]
**     Description :
**         Event is called when key is pressed
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Bean1_OnKeyDown(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Timer_OnInterrupt (module Events)
**
**     From bean   :  Timer [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the bean is enabled - "Enable" and the events are
**         enabled - "EnableEvent").
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Timer_OnInterrupt(void)
{
	OnTimer();
}


/* END Events */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 02.89 for 
**     the Motorola HC08 series of microcontrollers.
**
** ###################################################################
*/
