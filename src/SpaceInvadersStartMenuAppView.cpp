/*
============================================================================
 Name		 : SpaceInvadersStartMenuAppView.cpp
 Author	     : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : Application view implementation
============================================================================
*/

// INCLUDE FILES
#include <coemain.h>
#include "SpaceInvadersStartMenuAppView.h"
#include "BitmapDefines.h"
#include <eikenv.h>
#include <aknutils.h>
#include <gdi.h>

CSpaceInvadersStartMenuAppView* CSpaceInvadersStartMenuAppView::NewL(
		                                            const TRect& aRect,
		                                            CSpaceInvadersAppUi* aAppUi,
		                                            THighscoreHolder* aHolder)
{
	CSpaceInvadersStartMenuAppView* self =
	             CSpaceInvadersStartMenuAppView::NewLC( aRect, aAppUi, aHolder);
	CleanupStack::Pop( self );
	return self;
}

CSpaceInvadersStartMenuAppView* CSpaceInvadersStartMenuAppView::NewLC(
		                                            const TRect& aRect,
		                                            CSpaceInvadersAppUi* aAppUi,
		                                            THighscoreHolder* aHolder)
{
	CSpaceInvadersStartMenuAppView* self =
	                            new ( ELeave ) CSpaceInvadersStartMenuAppView();
	CleanupStack::PushL( self );
	self->ConstructL( aRect, aAppUi, aHolder);
	return self;
}

void CSpaceInvadersStartMenuAppView::ConstructL( const TRect& aRect,
		                                         CSpaceInvadersAppUi* aAppUi,
		                                         THighscoreHolder* aHolder)
{
	// Create a window for this application view
	CreateWindowL();

	// Set the windows size
	SetRect( aRect );

	// Sets the extent of the screen so it draws on the places of status pane
	// and options pane
	SetExtentToWholeScreen();
	
	// Activate the window, which makes it ready to be drawn
	ActivateL();
	
	iAppUi          = aAppUi;
	iSelectedOption = 1;
	iHolder         = aHolder;
	
	iBitmapLogo = iEikonEnv->CreateBitmapL( gamelogoFile, 0 );
}

CSpaceInvadersStartMenuAppView::CSpaceInvadersStartMenuAppView()
{
	// No implementation required
}

CSpaceInvadersStartMenuAppView::~CSpaceInvadersStartMenuAppView()
{
	if ( iBitmapLogo )
	{
		delete iBitmapLogo;
		iBitmapLogo = NULL;
	}
}

void CSpaceInvadersStartMenuAppView::Draw( const TRect& /*aRect*/ ) const
{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();
	// Draw game logo
    DrawGameLogo(gc);
    // Draw start menu options
    DrawStartMenuOptions(gc);
}

void CSpaceInvadersStartMenuAppView::SizeChanged()
{  
	DrawNow();
}

void CSpaceInvadersStartMenuAppView::DrawStartMenuOptions(CWindowGc& aGc) const
{
	DrawStartMenuItem(1, KNewGameText().AllocL(), aGc);
	DrawStartMenuItem(2, KHighscoresText().AllocL(), aGc);
	DrawStartMenuItem(3, KExitText().AllocL(), aGc);
}

TInt CSpaceInvadersStartMenuAppView::SelectedOption() const
{
	return iSelectedOption;
}

void CSpaceInvadersStartMenuAppView::SetSelectedOption(TInt aValue)
{
	iSelectedOption = aValue;
}

void CSpaceInvadersStartMenuAppView::DrawStartMenuItem(TInt aOrder,
										  			   TDesC* aText,
										  			   CWindowGc& aGc) const
{
	TInt blue = 255;

	if ( iSelectedOption == aOrder )
	{	
		// The selected option is yellow
    	blue = 0;		
	}
	TRgb fontColor = TRgb(255, 255, blue);

    const CFont* menuFont = AknLayoutUtils::FontFromId(EAknLogicalFontTitleFont,
    		                                           NULL);
    aGc.UseFont(menuFont);
    
    TInt textLength = menuFont->TextWidthInPixels(*aText);
    TInt textHeight = menuFont->HeightInPixels();
	TPoint textpoint(Rect().Width() / 2 - textLength / 2,
			         gamelogo_height + (aOrder + 1) * textHeight);
	aGc.SetPenColor(fontColor);
	aGc.DrawText(*aText, textpoint);
	delete aText;
}

void CSpaceInvadersStartMenuAppView::DrawGameLogo(CWindowGc& aGc) const
{
	TRgb backcolor = TRgb(0,0,0);
	// Coordinates for the game logo
	TInt gamelogoX = Rect().Width() / 2 - gamelogo_width / 2;
	TInt gamelogoY = Rect().Height() / 10;
	// Position of the logo
	TPoint logopoint(gamelogoX, gamelogoY);
	aGc.SetBrushColor(backcolor);
	aGc.Clear();
	// Draw the image in the desired position
	aGc.BitBlt( logopoint, iBitmapLogo );
}

TKeyResponse CSpaceInvadersStartMenuAppView::HandleKeyEventL(
		                                             const TKeyEvent& aKeyEvent,
		                                             TEventCode aType)
{
	TKeyResponse retVal = EKeyWasNotConsumed;

			if ( aKeyEvent.iCode == EKeyUpArrow )
			{
				if ( SelectedOption() == 1 )
				{
					SetSelectedOption(3);
			 	}
				else if ( SelectedOption() == 2 )
				{
					SetSelectedOption(1);
			 	}
				else if ( SelectedOption() == 3 )
				{
					SetSelectedOption(2);
			 	}

				retVal = EKeyWasConsumed;
			}
			else if ( aKeyEvent.iCode == EKeyDownArrow )
			{
				if ( SelectedOption() == 1 )
				{
					SetSelectedOption(2);
			 	}
				else if ( SelectedOption() == 2 )
				{
					SetSelectedOption(3);
			 	}
				else if ( SelectedOption() == 3 )
				{
					SetSelectedOption(1);
			 	}

				retVal = EKeyWasConsumed;
			}
			else if ( aKeyEvent.iCode == EKeyDevice3
					  || aKeyEvent.iCode == EKeyEnter)
			{
				if ( SelectedOption() == 1 ) // New game
				{
					iAppUi->ChangeView((CCoeControl*)iAppUi->AppView());
			 	}
				else if ( SelectedOption() == 2 ) // Highscores
				{
					iAppUi->ChangeView((CCoeControl*)iAppUi->HighscoreView());
			 	}
				else if ( SelectedOption() == 3 ) // Exit
				{
					// Exit the game
					iAppUi->ExitGame();
			 	}

				retVal = EKeyWasConsumed;
			}
			
	return retVal;

}

CSpaceInvadersAppUi* CSpaceInvadersStartMenuAppView::AppUi()
{
	return iAppUi;
}

void CSpaceInvadersStartMenuAppView::SetAppUi(CSpaceInvadersAppUi* aAppUi)
{
	iAppUi = aAppUi;
}

// End of File
