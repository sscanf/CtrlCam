/*
** ###################################################################
**
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**
**     Filename  : Bean1.C
**
**     Project   : ctrlcam
** 
**     Processor : MC68HC908GP32CFB
**
**     Beantype  : KeyboardMatrix
**
**     Version   : Bean 01.001, Driver 01.12, CPU db: 2.87.041
**
**     Compiler  : Metrowerks HC08 C Compiler V-5.0.13
**
**     Date/Time : 1/20/martes, 18:21
**
**     Abstract  :
**
**         This bean implements a general keyboard matrix. Maximal size 
**         of the matrix is 8x8. The key of the keyboard is represented 
**         by 16-bit value called as "keycode". Keycode represents 
**         coordinates of a pressed key. Low byte of the keycode represents
**         a number of a column and high byte of the keycode represents 
**         a number of the row.
**
**     Settings  :
**
**         Pull resistor               : pull up
**         Keyboard uses interrupt     : yes
**         External interrupt pin      : IRQ
**         Matrix                      : 
**         Buffer size                 : 30
**         Rows
**         Row0 pin                    : PTA0_KBD0   
**         Row1 pin                    : PTA1_KBD1   
**         Row2 pin                    : PTA2_KBD2   
**         Row3 pin                    : PTA3_KBD3   
**         Columns
**         Column0 pin                 : PTA4_KBD4   
**         Column1 pin                 : PTA5_KBD5   
**         Column2 pin                 : PTA6_KBD6   
**         Column3 pin                 : PTA7_KBD7   
**         Initialization
**         Enable in init. code        : no
**         Events enabled in init.     : yes
**
**         User handling procedure     : Bean1_OnKeyDown
**         Interrupt Priority          : 0
**         This event is called when key is pressed
**
**
**     Contents  :
**
**         Enable     - byte Bean1_Enable(void);
**         Disable    - byte Bean1_Disable(void);
**         GetKeyCode - byte Bean1_GetKeyCode(word *key);
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


/* MODULE Bean1. */
#pragma MESSAGE DISABLE C5660 /* WARNING C5660: Removed dead code */

#include "Events.h"
#include "LED_VAL.h"
#include "SERIE.h"
#include "ENABLE_LED1.h"
#include "ENABLE_LED2.h"
#include "Bean1.h"
#include "Inhr1.h"
#include "Inhr2.h"
#include "Inhr3.h"
#include "Inhr4.h"
#include "Inhr5.h"
#include "Inhr6.h"
#include "Inhr7.h"
#include "Inhr8.h"
#include "Inhr9.h"
#include "Bean1.h"

static word keyBuff[30];
static byte keyBuff_Start;
static byte keyBuff_End;
static byte keyBuff_Size;
byte EnUser;
/*
** ===================================================================
**     Method      :  Bean1_ScanKeyboard (bean KeyboardMatrix)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
static word ScanKeyboard(void)
{
  word newKey;
  byte newColumn;
  newKey = 0;
  newColumn = 0;
  
  Inhr2_ClrVal();
  newColumn = 0;
  if (!Inhr6_GetVal())
    newColumn |= 1;
  if (!Inhr7_GetVal())
    newColumn |= 2;
  if (!Inhr8_GetVal())
    newColumn |= 4;
  if (!Inhr9_GetVal())
    newColumn |= 8;
  if (newColumn) {
    newKey |= 256 | newColumn;
  }
  Inhr2_SetVal();
  Inhr3_ClrVal();
  newColumn = 0;
  if (!Inhr6_GetVal())
    newColumn |= 1;
  if (!Inhr7_GetVal())
    newColumn |= 2;
  if (!Inhr8_GetVal())
    newColumn |= 4;
  if (!Inhr9_GetVal())
    newColumn |= 8;
  if (newColumn) {
    newKey |= 512 | newColumn;
  }
  Inhr3_SetVal();
  Inhr4_ClrVal();
  newColumn = 0;
  if (!Inhr6_GetVal())
    newColumn |= 1;
  if (!Inhr7_GetVal())
    newColumn |= 2;
  if (!Inhr8_GetVal())
    newColumn |= 4;
  if (!Inhr9_GetVal())
    newColumn |= 8;
  if (newColumn) {
    newKey |= 1024 | newColumn;
  }
  Inhr4_SetVal();
  Inhr5_ClrVal();
  newColumn = 0;
  if (!Inhr6_GetVal())
    newColumn |= 1;
  if (!Inhr7_GetVal())
    newColumn |= 2;
  if (!Inhr8_GetVal())
    newColumn |= 4;
  if (!Inhr9_GetVal())
    newColumn |= 8;
  if (newColumn) {
    newKey |= 2048 | newColumn;
  }
  Inhr5_SetVal();
  return newKey;
}
/*
** ===================================================================
**     Method      :  Bean1_GetKeyCode (bean KeyboardMatrix)
**
**     Description :
**         Method gets code for pressed key
**     Parameters  :
**         NAME            - DESCRIPTION
**       * key             - Keycode
**     Returns     :
**         ---             - Error
** ===================================================================
*/
byte Bean1_GetKeyCode(word *key)
{
  if (!EnUser)
    return ERR_DISABLED;
  if (keyBuff_Size == 0) {
    return ERR_NOTAVAIL;
  }
  else {
    *key = keyBuff[keyBuff_Start];
    keyBuff_Size--;
    keyBuff_Start++;
    if (keyBuff_Start == 30)
      keyBuff_Start = 0;
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  Bean1_Init (bean KeyboardMatrix)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
void Bean1_Init(void)
{
  EnUser=FALSE;
  keyBuff_Start = 0;
  keyBuff_End = 0;
  keyBuff_Size = 0;
  Inhr2_ClrVal();
  Inhr3_ClrVal();
  Inhr4_ClrVal();
  Inhr5_ClrVal();
}

/*
** ===================================================================
**     Method      :  Bean1_Disable (bean KeyboardMatrix)
**
**     Description :
**         Disable A/D convertor bean
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
byte Bean1_Disable(void)
{
  Inhr1_Disable();
   EnUser = FALSE;
   return ERR_OK;
}

/*
** ===================================================================
**     Method      :  Bean1_Enable (bean KeyboardMatrix)
**
**     Description :
**         Enable A/D convertor bean
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
byte Bean1_Enable(void)
{
  Inhr1_Enable();
  EnUser = TRUE;
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  Bean1_Inhr1_OnInterrupt (bean KeyboardMatrix)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
void Inhr1_OnInterrupt(void)
{
  word newKey;

  if (keyBuff_Size < 30) {
    Inhr1_Disable();
    Inhr2_SetVal();
    Inhr3_SetVal();
    Inhr4_SetVal();
    Inhr5_SetVal();
    newKey = ScanKeyboard();
    Inhr2_ClrVal();
    Inhr3_ClrVal();
    Inhr4_ClrVal();
    Inhr5_ClrVal();
    Inhr1_Enable();
    if (newKey!=0) {
      keyBuff[keyBuff_End] = newKey;
      keyBuff_End++;
      if (keyBuff_End == 30)
        keyBuff_End = 0;
      keyBuff_Size++;
    }
  }
    Bean1_OnKeyDown();
 }

/* END Bean1. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 02.89 for 
**     the Motorola HC08 series of microcontrollers.
**
** ###################################################################
*/

