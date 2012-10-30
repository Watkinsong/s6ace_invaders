/*
============================================================================
 Name		 : SpaceInvadersAppUi.h
 Author	     : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : Declares UI class for application.
============================================================================
*/

#ifndef __SPACEINVADERSAPPUI_h__
#define __SPACEINVADERSAPPUI_h__

// INCLUDES
#include <aknappui.h>
#include "SpaceInvadersStartMenuAppView.h"
#include "ShipEngine.h"
#include "SpaceInvadersAudioPlayer.h"
#include "SpaceInvadersHighscoreView.h"
#include "HighscoreHolder.h"


// FORWARD DECLARATIONS
class CSpaceInvadersAppView;
class CSpaceInvadersStartMenuAppView;


// CLASS DECLARATION
/**
* CSpaceInvadersAppUi application UI class.
* Interacts with the user through the UI and request message processing
* from the handler class
*/
class CSpaceInvadersAppUi : public CAknAppUi
	{
	public: // Constructors and destructor

		/**
		* ConstructL.
		* 2nd phase constructor.
		*/
		void ConstructL();

		/**
		* CSpaceInvadersAppUi.
		* C++ default constructor. This needs to be public due to
		* the way the framework constructs the AppUi
		*/
		CSpaceInvadersAppUi();

		/**
		* ~CSpaceInvadersAppUi.
		* Virtual Destructor.
		*/
		virtual ~CSpaceInvadersAppUi();
		
	private:  // Functions from base classes

		/**
		*  HandleStatusPaneSizeChange.
		*  Called by the framework when the application status pane
 		*  size is changed.
		*/
		void HandleStatusPaneSizeChange();
		
	public:
	
		/**
		 * Gets the pointer to the AppView (the gameplay view)
		 */
		CSpaceInvadersAppView* AppView();
		
		/**
		 * Sets the pointer to AppView.
		 */
		void SetAppView(CSpaceInvadersAppView* aAppView);
		
		/**
		 * Gets the pointer to start menu view.
		 */
		CSpaceInvadersStartMenuAppView* StartMenuView();
		
		/**
		 * Gets the pointer to highscores view.
		 */
		CSpaceInvadersHighscoreView* HighscoreView();
		
		/**
		 * Sets the pointer to start menu view.
		 */
		void SetStartMenuView(CSpaceInvadersStartMenuAppView* aStartMenuView);
	 	
		/**
		 * Handles key events from user.
		 */
		TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

		/**
		 * Changes the game view.
		 */
		void ChangeView(CCoeControl *aView);
		
		/**
		 * Updates the current view.
		 */
		void UpdateView();
		
		/**
		 * Saves the player's points and exits the game.
		 */
		void ExitGame();
		
		/**
		 * Sets the ship to starting position.
		 */
		void InitShip();
		
	private: // Data

		/**
		* The application view
		* Owned by CSpaceInvadersAppUi
		*/
		CSpaceInvadersAppView* iAppView;

		/**
		 * Start menu view.
		 */
		CSpaceInvadersStartMenuAppView* iStartMenuView;

		/**
		 * High score view.
		 */
		CSpaceInvadersHighscoreView* iHighscoreView;

		/**
		 * A CCoeControl -pointer to point to the current view.
		 */
		CCoeControl* iCurrentView;

		/**
		 * The ship controlled by the user.
		 */
		CShipEngine* iShip;

		/**
		 * The audioplayer, responsible for playing the game's background music.
		 */
		CSpaceInvadersAudioPlayer* iAudioPlayer;

		/**
		 * The highscores view.
		 */
		THighscoreHolder* iHighscoreHolder;

	};

#endif // __SPACEINVADERSAPPUI_h__

// End of File
