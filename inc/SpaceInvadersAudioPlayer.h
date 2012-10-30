/*
============================================================================
 Name		: SpaceInvadersAudioPlayer.h
 Author	  : Arttu Salonen
 Version	 :
 Copyright   : Copyright Arttu Salonen 2009
 Description : CSpaceInvadersAudioPlayer declaration
============================================================================
*/

#ifndef SPACEINVADERSAUDIOPLAYER_H
#define SPACEINVADERSAUDIOPLAYER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
//#include <MdaAudioSamplePlayer.h>
#include <mdaaudiosampleplayer.h>

// CLASS DECLARATION

/**
*  CSpaceInvadersAudioPlayer
* 
*/
class CSpaceInvadersAudioPlayer : public CBase, public MMdaAudioPlayerCallback
{
public: // Constructors and destructor

	/**
		* Destructor.
		*/
	~CSpaceInvadersAudioPlayer();

		/**
		* Two-phased constructor.
		*/
	static CSpaceInvadersAudioPlayer* NewL();

		/**
		* Two-phased constructor.
		*/
	static CSpaceInvadersAudioPlayer* NewLC();

private:

	/**
		* Constructor for performing 1st stage construction
		*/
	CSpaceInvadersAudioPlayer();

	/**
		* EPOC default constructor for performing 2nd stage construction
		*/
	void ConstructL();
	
	CMdaAudioPlayerUtility* iMySamplePlayer;
	
	enum TState {EIdle,
			     EPlayFilePrepare,
				 EPlayFilePlaying };

	TState iState;
				 
	void Cleanup();

public:

	void PlayMySampleL();
	
	void StopPlay();
	
	void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& /*aDuration*/);
	
	void MapcPlayComplete(TInt aError);
};

#endif // SPACEINVADERSAUDIOPLAYER_H

