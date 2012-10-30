/*
============================================================================
 Name		 : SpaceInvadersHighscoreView.h
 Author	     : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : Declares view class for application.
============================================================================
*/

#ifndef __SPACEINVADERSHIGHSCOREVIEW_h__
#define __SPACEINVADERSHIGHSCOREVIEW_h__

// INCLUDES
#include <coecntrl.h>
#include "HighscoreHolder.h"

class CSpaceInvadersAppUi;


// CLASS DECLARATION
/**
 * Draws the highscores -list to the display.
 */

class CSpaceInvadersHighscoreView : public CCoeControl
	{
	public: // New methods

		/**
		* NewL.
		* Two-phased constructor.
		* Create a CSpaceInvadersAppView object, which will draw itself to aRect.
		* @param aRect The rectangle this view will be drawn to.
		* @return a pointer to the created instance of CSpaceInvadersAppView.
		*/
		static CSpaceInvadersHighscoreView* NewL( const TRect& aRect, CSpaceInvadersAppUi* aAppUi, THighscoreHolder* aHolder);

		/**
		* NewLC.
		* Two-phased constructor.
		* Create a CSpaceInvadersAppView object, which will draw itself
		* to aRect.
		* @param aRect Rectangle this view will be drawn to.
		* @return A pointer to the created instance of CSpaceInvadersAppView.
		*/
		static CSpaceInvadersHighscoreView* NewLC( const TRect& aRect, CSpaceInvadersAppUi* aAppUi, THighscoreHolder* aHolder);

		/**
		* ~CSpaceInvadersAppView
		* Virtual Destructor.
		*/
		virtual ~CSpaceInvadersHighscoreView();

	public:  // Functions from base classes

		/**
		* From CCoeControl, Draw
		* Draw this CSpaceInvadersAppView to the screen.
		* @param aRect the rectangle of this view that needs updating
		*/
		void Draw( const TRect& aRect ) const;

		/**
		* From CoeControl, SizeChanged.
		* Called by framework when the view size is changed.
		*/
		virtual void SizeChanged();

	private: // Constructors

		/**
		* ConstructL
		* 2nd phase constructor.
		* Perform the second phase construction of a
		* CSpaceInvadersAppView object.
		* @param aRect The rectangle this view will be drawn to.
		*/
		void ConstructL( const TRect& aRect, CSpaceInvadersAppUi* aAppUi, THighscoreHolder* aHolder);

		/**
		* CSpaceInvadersAppView.
		* C++ default constructor.
		*/
		CSpaceInvadersHighscoreView();

	public: // Methods

		/**
		 * Handles user inputs.
		 */
		TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
		
		/**
		 * Draws an item to the higscores list.
		 */
		void DrawHighscoreItem(TInt aPoints, TInt aOrder, CWindowGc& aGc) const;
		
		/**
		 * Draws the command to go back to start screen.
		 */
		void DrawBackCommand(CWindowGc& aGc) const;
		
	private:
	
		/**
		 * A pointer to the application UI.
		 */
		CSpaceInvadersAppUi* iAppUi;
		
		/**
		 * The highscore holder used to draw highscores.
		 */
		THighscoreHolder* iHolder;

	};

#endif // __SPACEINVADERSHIGHSCOREVIEW_h__

// End of File
