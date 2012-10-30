/*
============================================================================
 Name		: SpaceInvadersAppUi.cpp
 Author	  : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : CSpaceInvadersAppUi implementation
============================================================================
*/

// INCLUDE FILES
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <f32file.h>
#include <s32file.h>
#include <hlplch.h>

#include <SpaceInvaders_0xEDBD9496.rsg>

#include "SpaceInvaders_0xEDBD9496.hlp.hrh"
#include "SpaceInvaders.hrh"
#include "SpaceInvaders.pan"
#include "SpaceInvadersApplication.h"
#include "SpaceInvadersAppUi.h"
#include "SpaceInvadersAppView.h"
#include "BitmapDefines.h"
#include "SpaceInvadersDocument.h"

void CSpaceInvadersAppUi::ConstructL()
{
	// Initialise app UI with standard value.
	BaseConstructL(CAknAppUi::EAknEnableSkin);

	// Create the highscore holder to use highscores
	CSpaceInvadersDocument* ptr = (CSpaceInvadersDocument*)Document();
	iHighscoreHolder            = ptr->Holder();

	TInt error;
	
	// Create the audioplayer
	TRAP(error, iAudioPlayer = CSpaceInvadersAudioPlayer::NewL());
	if( error )
	{
		Exit();
	}
	
	// Create the ship
	TRAP(error, iShip = CShipEngine::NewL(0, 0 ));
	if ( error )
	{
		Exit();
	}

	// Create view objects
	TRAP(error, iAppView = CSpaceInvadersAppView::NewL( ClientRect(),this,iShip,
			                                iHighscoreHolder));
	if ( error )
	{
		Exit();
	}
	
	iAppView->MakeVisible(EFalse);
	
	TRAP(error, iStartMenuView = CSpaceInvadersStartMenuAppView::
								 NewL(ClientRect(), this, iHighscoreHolder) );
	if ( error )
	{
		Exit();
	}
	iStartMenuView->MakeVisible(ETrue);
	
	TRAP(error, iHighscoreView = CSpaceInvadersHighscoreView::
								 NewL(ClientRect(), this, iHighscoreHolder) );
	if ( error )
	{
		Exit();
	}
	iHighscoreView->MakeVisible(EFalse);
	iCurrentView = iStartMenuView;
	
	AddToStackL( iCurrentView );

	// Hiding the status pane
	CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
	sp->MakeVisible(EFalse);

}

CSpaceInvadersAppUi::CSpaceInvadersAppUi()
{
	// No implementation required
}

CSpaceInvadersAppUi::~CSpaceInvadersAppUi()
{
	RemoveFromStack( iCurrentView );
	
	if ( iAppView )
	{
		delete iAppView;
		iAppView = NULL;
	}
	
	if ( iStartMenuView )
	{
		delete iStartMenuView;
		iStartMenuView = NULL;
	}
	
	if ( iHighscoreView )
	{
		delete iHighscoreView;
		iHighscoreView = NULL;
	}
	
	if ( iShip )
	{
		delete iShip;
		iShip = NULL;
	}

	if ( iAudioPlayer )
	{
		delete iAudioPlayer;
		iAudioPlayer = NULL;
	}
	
	if ( iHighscoreHolder )
	{
		delete iHighscoreHolder;
		iHighscoreHolder = NULL;
	}
}

void CSpaceInvadersAppUi::HandleStatusPaneSizeChange()
	{
	iAppView->SetRect( ClientRect() );
	} 

TKeyResponse CSpaceInvadersAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
{
	TKeyResponse retVal = EKeyWasNotConsumed;

	if ( iCurrentView == iStartMenuView )
	{
		retVal = iStartMenuView->HandleKeyEventL(aKeyEvent, aType);
	}
	else if ( iCurrentView == iAppView )
	{
		retVal = iAppView->HandleKeyEventL(aKeyEvent, aType);
	}
	else if ( iCurrentView == iHighscoreView )
	{
		retVal = iHighscoreView->HandleKeyEventL(aKeyEvent, aType);
	}

	if ( retVal == EKeyWasConsumed )
	{
		iCurrentView->DrawDeferred();
	}
	
	return retVal;
}

void CSpaceInvadersAppUi::ChangeView(CCoeControl* aView)
{
	RemoveFromStack( iCurrentView );
	
	iCurrentView->MakeVisible(EFalse);
	iCurrentView = aView;
	iCurrentView->MakeVisible(ETrue);
	AddToStackL( iCurrentView );
	
	if ( aView == iAppView )
	{
		InitShip();
		iAppView->StartTimerL();
		iAudioPlayer->PlayMySampleL();
	}
	else if ( aView == iHighscoreView )
	{
		iHighscoreHolder->UpdatePoints();
	}
	
	iCurrentView->DrawNow();
}


CSpaceInvadersAppView* CSpaceInvadersAppUi::AppView()
{
	return iAppView;
}

void CSpaceInvadersAppUi::SetAppView(CSpaceInvadersAppView* aAppView)
{
	iAppView = aAppView;
}

CSpaceInvadersStartMenuAppView* CSpaceInvadersAppUi::StartMenuView()
{
	return iStartMenuView;
}

void CSpaceInvadersAppUi::SetStartMenuView(CSpaceInvadersStartMenuAppView* aStartMenuView)
{
	iStartMenuView = aStartMenuView;
}

void CSpaceInvadersAppUi::UpdateView()
{
	iCurrentView->DrawDeferred();
}

CSpaceInvadersHighscoreView* CSpaceInvadersAppUi::HighscoreView()
{
	return iHighscoreView;
}

void CSpaceInvadersAppUi::ExitGame()
{
	SaveL();
	Exit();
}

void CSpaceInvadersAppUi::InitShip()
{
	TInt x = ClientRect().Width() / 2 - ship_width / 2;
	TInt y = ClientRect().Height() - 50;
	iShip->SetX(x);
	iShip->SetY(y);
}

// End of File
