/*
============================================================================
 Name		: SpaceInvadersApplication.h
 Author	  : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : Declares main application class.
============================================================================
*/

#ifndef __SPACEINVADERSAPPLICATION_H__
#define __SPACEINVADERSAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "SpaceInvaders.hrh"


// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidSpaceInvadersApp = { _UID3 };


// CLASS DECLARATION

/**
* CSpaceInvadersApplication application class.
* Provides factory to create concrete document object.
* An instance of CSpaceInvadersApplication is the application part of the
* AVKON application framework for the SpaceInvaders example application.
*/
class CSpaceInvadersApplication : public CAknApplication
	{
	public: // Functions from base classes

		/**
		* From CApaApplication, AppDllUid.
		* @return Application's UID (KUidSpaceInvadersApp).
		*/
		TUid AppDllUid() const;

	protected: // Functions from base classes

		/**
		* From CApaApplication, CreateDocumentL.
		* Creates CSpaceInvadersDocument document object. The returned
		* pointer in not owned by the CSpaceInvadersApplication object.
		* @return A pointer to the created document object.
		*/
		CApaDocument* CreateDocumentL();
	};

#endif // __SPACEINVADERSAPPLICATION_H__

// End of File
