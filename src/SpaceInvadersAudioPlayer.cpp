/*
============================================================================
 Name		 : SpaceInvadersAudioPlayer.cpp
 Author	     : Arttu Salonen
 Version	 :
 Copyright   : Copyright Arttu Salonen 2009
 Description : CSpaceInvadersAudioPlayer implementation
============================================================================
*/
#include "SpaceInvadersAudioPlayer.h"

CSpaceInvadersAudioPlayer::CSpaceInvadersAudioPlayer()
{
	// No implementation required
}


CSpaceInvadersAudioPlayer::~CSpaceInvadersAudioPlayer()
{
	Cleanup();
}

CSpaceInvadersAudioPlayer* CSpaceInvadersAudioPlayer::NewLC()
{
	CSpaceInvadersAudioPlayer* self = new (ELeave)CSpaceInvadersAudioPlayer();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

CSpaceInvadersAudioPlayer* CSpaceInvadersAudioPlayer::NewL()
{
	CSpaceInvadersAudioPlayer* self=CSpaceInvadersAudioPlayer::NewLC();
	CleanupStack::Pop(); // self;
	return self;
}

void CSpaceInvadersAudioPlayer::ConstructL()
{
	iState = EIdle;
}

void CSpaceInvadersAudioPlayer::PlayMySampleL() 
{
	if ( iState == EIdle )
	{
		_LIT(KSampleFileName, "../sounds/space_invaders_music.wav");
		// Create a sample player and load sample from file KSampleFileName 
		iMySamplePlayer = CMdaAudioPlayerUtility::NewFilePlayerL( KSampleFileName,
				                                                  *this ); 
	}
}

void CSpaceInvadersAudioPlayer::StopPlay()
{
	Cleanup();
}

void CSpaceInvadersAudioPlayer::Cleanup()
{
	if ( iMySamplePlayer )
	{
		iMySamplePlayer->Stop();
		iMySamplePlayer->Close();
		delete iMySamplePlayer;
		iMySamplePlayer = NULL;
		iState = EIdle;
	}
}

void CSpaceInvadersAudioPlayer::MapcInitComplete(TInt aError,
		                        const TTimeIntervalMicroSeconds& /*aDuration*/)
{ 
	if (aError)
	{
		Cleanup();
		return;
	}
		
	if (iState == EPlayFilePrepare)
	{
		iState = EPlayFilePlaying;
		iMySamplePlayer->Play();
		return;
	}
} 
		 
void CSpaceInvadersAudioPlayer::MapcPlayComplete(TInt aError)
{
	/*
	 * The status of playback. The following values have the same specific
	 * meaning across all EPOC platforms: KErrNone playing of the audio sample
	 * is complete. KErrCorrupt the sample data is corrupt. KErrInUse the
	 * sound device is in use by another higher priority client. This can
	 * happen during playback. KErrNoMemory there is insufficient memory to
	 * play this audio sample Other values are possible indicating a problem
	 * opening the audio sample. These values are dependent on the EPOC
	 * platform.
	 */
	Cleanup();
}
