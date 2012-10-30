/*
============================================================================
 Name		 : ShotEngine.h
 Author	     : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : The model-class for the shot.
============================================================================
*/

#include "ShotEngine.h"

TShotEngine::TShotEngine(TInt aX, TInt aY)
{
	iX = aX;
	iY = aY;
}

TShotEngine::~TShotEngine()
{
}

void TShotEngine::SetY(TInt aY)
{
	iY = aY;
}

TInt TShotEngine::Y()
{
	return iY;
}

void TShotEngine::SetX(TInt aX)
{
	iX = aX;
}

TInt TShotEngine::X()
{
	return iX;
}

// End of file