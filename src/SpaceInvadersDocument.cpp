/*
============================================================================
 Name		 : SpaceInvadersDocument.cpp
 Author	     : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : CSpaceInvadersDocument implementation
============================================================================
*/


// INCLUDE FILES
#include "SpaceInvadersAppUi.h"
#include "SpaceInvadersDocument.h"

CSpaceInvadersDocument* CSpaceInvadersDocument::NewL( CEikApplication& aApp )
{
	CSpaceInvadersDocument* self = NewLC( aApp );
	CleanupStack::Pop( self );
	return self;
}

CSpaceInvadersDocument* CSpaceInvadersDocument::NewLC( CEikApplication& aApp )
{
	CSpaceInvadersDocument* self =
		new ( ELeave ) CSpaceInvadersDocument( aApp );

	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
}

void CSpaceInvadersDocument::ConstructL()
{
		iHolder = new THighscoreHolder();
}

CSpaceInvadersDocument::CSpaceInvadersDocument( CEikApplication& aApp )
	: CAknDocument( aApp )
{
	// No implementation required
}

CSpaceInvadersDocument::~CSpaceInvadersDocument()
{
	// No implementation required
}

CEikAppUi* CSpaceInvadersDocument::CreateAppUiL()
{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return ( static_cast <CEikAppUi*> ( new ( ELeave )
										CSpaceInvadersAppUi ) );
}

void CSpaceInvadersDocument::SetHolder(THighscoreHolder* aHolder)
{
	iHolder = aHolder;
}

THighscoreHolder* CSpaceInvadersDocument::Holder()
{
	return iHolder;
}

void CSpaceInvadersDocument::StoreL(CStreamStore& aStore,
		                            CStreamDictionary& aStreamDic) const
{
	// Calls engine's StoreL -method
	TStreamId id = iHolder->StoreL(aStore);
	aStreamDic.AssignL(TUid::Uid(8), id);
}

void CSpaceInvadersDocument::RestoreL(const CStreamStore& aStore,
		                              const CStreamDictionary& aStreamDic)
{
	TStreamId streamId = aStreamDic.At(TUid::Uid(8));
	
	TInt error;
	TRAP(error, iHolder->RestoreL(aStore, streamId));
	if ( error )
	{
		iHolder->InitPointArray();
	}
}

CFileStore* CSpaceInvadersDocument::OpenFileL(TBool aDoOpen,
		                                      const TDesC& aFilename, RFs& aFs)
{
	return CEikDocument::OpenFileL(aDoOpen, aFilename, aFs);
}

// End of File
