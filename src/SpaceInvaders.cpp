/*
============================================================================
 Name		: SpaceInvaders.cpp
 Author	  : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : Main application class
============================================================================
*/

// INCLUDE FILES
#include <eikstart.h>
#include "SpaceInvadersApplication.h"


LOCAL_C CApaApplication* NewApplication()
	{
	return new CSpaceInvadersApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication( NewApplication );
	}

