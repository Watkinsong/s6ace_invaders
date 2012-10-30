/*
============================================================================
 Name		 : SpaceInvadersHighscoreView.cpp
 Author	     : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : Application view implementation
============================================================================
*/

// INCLUDE FILES
#include <coemain.h>
#include "SpaceInvadersHighscoreView.h"
#include "SpaceInvadersAppUi.h"
#include <aknutils.h>

CSpaceInvadersHighscoreView* CSpaceInvadersHighscoreView::NewL(
		                                            const TRect& aRect,
		                                            CSpaceInvadersAppUi* aAppUi,
		                                            THighscoreHolder* aHolder)
{
	CSpaceInvadersHighscoreView* self =
	                 CSpaceInvadersHighscoreView::NewLC(aRect, aAppUi, aHolder);
	CleanupStack::Pop( self );
	return self;
}

CSpaceInvadersHighscoreView* CSpaceInvadersHighscoreView::NewLC(
		                                            const TRect& aRect, 
		                                            CSpaceInvadersAppUi* aAppUi,
		                                            THighscoreHolder* aHolder)
{
	CSpaceInvadersHighscoreView* self =
	                                 new ( ELeave ) CSpaceInvadersHighscoreView;
	CleanupStack::PushL( self );
	self->ConstructL(aRect, aAppUi, aHolder);
	return self;
}

void CSpaceInvadersHighscoreView::ConstructL( const TRect& aRect,
		                                      CSpaceInvadersAppUi* aAppUi,
		                                      THighscoreHolder* aHolder)
{
	// Create a window for this application view
	CreateWindowL();

	// Set the windows size
	SetRect( aRect );
	iAppUi  = aAppUi;
	iHolder = aHolder;
	// Sets the extent of the screen so it draws on the places of status pane
	// and options pane
	SetExtentToWholeScreen();
	ActivateL();
}

CSpaceInvadersHighscoreView::CSpaceInvadersHighscoreView()
{
	// No implementation required
}

CSpaceInvadersHighscoreView::~CSpaceInvadersHighscoreView()
{	

}

void CSpaceInvadersHighscoreView::Draw( const TRect& /*aRect*/ ) const
{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	TRgb backcolor = TRgb(0,0,0);
	gc.SetBrushColor(backcolor);
	gc.Clear();
	
		for ( TInt i = 0 ; i < iHolder->NumberOfItems() ; i++ )
		{
			DrawHighscoreItem(iHolder->PointArray()[i], i + 1, gc);
		}
	
	DrawBackCommand(gc);
		
}

void CSpaceInvadersHighscoreView::SizeChanged()
{  
	DrawNow();
}

TKeyResponse CSpaceInvadersHighscoreView::HandleKeyEventL(
		                            const TKeyEvent& aKeyEvent,TEventCode aType)
{
	TKeyResponse retVal = EKeyWasNotConsumed;
		
		if ( aKeyEvent.iCode == EKeyDevice3 || aKeyEvent.iCode == EKeyEnter)
		{
			iAppUi->ChangeView(iAppUi->StartMenuView());

			retVal = EKeyWasConsumed;
		}
	
	return retVal;
}

void CSpaceInvadersHighscoreView::DrawHighscoreItem(TInt aPoints,
		                                            TInt aOrder,
		                                            CWindowGc& aGc) const
{
	TRgb pencolor = TRgb(255,255,0);
	aGc.SetPenColor(pencolor);
	_LIT(KDelimiter, ". ");
	
	TBufC<30> pointsText;
	TPtr pointsPtr = pointsText.Des();
	pointsPtr.AppendNum(aOrder);
	pointsPtr.Append(KDelimiter);
	pointsPtr.AppendNum(aPoints);
	
	const CFont* menuFont =
	             AknLayoutUtils::FontFromId(EAknLogicalFontSecondaryFont, NULL);
	aGc.UseFont(menuFont);
	TInt textLength = menuFont->TextWidthInPixels(pointsPtr);
	TInt textHeight = menuFont->HeightInPixels() + 5;
	TPoint textpoint(Rect().Width() / 2 - textLength / 2, textHeight * aOrder);
	aGc.DrawText(pointsPtr, textpoint);
}

void CSpaceInvadersHighscoreView::DrawBackCommand(CWindowGc& aGc) const
{
	TRgb pencolor = TRgb(255,255,0);
	aGc.SetPenColor(pencolor);
	_LIT(KQuitText, "Back");
	
	TBufC<30> backText;
	TPtr backPtr = backText.Des();
	backPtr.Append(KQuitText);
	
	const CFont* menuFont =
	          AknLayoutUtils::FontFromId(EAknLogicalFontPrimarySmallFont, NULL);
	aGc.UseFont(menuFont);
	TInt textLength = menuFont->TextWidthInPixels(backPtr);
	TInt textHeight = menuFont->HeightInPixels();
	TPoint textpoint(Rect().Width() / 2 - textLength / 2 ,
			         Rect().Height() - textHeight);
	aGc.DrawText(backPtr, textpoint);
}

// End of File
