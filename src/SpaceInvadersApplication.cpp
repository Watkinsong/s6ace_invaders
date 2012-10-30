/*
============================================================================
 Name		: SpaceInvadersApplication.cpp
 Author	  : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : Main application class
============================================================================
*/

// INCLUDE FILES
#include "SpaceInvaders.hrh"
#include "SpaceInvadersDocument.h"
#include "SpaceInvadersApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CSpaceInvadersApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CSpaceInvadersApplication::CreateDocumentL()
	{
	// Create an SpaceInvaders document, and return a pointer to it
	return (static_cast<CApaDocument*>
					( CSpaceInvadersDocument::NewL( *this ) ) );
	}

// -----------------------------------------------------------------------------
// CSpaceInvadersApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CSpaceInvadersApplication::AppDllUid() const
	{
	// Return the UID for the SpaceInvaders application
	return KUidSpaceInvadersApp;
	}

// End of File
