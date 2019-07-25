/*
** ###################################################################
**
**     Filename  : CtrlCam.C
**
**     Project   : CtrlCam
** 
**     Processor : MC68HC908GP32CFB
**
**     Version   : Driver 01.00
**
**     Compiler  : Metrowerks HC08 C Compiler V-5.0.13
**
**     Date/Time : 1/20/martes, 13:05
**
**     Abstract  :
**
**         Main module. 
**         Here is to be placed user's code.
**
**     Settings  :
**
**
**     Contents  :
**
**         No public methods
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
/* MODULE CtrlCam */

//#pragma MESSAGE DISABLE C1420 /* WARNING C1420: Result of function-call is ignored. You can uncomment this line to disable this compiler warning */

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
/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "CtrlCam.h"
#include <ctype.h>
#include <stdlib.h>


//Funciones para protocolo serie

#define BUFFER_SIZE 6

#define INTERRUMPIR	0
#define FOCO_MAS	1
#define FOCO_MENOS	2
#define ZOOM_MAS	3
#define ZOOM_MENOS	4
#define IZQUIERDA	5
#define	DERECHA		6
#define ARRIBA		7
#define ABAJO		8

const char teclado[4][4]={ 1,2,3,'A',
				 		   4,5,6,'B',
						   7,8,9,'D',
				    	  'C',0,'E','F'};


byte ValDisp;

char DisplayBuff[3];
char rsbuff[BUFFER_SIZE];
char strBuff[3];

char next_in=0;
word tmp;

void WriteDisplay (char value)
{
	ENABLE_LED1_ClrVal();
	LED_VAL_PutVal (value&0x0f);
	ENABLE_LED1_SetVal();

	ENABLE_LED2_ClrVal();
	LED_VAL_PutVal ((value>>4)&0x0f);
	ENABLE_LED2_SetVal();
}


void InicializaDisplay ()
{
	DisplayBuff[0]=0;
	DisplayBuff[1]=0;
	DisplayBuff[1]=0;
	ValDisp = 0;
	WriteDisplay (0);
}

byte BitPos2Dec (byte code)
{
	byte n;
	byte pos;
	byte chr=code;
	
	for (pos=0,n=1;pos<9;n<<=1,pos++)
	{
		chr = code&n;
		if (chr)
			return pos;
	}
	
	return pos;
}
word kbhit ()
{
	unsigned int n;
	word code;
	Teclado_GetKeyCode(&code);
	for (n=0;n<1000;n++);
	Teclado_GetKeyCode(&code);
	return code;
}
void main(void)
{
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
	bool err,bFlag;
	word code;
	word total;
	byte tecla;
	

	InicializaDisplay();		
	Timer_Enable();
	Teclado_Enable();

	while (TRUE)
	{	
		if (!JoistickAction_GetVal())
		{
			bFlag=FALSE;
			Seleccion_PutVal (tmp);
			Timer_Disable();
			Flash_SetVal();
			DisplayBuff[0]=0;
			DisplayBuff[1]=0;
		}
		
		if ((code=kbhit()))
		{
			Timer_Disable();
			Flash_SetVal();
			
			tecla= teclado[BitPos2Dec(code)][BitPos2Dec(code>>8)];		
			switch (tecla)
			{
				//Tecla de intro
				case 'F':					
					if (bFlag)
					{
						bFlag=FALSE;
						Seleccion_PutVal (tmp);
						Timer_Disable();
						Flash_SetVal();
						DisplayBuff[0]=0;
						DisplayBuff[1]=0;
					}
				break;

				//Tecla de borrado
				case 'C':
					InicializaDisplay();
					Timer_Enable();
				break;
				
				
				case 'A':	//FOCO +
					bFlag=FALSE;
					Seleccion_PutVal (tmp);
					Timer_Disable();
					Flash_SetVal();
					DisplayBuff[0]=0;
					DisplayBuff[1]=0;
				
					FOCOMAS_SetVal();
					while (kbhit());
					FOCOMAS_ClrVal();
				break;
				
				case 'B':	//FOCO -
					bFlag=FALSE;
					Seleccion_PutVal (tmp);
					Timer_Disable();
					Flash_SetVal();
					DisplayBuff[0]=0;
					DisplayBuff[1]=0;
					
					FOCOMENOS_SetVal();
					while (kbhit());
					FOCOMENOS_ClrVal();

				break;
				
				case 'D':	//ZOOM +
					bFlag=FALSE;
					Seleccion_PutVal (tmp);
					Timer_Disable();
					Flash_SetVal();
					DisplayBuff[0]=0;
					DisplayBuff[1]=0;
				
					ZOOMMAS_SetVal();
					while (kbhit());
					ZOOMMAS_ClrVal();
				break;
				
				
				case 'E':	//ZOOM -
					bFlag=FALSE;
					Seleccion_PutVal (tmp);
					Timer_Disable();
					Flash_SetVal();
					DisplayBuff[0]=0;
					DisplayBuff[1]=0;
				
					ZOOMMENOS_SetVal();
					while (kbhit());
					ZOOMMENOS_ClrVal();
				break;
				
				
				default:
					bFlag=TRUE;
					DisplayBuff[1]=DisplayBuff[0];
					DisplayBuff[0]=tecla;

					ValDisp = MAKEBYTE (DisplayBuff[0],DisplayBuff[1]);
					WriteDisplay (ValDisp);
					
					strBuff[0]=DisplayBuff[1]+'0';
					strBuff[1]=DisplayBuff[0]+'0';
					strBuff[2]=0;				
					tmp = atoi (strBuff);
					
					Timer_Enable();
				break;
			}				
			while (kbhit());

		}
	 }
 }


void DoFunction (byte function)
{
	
	Flash_SetVal();
	Timer_Disable();

	//Activamos relé
	switch (function)
	{
		case INTERRUMPIR:
			ZOOMMAS_ClrVal();
			ZOOMMENOS_ClrVal();
			FOCOMAS_ClrVal();
			FOCOMENOS_ClrVal();
			DERECHA_ClrVal();
			IZQUIERDA_ClrVal();
			ARRIBA_ClrVal();
			ABAJO_ClrVal();
		break;
		
		case ZOOM_MAS:
			ZOOMMENOS_ClrVal();
			ZOOMMAS_SetVal();
		break;

		case ZOOM_MENOS:
			ZOOMMAS_ClrVal();
			ZOOMMENOS_SetVal();
		break;
		
		case FOCO_MAS:
			FOCOMENOS_ClrVal();
			FOCOMAS_SetVal();
		break;
		
		case FOCO_MENOS:
			FOCOMAS_ClrVal();
			FOCOMENOS_SetVal();		
		break;
		
		case ARRIBA:
			ABAJO_ClrVal();
			ARRIBA_SetVal();
		break;
		
		case ABAJO:
			ARRIBA_ClrVal();
			ABAJO_SetVal();
		break;
		
		case DERECHA:
			IZQUIERDA_ClrVal();
			DERECHA_SetVal();
		break;
		
		case IZQUIERDA:
			DERECHA_ClrVal();
			IZQUIERDA_SetVal();
		break;		
	}
}
 
void OnRxChar(void)
{
	static char start=0;
	static char str[3];
	byte bcdIndi;
	char cTmp,func;

	while (SERIE_GetCharsInRxBuf())
	{
		
		if ((SERIE_RecvChar(&cTmp))==ERR_OK)
		{
			SERIE_SendChar (cTmp);
			
			rsbuff[next_in]=cTmp;
			
			if (start==1 && next_in==3)
			{
				bcdIndi = MAKEBYTE (rsbuff[1]-'0',rsbuff[0]-'0');

				str[0]=rsbuff[0];
				str[1]=rsbuff[1];
				str[2]=0;
				tmp = atoi (str);
				
				str[0]=rsbuff[2];
				str[1]=rsbuff[3];
				str[2]=0;
				func = atoi (str);

				start=0;
	
				//Seleccionamos el indicativo
				WriteDisplay (bcdIndi);
				Seleccion_PutVal (tmp);
				DoFunction (func);
			}

			if (rsbuff[next_in]=='S' || rsbuff[next_in]=='s')
			{
				start=1;
				next_in=0;
			}
			else
				next_in++;

		   if(next_in>=BUFFER_SIZE-1)
			   next_in=0; 
		}
	}
}
 
 void OnTimer (void)
 {
 	Flash_NegVal();
 }
 
/* END CtrlCam */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 02.89 for 
**     the Motorola HC08 series of microcontrollers.
**
** ###################################################################
*/
