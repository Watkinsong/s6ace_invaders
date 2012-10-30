/*
============================================================================
 Name		 : ShipEngine.cpp
 Author	     : Arttu Salonen
 Version	 :
 Copyright   : Copyright Arttu Salonen 2009
 Description : CShipEngine implementation
============================================================================
*/

#include "ShipEngine.h"
#include "BitmapDefines.h"

CShipEngine::CShipEngine()
{
	// No implementation required
}


CShipEngine::~CShipEngine()
{
	if ( iShot )
	{
		delete iShot;
		iShot = NULL;
	}
}

CShipEngine* CShipEngine::NewLC(TInt aX, TInt aY)
{
	CShipEngine* self = new (ELeave)CShipEngine();
	CleanupStack::PushL(self);
	self->ConstructL(aX, aY);
	return self;
}

CShipEngine* CShipEngine::NewL(TInt aX, TInt aY)
{
	CShipEngine* self=CShipEngine::NewLC(aX, aY);
	CleanupStack::Pop(); // self;
	return self;
}

void CShipEngine::ConstructL(TInt aX, TInt aY)
{
	iX = aX;
	iY = aY;
	iHasFired = EFalse;
}

TInt CShipEngine::X()
{
	return iX;
}

void CShipEngine::SetX(TInt aX)
{
	iX = aX;
}

TInt CShipEngine::Y()
{
	return iY;
}

void CShipEngine::SetY(TInt aY)
{
	iY = aY;
}

TBool CShipEngine::HasFired()
{
	return iHasFired;
}

void CShipEngine::SetHasFired(TBool aHasFired)
{
	iHasFired = aHasFired;
}

void CShipEngine::increaseX(TInt aX)
{
	iX += aX;
}

void CShipEngine::decreaseX(TInt aX)
{
	iX -= aX;
}

void CShipEngine::increaseY(TInt aY)
{
	iY += aY;
}

void CShipEngine::decreaseY(TInt aY)
{
	iY -= aY;
}

void CShipEngine::SetShot(TShotEngine* aShot)
{
	iShot = aShot;
}

TShotEngine* CShipEngine::Shot()
{
	return iShot;
}

void CShipEngine::ShotFired()
{
	iHasFired = ETrue;
	TInt shotX = iX + ship_width / 2 - 1;
	TInt shotY = iY - ship_height;
	iShot = new TShotEngine(shotX, shotY);
}

void CShipEngine::ShotExpired()
{
	iHasFired = EFalse;
	delete iShot;
	iShot = NULL;
}

TBool CShipEngine::IntersectsWith(TShotEngine* aShot)
{
	TBool retVal = EFalse;
	
	TRect shipRect(TPoint(X(), Y()), TSize(ship_width, ship_height));
	TRect shotRect(TPoint(aShot->X(), aShot->Y()),
			       TSize(shot_width, shot_height));
	
	if ( shipRect.Intersects(shotRect) )
	{
		retVal = ETrue;
	}

	return retVal;
}

TBool CShipEngine::IntersectsWith(CShipEngine* aShip)
{
	TBool retVal = EFalse;
	
	TRect shipRect(TPoint(X(), Y()), TSize(ship_width, ship_height));
	TRect alienRect(TPoint(aShip->X(), aShip->Y()),
			        TSize(shot_width, shot_height));
	
	if ( shipRect.Intersects(alienRect) )
	{
		retVal = ETrue;
	}

	return retVal;
}
