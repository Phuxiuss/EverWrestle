// EverWrestle - A Peak Entertainment Production (2026)


#include "GameHUD.h"

void AGameHUD::SwitchToGameUI()
{
	SetCurrentWidget(GameUIWidget, EInputType::GameOnly, false);
}

void AGameHUD::SwitchToScoreboard(const TArray<FPlayerScoreEntry>& FinalScores, const int32 MaxPoints, const bool bHasWinner)
{
	SetCurrentWidget(ScoreboardUIWidget, EInputType::UIOnly, true);
	
	if (URoundEndWidget* EndWidget = Cast<URoundEndWidget>(CurrentGameHUD))
	{
		EndWidget->SetPlayerData(FinalScores, MaxPoints, bHasWinner);
	}
}