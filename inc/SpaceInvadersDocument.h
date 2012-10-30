/*
============================================================================
 Name		 : SpaceInvadersDocument.h
 Author	     : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : Declares document class for application.
============================================================================
*/

#ifndef __SPACEINVADERSDOCUMENT_h__
#define __SPACEINVADERSDOCUMENT_h__

// INCLUDES
#include <akndoc.h>
#include "HighscoreHolder.h"

// FORWARD DECLARATIONS
class CSpaceInvadersAppUi;
class CEikApplication;


// CLASS DECLARATION

/**
* CSpaceInvadersDocument application class.
* An instance of class CSpaceInvadersDocument is the Document part of the
* AVKON application framework for the SpaceInvaders example application.
*/
class CSpaceInvadersDocument : public CAknDocument
	{
	public: // Constructors and destructor

		/**
		* NewL.
		* Two-phased constructor.
		* Construct a CSpaceInvadersDocument for the AVKON application aApp
		* using two phase construction, and return a pointer
		* to the created object.
		* @param aApp Application creating this document.
		* @return A pointer to the created instance of CSpaceInvadersDocument.
		*/
		static CSpaceInvadersDocument* NewL( CEikApplication& aApp );

		/**
		* NewLC.
		* Two-phased constructor.
		* Construct a CSpaceInvadersDocument for the AVKON application aApp
		* using two phase construction, and return a pointer
		* to the created object.
		* @param aApp Application creating this document.
		* @return A pointer to the created instance of CSpaceInvadersDocument.
		*/
		static CSpaceInvadersDocument* NewLC( CEikApplication& aApp );

		/**
		* ~CSpaceInvadersDocument
		* Virtual Destructor.
		*/
		virtual ~CSpaceInvadersDocument();

	public: // Functions from base classes

		/**
		* CreateAppUiL
		* From CEikDocument, CreateAppUiL.
		* Create a CSpaceInvadersAppUi object and return a pointer to it.
		* The object returned is owned by the Uikon framework.
		* @return Pointer to created instance of AppUi.
		*/
		CEikAppUi* CreateAppUiL();
		
		/**
		 * Saves the state of the game (= the highscores)
		 */
		void StoreL(CStreamStore& aStore, CStreamDictionary& aStreamDic) const;

		/**
		 * Resteres the state of the game.
		 */
		void RestoreL(const CStreamStore& aStore, const CStreamDictionary& aStreamDic);
		
		/**
		 * Calls for parent class' OpenFile -method.
		 */
		CFileStore* OpenFileL(TBool aDoOpen, const TDesC& aFilename, RFs& aFs);
		
		/**
		 * Sets the highscore holder.
		 */
		void SetHolder(THighscoreHolder* aHolder);
		
		/**
		 * Gets the pointer to the highscore holder.
		 */
		THighscoreHolder* Holder();

	private: // Constructors

		/**
		* ConstructL
		* 2nd phase constructor.
		*/
		void ConstructL();

		/**
		* CSpaceInvadersDocument.
		* C++ default constructor.
		* @param aApp Application creating this document.
		*/
		CSpaceInvadersDocument( CEikApplication& aApp );
		
		/**
		 * The highscore holder object to be stored and restored.
		 */
		THighscoreHolder* iHolder;

	};

#endif // __SPACEINVADERSDOCUMENT_h__

// End of File
