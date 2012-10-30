/*
============================================================================
 Name		 : ShipEngine.h
 Author	     : Arttu Salonen
 Version	 :
 Copyright   : Copyright Arttu Salonen 2009
 Description : CShipEngine declaration
============================================================================
*/

#ifndef SHIPENGINE_H
#define SHIPENGINE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "ShotEngine.h"

// CLASS DECLARATION
/**
* The model-class for the ship controlled by the player and the aliens.
* Allocates TShotEngine dynamically.
*/

class CShipEngine : public CBase
{
public: // Constructors and destructor

		/**
		* Destructor.
		*/
	~CShipEngine();

		/**
		* Two-phased constructor.
		*/
	static CShipEngine* NewL(TInt aX, TInt aY);

		/**
		* Two-phased constructor.
		*/
	static CShipEngine* NewLC(TInt aX, TInt aY);

	/**
	 * Gets the abscissa of the ship.
	 */
	TInt X();
	
	/**
	 * Sets the abscissa of the ship.
	 */
	void SetX(TInt aX);
	
	/**
	 * Gets the ordinate of the ship.
	 */
	TInt Y();
	
	/**
	 * Sets the ordinate of the ship.
	 */
	void SetY(TInt aY);
	
	/**
	 * Called when the ship fires a shot.
	 */
	void ShotFired();
	
	/**
	 * Called when the ship has fired a shot and the shot is no longer needed.
	 */
	void ShotExpired();
	
	/**
	 * Sets the attribute depicting whether a shot has been fired.
	 */
	void SetHasFired(TBool aHasFired);
	
	/**
	 * Checks if the ship has shot.
	 */
	TBool HasFired();
	
	/**
	 * Increases ship's abscissa.
	 */
	void increaseX(TInt aX);
	
	/**
	 * Decreases ship's abscissa.
	 */
	void decreaseX(TInt aX);
	
	/**
	 * Increases ship's ordinate.
	 */
	void increaseY(TInt aY);
	
	/**
	 * Decreases ship's ordinate.
	 */
	void decreaseY(TInt aY);
	
	/**
	 * Sets the TShotEngine - pointer.
	 */
	void SetShot(TShotEngine* aShot);
	
	/**
	 * Gets the ship's shot.
	 */
	TShotEngine* Shot();
	
	/**
	 * Checks whether the ship collides with a shot.
	 */
	TBool IntersectsWith(TShotEngine* aShot);
	
	/**
	 * Checks whether the ship collides with another ship.
	 */
	TBool IntersectsWith(CShipEngine* aShip);

private:

	/**
	 * The abscissa of the ship.
	 */
	TInt iX;
	
	/**
	 * The ordinate of the ship.
	 */
	TInt iY;
	
	/**
	 * The state of the ship firing.
	 */
	TBool iHasFired;
	
	/**
	 * The shot of the ship.
	 */
	TShotEngine* iShot;
	
private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CShipEngine();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL(TInt aX, TInt aY);

};

#endif // SHIPENGINE_H

