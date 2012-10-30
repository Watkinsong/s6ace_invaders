/*
============================================================================
 Name		: SpaceInvaders.pan
 Author	  : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : This file contains panic codes.
============================================================================
*/

#ifndef __SPACEINVADERS_PAN__
#define __SPACEINVADERS_PAN__

/** SpaceInvaders application panic codes */
enum TSpaceInvadersPanics
	{
	ESpaceInvadersUi = 1
	// add further panics here
	};

inline void Panic(TSpaceInvadersPanics aReason)
	{
	_LIT(applicationName,"SpaceInvaders");
	User::Panic(applicationName, aReason);
	}

#endif // __SPACEINVADERS_PAN__
