/*
============================================================================
 Name		 : ShotEngine.h
 Author	     : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : The model-class for the shot.
============================================================================
*/

#ifndef SHOTENGINE_H_
#define SHOTENGINE_H_

#include <e32base.h>
#include <s32std.h>

// CLASS DECLARATION
/**
* Depicts a shot used by the CShipEngine -objects.
*/

class TShotEngine
{
public:

	/**
	 * The constructor.
	 */
	TShotEngine(TInt aX, TInt aY);
	
	/**
	 * The destructor.
	 */
	virtual ~TShotEngine();
	
	/**
	 * Sets the abscissa of the shot.
	 */
	void SetX(TInt aX);
	
	/**
	 * Gets the abscissa of the shot.
	 */
	TInt X();
	
	/**
	 * Sets the ordinate of the shot.
	 */
	void SetY(TInt aY);
	
	/**
	 * Gets the ordinate of the shot.
	 */
	TInt Y();

private:

	/**
	 * Abscissa of the shot.
	 */
	TInt iX;
	
	/**
	 * Ordinate of the shot.
	 */
	TInt iY;
};

#endif /*SHOTENGINE_H_*/
