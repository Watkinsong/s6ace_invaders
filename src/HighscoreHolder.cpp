/*
============================================================================
 Name		 : HighscoreHolder.h
 Author	     : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : Holds and stores the highscores of the game.
============================================================================
*/

#include "HighscoreHolder.h"

THighscoreHolder::THighscoreHolder()
{
	iNumberOfItems = 10;
	iActivePoints  = 0;

	InitPointArray();
}

THighscoreHolder::~THighscoreHolder()
{

}

void THighscoreHolder::InitPointArray()
{
	for ( TInt i = 0 ; i < iNumberOfItems ; i++ )
	{
		iPointArray[i] = 0;
	}
}

TStreamId THighscoreHolder::StoreL(CStreamStore& aStore) const
{
	RStoreWriteStream stream;
	TStreamId id = stream.CreateLC(aStore);
	ExternalizeL(stream);
	stream.CommitL();
	CleanupStack::PopAndDestroy();
	return id;
}

void THighscoreHolder::RestoreL(const CStreamStore& aStore, TStreamId aStreamId)
{
	RStoreReadStream stream;
	stream.OpenLC(aStore, aStreamId);
	InternalizeL(stream);
	CleanupStack::PopAndDestroy();
}

void THighscoreHolder::ExternalizeL(RWriteStream& aStream) const
{
	for ( TInt i = 0 ; i < iNumberOfItems ; i++ )
	{
		aStream.WriteInt32L(iPointArray[i]);
	}
}

void THighscoreHolder::InternalizeL(RReadStream& aStream)
{
	for ( TInt i = 0 ; i < iNumberOfItems ; i++ )
	{
		TInt error;
		TRAP(error, RestorePointL(i, aStream));
		if ( error )
		{
			iPointArray[i] = 0;
		}
	}
	
	SortPoints();
}

void THighscoreHolder::SetActivePoints(TInt aActivePoints)
{
	iActivePoints = aActivePoints;
}

TInt THighscoreHolder::ActivePoints()
{
	return iActivePoints;
}

TInt THighscoreHolder::NumberOfItems()
{
	return iNumberOfItems;
}

TFixedArray<TInt, 10> THighscoreHolder::PointArray()
{
	return iPointArray;
}

void THighscoreHolder::UpdatePoints()
{
	if ( iPointArray[iNumberOfItems - 1] < iActivePoints )
	{
		iPointArray[iNumberOfItems - 1] = iActivePoints;
		SortPoints();
		iActivePoints = 0;
	}
}

void THighscoreHolder::SortPoints()
{
	for ( TInt j = 0 ; j < iNumberOfItems ; j++ )
	{
		for ( TInt i = 0 ; i < iNumberOfItems ; i++ )
		{
			if ( i > 0 )
			{
				if ( iPointArray[i] > iPointArray[i - 1] )
				{
					TInt first  = iPointArray[i];
					TInt second = iPointArray[i - 1];
					
					iPointArray[i]     = second;
					iPointArray[i - 1] = first;
				}
			}
		}	
	}
}

void THighscoreHolder::RestorePointL(TInt aIndex, RReadStream& aStream)
{
	iPointArray[aIndex] = aStream.ReadInt32L();
}

// End of file