================================================================================
    BIBLIOTECA DE MICROSOFT FOUNDATION CLASS: WinCam Informaci�n general del proyecto
===============================================================================

El Asistente para aplicaciones ha creado esta WinCam aplicaci�n para usted. Esta 
aplicaci�n no s�lo muestra los conceptos b�sicos para utilizar Microsoft Foundation Classes,
sino que tambi�n es un punto de partida para escribir su aplicaci�n.

Este archivo contiene un resumen de lo que encontrar� en cada uno de los archivos que
componen su WinCam aplicaci�n.

WinCam.vcproj
    Este es el archivo de proyecto principal para proyectos de VC++ generados con un Asistente 
    para aplicaciones. Contiene informaci�n sobre la versi�n de Visual C++ que gener� el archivo e 
    informaci�n acerca de las plataformas, las configuraciones y las caracter�sticas del proyecto
    seleccionadas con el Asistente para aplicaciones.

WinCam.h
    Este es el archivo de encabezado principal para la aplicaci�n. Incluye otros
    encabezados espec�ficos del proyecto (incluyendo Resource.h) y declara la
    clase de la aplicaci�n CWinCamApp.

WinCam.cpp
    Este es el archivo de c�digo fuente principal de la aplicaci�n que contiene la
    clase de la aplicaci�n CWinCamApp.

WinCam.rc
    Esta es una lista de todos los recursos de Microsoft Windows que utiliza
    el programa. Incluye los iconos, mapas de bits y cursores almacenados en el
    subdirectorio RES. Este archivo se puede editar directamente en Microsoft
    Visual C++. Los recursos del proyecto est�n en 3082.

res\WinCam.ico
    Este es un archivo de icono, que se utiliza como icono de la aplicaci�n. El
    icono est� incluido en el archivo de recursos principal WinCam.rc.

res\WinCam.rc2
    Este archivo contiene recursos no editados por Microsoft 
    Visual C++. Debe ubicar todos los recursos no editables por
    el editor de recursos en este archivo.

/////////////////////////////////////////////////////////////////////////////

El Asistente para aplicaciones crea una clase de di�logo:
WinCamDlg.h, WinCamDlg.cpp - cuadro de di�logo
    Estos archivos contienen la clase CWinCamDlg. Esta clase define
    el comportamiento del cuadro de di�logo principal de la aplicaci�n. La plantilla del cuadro
    de di�logo est� en WinCam.rc, que se puede editar en Microsoft Visual C++.
/////////////////////////////////////////////////////////////////////////////

Otras caracter�sticas:

Controles ActiveX
    La aplicaci�n admite el uso de los controles ActiveX.

Compatibilidad para impresi�n y vista preliminar
    El Asistente para aplicaciones gener� el c�digo para controlar los comandos de impresi�n, de configuraci�n
    de impresi�n y de vista preliminar llamando a las funciones miembro en la clase CView desde la biblioteca MFC.
/////////////////////////////////////////////////////////////////////////////
Otros archivos est�ndar:

StdAfx.h, StdAfx.cpp
    Estos archivos se utilizan para compilar un archivo de encabezado precompilado (PCH)
    denominado WinCam.pch y un archivo de tipos precompilados denominado StdAfx.obj.

Resource.h
    Este es el archivo de encabezado est�ndar, que define nuevos identificadores de recursos.
    Microsoft Visual C++ lee y actualiza este archivo.

/////////////////////////////////////////////////////////////////////////////

Otras notas:

El Asistente para aplicaciones utiliza "ToDo:" para indicar las partes del c�digo fuente que
debe agregar o personalizar.

Si su aplicaci�n utiliza MFC en un archivo DLL compartido y la aplicaci�n est� en un
idioma distinto al idioma actual del sistema operativo, ser� necesario copiar 
los recursos MFC70XXX.DLL localizados correspondientes del CD-ROM de Microsoft
Visual C++ bajo el directorio Win\System en el directorio del sistema o 
system32 de su equipo y cambiar el nombre a MFCLOC.DLL. ("XXX" corresponde a la 
abreviatura del idioma. Por ejemplo, MFC70DEU.DLL contiene recursos traducidos
al alem�n.) Si no realiza esta operaci�n, algunos de los elementos de la interfaz de usuario de
su aplicaci�n permanecer�n en el idioma del sistema operativo.

/////////////////////////////////////////////////////////////////////////////
