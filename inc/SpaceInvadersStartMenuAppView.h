/*
============================================================================
 Name		 : SpaceInvadersStartMenuAppView.h
 Author	     : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : Declares view class for application.
============================================================================
*/

#ifndef __SPACEINVADERSSTARTMENUAPPVIEW_h__
#define __SPACEINVADERSSTARTMENUAPPVIEW_h__

_LIT(KNewGameText, "NEW GAME");
_LIT(KHighscoresText, "HIGHSCORES");
_LIT(KExitText, "EXIT");

// INCLUDES
#include <coecntrl.h>
#include "SpaceInvadersAppUi.h"
#include "HighscoreHolder.h"

class CSpaceInvadersAppUi;

// CLASS DECLARATION
/**
 * CSpaceInvadersStartMenuAppView application view class.
 * Displays the starting menu screen of the game.
 */

class CSpaceInvadersStartMenuAppView : public CCoeControl
{
	public: // New methods

		/**
		* NewL.
		* Two-phased constructor.
		* Create a CStartMenuAppView object, which will draw itself to aRect.
		* @param aRect The rectangle this view will be drawn to.
		* @return a pointer to the created instance of CStartMenuAppView.
		*/
		static CSpaceInvadersStartMenuAppView* NewL( const TRect& aRect,
				                                    CSpaceInvadersAppUi* aAppUi,
				                                    THighscoreHolder* aHolder);

		/**
		* NewLC.
		* Two-phased constructor.
		* Create a CStartMenuAppView object, which will draw itself
		* to aRect.
		* @param aRect Rectangle this view will be drawn to.
		* @return A pointer to the created instance of CStartMenuAppView.
		*/
		static CSpaceInvadersStartMenuAppView* NewLC( const TRect& aRect,
				                                    CSpaceInvadersAppUi* aAppUi,
				                                    THighscoreHolder* aHolder);

		/**
		* ~CStartMenuAppView
		* Virtual Destructor.
		*/
		virtual ~CSpaceInvadersStartMenuAppView();
		
	public:  // Functions from base classes

		/**
		* From CCoeControl, Draw
		* Draw this CStartMenuAppView to the screen.
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
		* CStartMenuAppView object.
		* @param aRect The rectangle this view will be drawn to.
		*/
		void ConstructL( const TRect& aRect, CSpaceInvadersAppUi* aAppUi,
				         THighscoreHolder* aHolder);

		/**
		* CSpaceInvadersStartMenuAppView.
		* C++ default constructor.
		*/
		CSpaceInvadersStartMenuAppView();
		
	public:
	
		/**
		 * Draws the start menu options ( new game, highscores, exit)
		 */
		void DrawStartMenuOptions(CWindowGc& aGc) const;
		
		/**
		 * Draws the game's logo
		 */
		void DrawGameLogo(CWindowGc& aGc) const;
		
		/**
		 * Gets the selected option.
		 */
		TInt SelectedOption() const;
		
		/**
		 * Sets the selected option.
		 */
		void SetSelectedOption(TInt aValue);
		
		/**
		 * Gets the pointer to the application UI.
		 */
		CSpaceInvadersAppUi* AppUi();
		
		/**
		 * Sets the pointer to the application UI.
		 */
		void SetAppUi(CSpaceInvadersAppUi* aAppUi);
		
		/**
		 * Handles key events from user.
		 */
	    TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,
	    		                     TEventCode aType);
		
	private:
	
		/**
		 * The selected option.
		 */
		TInt iSelectedOption;
		
		/**
		 * Pointer to the application UI.
		 */
		CSpaceInvadersAppUi* iAppUi;
		
		/**
		 * Pointer to the highscore holder.
		 */
		THighscoreHolder* iHolder;
		
		/**
		 * Bitmap for the game logo.
		 */
		CFbsBitmap* iBitmapLogo;
		
		/**
		 * Draws an option to the start menu.
		 */
		void DrawStartMenuItem(TInt aOrder,
				               TDesC* aText,
                			   CWindowGc& aGc) const;
	
};

#endif // __SPACEINVADERSSTARTMENUAPPVIEW_h__

// End of File
