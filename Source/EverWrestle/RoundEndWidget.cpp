// EverWrestle - A Peak Entertainment Production (2025)


#include "RoundEndWidget.h"

void URoundEndWidget::SetPlayerData(const TArray<FPlayerScoreEntry>& NewScores, const int32 MaxPoints, const bool bHasWinner)
{
	if (NewScores.IsEmpty()) return;
	
	PlayerData.Empty();
	
	this->PlayerData = NewScores;
	
	this->MaxPointsForWin = MaxPoints;
	
	this->bRoundOver = bHasWinner;
	
	ConstructScoreEntries();
}