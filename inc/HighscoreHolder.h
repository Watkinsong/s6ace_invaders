/*
============================================================================
 Name		 : HighscoreHolder.h
 Author	     : Arttu Salonen
 Copyright   : Copyright 2009 Arttu Salonen
 Description : Holds and stores the highscores of the game.
============================================================================
*/

#ifndef HIGHSCOREHOLDER_H_
#define HIGHSCOREHOLDER_H_

#include <e32base.h>
#include <s32std.h>
#include <s32stor.h>
#include <e32cmn.h> 

// CLASS DECLARATION
/**
* Holds the points of the current game and those of in the highscores list.
*/

class THighscoreHolder
{
public:

	/**
	 * The constructor.
	 */
	THighscoreHolder();
	
	/**
	 * The destructor.
	 */
	virtual ~THighscoreHolder();
	
	/**
	 * Inits the point array.
	 */
	void InitPointArray();
	
	/**
	 * Saves the attributes of the class.
	 * 
	 * @param CStreamStore& aStore  The stream store.
	 */
	TStreamId StoreL(CStreamStore& aStore) const;
	
	/**
	 * Restores the attributes of the class.
	 * 
	 * @param CStreamStore aStore    The stream store.
	 * @param TStreamId    aStreamId The id of the stream.
	 */
	void RestoreL(const CStreamStore& aStore, TStreamId aStreamId);
	
	/**
	 * Sets the active poinst.
	 */
	void SetActivePoints(TInt aActivePoints);
	
	/**
	 * Gets the active points.
	 */
	TInt ActivePoints();
	
	/**
	 * Sets the number of items in the highscores list.
	 */
	TInt NumberOfItems();
	
	/**
	 * Gets the array of the highscores.
	 */
	TFixedArray<TInt, 10> PointArray();
	
	/**
	 * Updates the highscore points by checking if the user's current point
	 * can make it to the list.
	 */
	void UpdatePoints();
	
	/**
	 * Sorts points using bubble sort algorithm.
	 */
	void SortPoints();
	
	void RestorePointL(TInt aIndex, RReadStream& aStream);
	
private:

	/**
	 * Number of items on the highscores list.
	 */
	TInt iNumberOfItems;

	/**
	 * The array to store the highscores.
	 */
	TFixedArray<TInt, 10> iPointArray;
	
	/**
	 * Keeps track of the player's current points.
	 */
	TInt iActivePoints;
	
	/**
	 * Externalizes the attributes of the class to store them permanently.
	 * Used by the SpaceInvadersDocument.
	 */
	void ExternalizeL(RWriteStream& aStream) const;

	/**
	 * Internalizes the attributes of the class to restore them form permanent
	 * storage.
	 * Used by the SpaceInvadersDocument.
	 */
	void InternalizeL(RReadStream& aStream);
};

#endif /*HIGHSCOREHOLDER_H_*/
