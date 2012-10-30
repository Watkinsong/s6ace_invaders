/*
============================================================================
 Name		 : SpaceInvadersAppView.h
 Author	     : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : Declares view class for application.
============================================================================
*/

#ifndef __SPACEINVADERSAPPVIEW_h__
#define __SPACEINVADERSAPPVIEW_h__
#define alien_vertical_move = 20
#define alien_horizontal_move = 30

// INCLUDES
#include <coecntrl.h>
#include "ShipEngine.h"
#include "HighscoreHolder.h"
#include <w32std.h>

class CSpaceInvadersAppUi;

// CLASS DECLARATION
/**
 * CSpaceInvadersAppView application UI class.
 * Draws the game screen and updates the game mechanics.
 */

class CSpaceInvadersAppView : public CCoeControl
	{
	public: // New methods

		/**
		* NewL.
		* Two-phased constructor.
		* Create a CSpaceInvadersAppView object, which will draw itself to aRect.
		* @param aRect The rectangle this view will be drawn to.
		* @return a pointer to the created instance of CSpaceInvadersAppView.
		*/
		static CSpaceInvadersAppView* NewL( const TRect& aRect,
				                            CSpaceInvadersAppUi* aAppUi,
				                            CShipEngine* aShip,
				                            THighscoreHolder* aHolder);

		/**
		* NewLC.
		* Two-phased constructor.
		* Create a CSpaceInvadersAppView object, which will draw itself
		* to aRect.
		* @param aRect Rectangle this view will be drawn to.
		* @return A pointer to the created instance of CSpaceInvadersAppView.
		*/
		static CSpaceInvadersAppView* NewLC( const TRect& aRect,
				                             CSpaceInvadersAppUi* aAppUi,
				                             CShipEngine* aShip,
				                             THighscoreHolder* aHolder);

		/**
		* ~CSpaceInvadersAppView
		* Virtual Destructor.
		*/
		virtual ~CSpaceInvadersAppView();

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
		void ConstructL( const TRect& aRect, CSpaceInvadersAppUi* aAppUi,
				         CShipEngine* aShip, THighscoreHolder* aHolder);

		/**
		* CSpaceInvadersAppView.
		* C++ default constructor.
		*/
		CSpaceInvadersAppView();

	public: // Methods

	/**
	 * Handles key events from user.
	 */
	TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

	/**
	 * Starts the CPeriodic -timer for game loop.
	 */
	void StartTimerL();
	
	/**
	 * Stops the game loop timer.
	 */
	void StopTimer();
	
	/**
	 * Static method for the CPeriodic - object to call on every period.
	 */
	static TInt Tick(TAny* aObject);
	
	/**
	 * Updates the states of the objects of the game and checks for collisions.
	 */
	void NextTick();
	
	/**
	 * Create alien CShipEngine-objects and set them to starting positions.
	 */
	void InitAliens();
	
	/**
	 * Saves the points, initializes the aliens and stops the game loop timer.
	 * Called when the player dies or finishes the game.
	 */
	void GameOver();
	
	/**
	 * Draws the background of the game.
	 */
	void DrawBackground(CWindowGc& aGc) const;
	
	/**
	 * Draws the player's ship.
	 */
	void DrawShip(CWindowGc& aGc) const;
	
	/**
	 * Draws the aliens.
	 */
	void DrawAliens(CWindowGc& aGc) const;
	
	/**
	 * Draws the player's points to the top of the screen.
	 */
	void DrawPoints(CWindowGc& aGc) const;
	
	/**
	 * Draws the command for quitting the game to the down-left of the screen.
	 */
	void DrawQuitCommand(CWindowGc& aGc) const;
	
	/**
	 * Updates the coordinates of the player's ship to move it up.
	 */
	void MoveShipUp() const;
	
	/**
	 * Updates the coordinates of the player's ship to move it right.
	 */
	void MoveShipRight() const;
	
	/**
	 * Updates the coordinates of the player's ship to move it down.
	 */
	void MoveShipDown() const;
	
	/**
	 * Updates the coordinates of the player's ship to move it left.
	 */
	void MoveShipLeft() const;

	void LoadBitmapsL();
	
	private: // Data

		/**
		 * Counter to measure the need to update (move) the aliens.
		 */
		TInt iTickCounter;
		
		/**
		 * Counter to measure the need for an alien to shoot.
		 */
		TInt iShotCounter;
		
		/**
		 * The ship controlled by the player.
		 */
		CShipEngine* iShip;
		
		/**
		 * The number of aliens.
		 */
		TInt iTotalAliens;
		
		/**
		 * Counts remaining aliens to know when the game has ended.
		 */
		TInt iRemainingAliens;
		
		/**
		 * Array of CShipEngine-pointers.
		 */
		TFixedArray<CShipEngine*, 18> iAlienArray;

		/**
		 * Pointer to the application UI.
		 */
		CSpaceInvadersAppUi* iAppUi;
		
		/**
		 * The timer for the game loop.
		 */
		CPeriodic* iPeriodic;

		/**
		 * Maximum number of aliens' horizontal moves.
		 */
		TInt iMaxHorizontalMoves;
		
		/**
		 * Counter to keep track when the aliens need to descend.
		 */
		TInt iHorizontalMoves;
		
		/**
		 * The direction where the aliens should be moved.
		 */
		enum TDirection{ERight, ELeft};
		
		/**
		 * The direction of the aliens.
		 */
		TDirection iAlienDirection;
		
		/**
		 * The highscore holder to keep track of player's points.
		 */
		THighscoreHolder* iHolder;
		
		/**
		 * Bitmap for the ship.
		 */
		CFbsBitmap* iBitmapShip;
		
		/**
		 * Bitmap for the first alien type.
		 */
		CFbsBitmap* iBitmapAlien1;
		
		/**
		 * Bitmap for the second alien type.
		 */
		CFbsBitmap* iBitmapAlien2;
		
		/**
		 * Bitmap for the third alien type.
		 */
		CFbsBitmap* iBitmapAlien3;
		
		/**
		 * Bitmap for the shot.
		 */
		CFbsBitmap* iBitmapShot;
		
	};

#endif // __SPACEINVADERSAPPVIEW_h__

// End of File
