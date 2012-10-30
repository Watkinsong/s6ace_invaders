/*
============================================================================
 Name		 : SpaceInvadersAppView.cpp
 Author	     : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : Application view implementation
============================================================================
*/

// INCLUDE FILES
#include <coemain.h>
#include "SpaceInvadersAppView.h"
#include "BitmapDefines.h"
#include "SpaceInvadersAppUi.h"
#include "ShipEngine.h"
#include "ShotEngine.h"
#include <e32std.h>
#include <w32std.h>
#include <aknutils.h>
#include <fbs.h>

CSpaceInvadersAppView* CSpaceInvadersAppView::NewL( const TRect& aRect,
		                                            CSpaceInvadersAppUi* aAppUi,
		                                            CShipEngine* aShip, 
		                                            THighscoreHolder* aHolder)
{
	CSpaceInvadersAppView* self = CSpaceInvadersAppView::NewLC( aRect,
			                                                   aAppUi,
			                                                   aShip,
			                                                   aHolder);
	CleanupStack::Pop( self );
	return self;
}

CSpaceInvadersAppView* CSpaceInvadersAppView::NewLC( const TRect& aRect,
		                                            CSpaceInvadersAppUi* aAppUi,
		                                            CShipEngine* aShip,
		                                            THighscoreHolder* aHolder)
{
	CSpaceInvadersAppView* self = new ( ELeave ) CSpaceInvadersAppView;
	CleanupStack::PushL( self );
	self->ConstructL( aRect, aAppUi, aShip, aHolder);
	return self;
}

void CSpaceInvadersAppView::ConstructL( const TRect& aRect,
		                                CSpaceInvadersAppUi* aAppUi,
		                                CShipEngine* aShip,
		                                THighscoreHolder* aHolder)
{
	// Create a window for this application view
	CreateWindowL();

	// Set the windows size
	SetRect( aRect );
	// Sets the extent of the screen so it draws on the places of status pane
	// and options pane
	SetExtentToWholeScreen();

	iShip               = aShip;
	iAppUi              = aAppUi;
	iTickCounter        = 0;
	iShotCounter        = 0;
	iMaxHorizontalMoves = Rect().Width() / (6 * ship_width) + 2;
	iHorizontalMoves    = 2;
    iHolder 		    = aHolder;
	
    // Creates the alien CShipEngine -objects and places them to start positions
	InitAliens();

	TInt error;
	TRAP(error, LoadBitmapsL());
	if ( error )
	{
		iAppUi->Exit();
	}

	// Activate the window, which makes it ready to be drawn
	ActivateL();
}

CSpaceInvadersAppView::CSpaceInvadersAppView()
{
	// No implementation required
}

CSpaceInvadersAppView::~CSpaceInvadersAppView()
{	
	iAlienArray.DeleteAll();
	iAlienArray.Reset();
	StopTimer();
	
	if ( iBitmapShip )
	{
		delete iBitmapShip;
		iBitmapShip = NULL;
	}
    
    
	if ( iBitmapAlien1 )
	{
		delete iBitmapAlien1;
		iBitmapAlien1 = NULL;
	}
    
    
	if ( iBitmapAlien2 )
	{
		delete iBitmapAlien2;
		iBitmapAlien2 = NULL;
	}
    
    
	if ( iBitmapAlien3 )
	{
		delete iBitmapAlien3;
		iBitmapAlien3 = NULL;
	}
    
    
	if ( iBitmapShot )
	{
		delete iBitmapShot;
		iBitmapShot = NULL;
	}
    
}

void CSpaceInvadersAppView::LoadBitmapsL()
{
	TFileName mbmShipFileName(shipFile);
	CompleteWithAppPath(mbmShipFileName);

	iBitmapShip = new (ELeave) CFbsBitmap();
	
	User::LeaveIfError(iBitmapShip->Load(mbmShipFileName, 0));
	
	TFileName mbmAlien1FileName(alien1File);
	CompleteWithAppPath(mbmAlien1FileName);
	
	iBitmapAlien1 = new (ELeave) CFbsBitmap();
	
	User::LeaveIfError(iBitmapAlien1->Load(mbmAlien1FileName, 0));
	
	TFileName mbmAlien2FileName(alien2File);
	CompleteWithAppPath(mbmAlien2FileName);
	
	iBitmapAlien2 = new (ELeave) CFbsBitmap();
	
	User::LeaveIfError(iBitmapAlien2->Load(mbmAlien2FileName, 0));
	
	TFileName mbmAlien3FileName(alien3File);
	CompleteWithAppPath(mbmAlien3FileName);
	
	iBitmapAlien3 = new (ELeave) CFbsBitmap();
	
	User::LeaveIfError(iBitmapAlien3->Load(mbmAlien3FileName, 0));
	
	TFileName mbmShotFileName(shotFile);
	CompleteWithAppPath(mbmShotFileName);
	
	iBitmapShot = new (ELeave) CFbsBitmap();
	
	User::LeaveIfError(iBitmapShot->Load(mbmShotFileName, 0));
}

void CSpaceInvadersAppView::InitAliens()
{
	iTotalAliens     = 18;
	iRemainingAliens = iTotalAliens;
	iAlienDirection  = ERight;

	TInt row       = 1;
	TInt column    = 1;
	TInt spaceX    = Rect().Width() / 6;
	TInt previousX = spaceX ;

	TInt alienCounter = 0;
	
	for(TInt i = 0 ; i < iTotalAliens ; i++ )
	{
		TInt x = previousX + 10 ;
		TInt y = row * (ship_height + 10);

		if ( iAlienArray[i] )
		{
			delete iAlienArray[i];
			iAlienArray[i] = NULL;
		}
		
		TInt error;
		TRAP(error, iAlienArray[i] = CShipEngine::NewL(x, y ))
		if ( error )
		{
			// Half of the aliens created, that's enough
			if ( alienCounter >= iTotalAliens / 2 )
			{
				break;
			}
		}
		else
		{
			alienCounter++;
		}

		column++;
		previousX += ship_width + 10;
		
		if ( column == 7 )
		{
			column = 1;
			row++;
			previousX = spaceX;
		}
	}
}

void CSpaceInvadersAppView::StartTimerL()
{
	const TInt KTickInterval = 10000;
	iPeriodic = CPeriodic::NewL(CActive::EPriorityUserInput);
	iPeriodic->Start(KTickInterval, KTickInterval, TCallBack(Tick, this));
}

void CSpaceInvadersAppView::StopTimer()
{
	if ( iPeriodic )
	{
		iPeriodic->Cancel();
		delete iPeriodic;
		iPeriodic = NULL;
	}
}

TInt CSpaceInvadersAppView::Tick(TAny* aObject)
{
	static_cast<CSpaceInvadersAppView*>(aObject)->NextTick();
	return 1;
}

void CSpaceInvadersAppView::NextTick()
{
	iTickCounter++;
	TInt changeX     = 0;
	TInt changeY     = 0;
	TBool moveAliens = EFalse;

	if ( iTickCounter == 48 )
	{
		if ( iAlienDirection == ERight )
		{

			if ( iHorizontalMoves < iMaxHorizontalMoves )
			{
				changeX = 20;
				iHorizontalMoves++;
			}
			else
			{
				changeY          = 20;
				iAlienDirection  = ELeft;
				iHorizontalMoves = 0;
			}
		}
		else
		{
			if ( iHorizontalMoves < iMaxHorizontalMoves )
			{
				changeX = -20;
				iHorizontalMoves++;
			}
			else
			{
				changeY          = 20;
				iAlienDirection  = ERight;
				iHorizontalMoves = 0;
			}

		}

		iTickCounter = 0;
		iShotCounter++;
		moveAliens = ETrue;
	}

	// Checking for collisions between aliens and ship and shots and updating
	// the coordinates in one loop.
	for(TInt i = 0 ; i < iTotalAliens ; i++ )
	{
		if ( iAlienArray[i] && iAlienArray[i]->HasFired() )
		{
			if ( iShip->IntersectsWith(iAlienArray[i]->Shot()) )
			{
				// Alien shot hits alien
				GameOver();
			}
			else if ( iAlienArray[i]->Shot()->Y() + 5 < Rect().Height() )
			{
				iAlienArray[i]->Shot()->SetY(iAlienArray[i]->Shot()->Y() + 5);
			}
			else
			{
				iAlienArray[i]->ShotExpired();
			}

			DrawNow();
		}
		else if ( iAlienArray[i] )
		{
			if ( iShotCounter == 3 )
			{
				iAlienArray[i]->ShotFired();
				iShotCounter = 0;
			}
		}

		if ( iAlienArray[i] && iShip->HasFired() )
		{
			if ( iAlienArray[i]->IntersectsWith(iShip->Shot()))
			{
				// Player's shot hits alien
				delete iAlienArray[i];
				iAlienArray[i] = NULL;
				iShip->ShotExpired();
				iRemainingAliens--;
				iHolder->SetActivePoints(iHolder->ActivePoints() + 10);
				
				if ( iRemainingAliens == 0 )
				{
					// All the aliens have been destroyed
					GameOver();
				}
				else
				{
					DrawNow();
				}
			}
		}

		if ( iAlienArray[i] && iAlienArray[i]->IntersectsWith(iShip) )
		{
			// Alien hits ship
			GameOver();
		}
		else if ( iAlienArray[i] )
		{
			if ( iAlienArray[i]->Y() + changeY + ship_height < Rect().Height() )
			{
				iAlienArray[i]->SetX(iAlienArray[i]->X() + changeX);
				iAlienArray[i]->SetY(iAlienArray[i]->Y() + changeY);
			}
			else
			{
				// Game ends if the aliens reach the bottom of the screen
				GameOver();
			}	
		}

	}

	if ( iShip->HasFired() )
	{
	    if ( iShip->Shot()->Y() - 5 > 0 )
		{
			iShip->Shot()->SetY(iShip->Shot()->Y() - 5 );
		}
		else
		{
			iShip->ShotExpired();
		}
	    DrawDeferred();
	}
	else if (moveAliens)
	{
		DrawDeferred();
	}

}

void CSpaceInvadersAppView::Draw( const TRect& /*aRect*/ ) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	DrawBackground(gc);
	DrawShip(gc);
	DrawAliens(gc);
	DrawPoints(gc);
	DrawQuitCommand(gc);
	
	}

void CSpaceInvadersAppView::SizeChanged()
{  
	DrawNow();
}

TKeyResponse CSpaceInvadersAppView::HandleKeyEventL(const TKeyEvent& aKeyEvent,
		                                            TEventCode aType)
{
	TKeyResponse retVal = EKeyWasNotConsumed;

		if ( aKeyEvent.iCode == EKeyUpArrow )
		{
			MoveShipUp();
			retVal = EKeyWasConsumed;
		}
		else if ( aKeyEvent.iCode == EKeyRightArrow )
		{
			MoveShipRight();
			retVal = EKeyWasConsumed;
		}
		else if ( aKeyEvent.iCode == EKeyDownArrow )
		{
			MoveShipDown();
			retVal = EKeyWasConsumed;
		}
		else if ( aKeyEvent.iCode == EKeyLeftArrow )
		{
			MoveShipLeft();
			retVal = EKeyWasConsumed;
		}
		else if ( aKeyEvent.iCode == EKeyDevice1 )
		{
			GameOver();
			retVal = EKeyWasConsumed;
		}
		else if ( aKeyEvent.iCode == EKeyDevice3
				  || aKeyEvent.iCode == EKeyEnter )
		{
			if ( ! iShip->HasFired() )
			{
				iShip->ShotFired();
			}

			retVal = EKeyWasConsumed;
		}

	return retVal;
}

void CSpaceInvadersAppView::DrawBackground(CWindowGc& aGc) const
{
	TRgb backcolor = TRgb(0,0,0);
	aGc.SetBrushColor(backcolor);
	aGc.Clear();
}

void CSpaceInvadersAppView::DrawShip(CWindowGc& aGc) const
{
	// Draw the image in the desired position
	TPoint shipPoint(iShip->X(), iShip->Y());	
	aGc.BitBlt( shipPoint, iBitmapShip);
	
	if ( iShip->HasFired() )
	{
		TPoint shotPoint(iShip->Shot()->X(), iShip->Shot()->Y());
		aGc.BitBlt( shotPoint, iBitmapShot );
	}
}

void CSpaceInvadersAppView::DrawAliens(CWindowGc& aGc) const
{
	for ( TInt i = 0 ; i < iTotalAliens ; i++ )
	{
		if ( iAlienArray[i] )
		{
	
			TPoint shipPoint(iAlienArray[i]->X(), iAlienArray[i]->Y());
			CFbsBitmap* iBitmapShip;
			
			if ( i < 6 )
			{
				iBitmapShip = iBitmapAlien1;
			}
			else if ( i < 12 )
			{
				iBitmapShip = iBitmapAlien2;
			}
			else
			{
				iBitmapShip = iBitmapAlien3;
			}
	    	aGc.BitBlt( shipPoint, iBitmapShip );
	    	
	    	if ( iAlienArray[i]->HasFired() )
			{
				TPoint shotPoint(iAlienArray[i]->Shot()->X(),
						         iAlienArray[i]->Shot()->Y());
				aGc.BitBlt( shotPoint, iBitmapShot );
			}
    	
		}
	}
}

void CSpaceInvadersAppView::DrawPoints(CWindowGc& aGc) const
{
	TRgb pencolor = TRgb(255,255,255);
	aGc.SetPenColor(pencolor);
	_LIT(KPointsText, "Points: ");
	
	TBufC<15> pointsText;
	TPtr pointsPtr = pointsText.Des();
	pointsPtr.Append(KPointsText);
	pointsPtr.AppendNum(iHolder->ActivePoints());
	
    const CFont* menuFont =
              AknLayoutUtils::FontFromId(EAknLogicalFontPrimarySmallFont, NULL);
    aGc.UseFont(menuFont);
    TInt textLength = menuFont->TextWidthInPixels(pointsPtr);
    TInt textHeight = menuFont->HeightInPixels();
	TPoint textpoint(Rect().Width() / 2 - textLength / 2, textHeight);
	aGc.DrawText(pointsPtr, textpoint);
}

void CSpaceInvadersAppView::DrawQuitCommand(CWindowGc& aGc) const
{
	TRgb pencolor = TRgb(255,255,255);
	aGc.SetPenColor(pencolor);
	_LIT(KQuitText, "Quit");
	
	TBufC<4> quitText;
	TPtr quitPtr = quitText.Des();
	quitPtr.Append(KQuitText);
	
	const CFont* menuFont =
	          AknLayoutUtils::FontFromId(EAknLogicalFontPrimarySmallFont, NULL);
	aGc.UseFont(menuFont);
	TInt textLength = menuFont->TextWidthInPixels(quitPtr);
	TInt textHeight = menuFont->HeightInPixels();
	TPoint textpoint(Rect().Width() - ( textLength + 10 ),
			         Rect().Height() - textHeight);
	aGc.DrawText(quitPtr, textpoint);
}

void CSpaceInvadersAppView::GameOver()
{
	StopTimer();
	InitAliens();
	iAppUi->ChangeView(iAppUi->HighscoreView());
}

void CSpaceInvadersAppView::MoveShipUp() const
{
	if ( iShip->Y() - ship_movement > 0)
	{
		iShip->decreaseY(ship_movement);
	}
}

void CSpaceInvadersAppView::MoveShipRight() const
{
	if ( iShip->X() + ship_movement < Rect().Width() - ship_width )
	{
		iShip->increaseX(ship_movement);
	}
}

void CSpaceInvadersAppView::MoveShipDown() const
{
	if ( iShip->Y() + ship_movement < Rect().Height() - ship_width )
	{
		iShip->increaseY(ship_movement);
	}
}

void CSpaceInvadersAppView::MoveShipLeft() const
{
	if ( iShip->X() - ship_movement > 0)
	{
		iShip->decreaseX(ship_movement);
	}
}

// End of File
