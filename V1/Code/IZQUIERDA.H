/*
** ###################################################################
**
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**
**     Filename  : IZQUIERDA.H
**
**     Project   : CtrlCam
** 
**     Processor : MC68HC908GP32CFB
**
**     Beantype  : BitIO
**
**     Version   : Bean 02.021, Driver 02.15, CPU db: 2.89.000
**
**     Compiler  : Metrowerks HC08 C Compiler
**
**     Date/Time : 9/15/mi�rcoles, 10:49
**
**     Abstract  :
**
**         This bean "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Note: This bean is set to work in Output direction only.
**         Methods of this bean are mostly implemented as a macros 
**         (if supported by target language and compiler).
**
**     Settings  :
**
**         Used pin                    : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       23            |  PTB1_AD1
**             ----------------------------------------------------
**
**         Port name                   : PTB
**
**         Bit number (in port)        : 1
**         Bit mask of the port        : 2
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : PTB       [1]
**         Port control register       : DDRB      [5]
**
**         Optimization for            : speed
**
**     Contents  :
**
**         GetVal - bool IZQUIERDA_GetVal(void);
**         PutVal - void IZQUIERDA_PutVal(bool Output);
**         ClrVal - void IZQUIERDA_ClrVal(void);
**         SetVal - void IZQUIERDA_SetVal(void);
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

#ifndef __IZQUIERDA_H
#define __IZQUIERDA_H


/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

/*
** ===================================================================
**     Method      :  IZQUIERDA_GetVal (bean BitIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pin and returns it
**           b) direction = Output : returns the last written value
**         Note: This bean is set to work in Output direction only.
**     Parameters  : None
**     Returns     :
**         ---        - Input value (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
** ===================================================================
*/
#define IZQUIERDA_GetVal() ((PTB) & 2)

/*
** ===================================================================
**     Method      :  IZQUIERDA_PutVal (bean BitIO)
**
**     Description :
**         This method writes the new output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Value      - Output value (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
**     Returns     : Nothing
** ===================================================================
*/
void IZQUIERDA_PutVal(byte Value);




/*
** ===================================================================
**     Method      :  IZQUIERDA_ClrVal (bean BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define IZQUIERDA_ClrVal() (PTB &= ~2)

/*
** ===================================================================
**     Method      :  IZQUIERDA_SetVal (bean BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define IZQUIERDA_SetVal() (PTB |= 2)


#endif /* __IZQUIERDA_H*/
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 03.23 for 
**     the Motorola HC08 series of microcontrollers.
**
** ###################################################################
*/
