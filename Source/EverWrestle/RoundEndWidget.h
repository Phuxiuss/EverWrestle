// EverWrestle - A Peak Entertainment Production (2025)

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoundEndWidget.generated.h"

USTRUCT(BlueprintType)
struct FPlayerScoreEntry
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "InGame | Player Appearance")
	FText PlayerName;
	
	UPROPERTY(BlueprintReadOnly, Category = "InGame | Scoring & Progression")
	int32 PlayerScore = 0;
	
	FPlayerScoreEntry() {}
	FPlayerScoreEntry(const FText& InPlayerName, const int32 InPlayerScore) 
		: PlayerName(InPlayerName), PlayerScore(InPlayerScore) {}
};

UCLASS()
class EVERWRESTLE_API URoundEndWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// UI Management
	UFUNCTION(BlueprintCallable, Category = "InGame | UI Management")
	void SetPlayerData(const TArray<FPlayerScoreEntry>& NewScores, const int32 MaxPoints, const bool bHasWinner);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "InGame | UI Management")
	void ConstructScoreEntries();
	
private:
	// Scoring & Progression State
	UPROPERTY(BlueprintReadWrite, Category = "InGame | Scoring & Progression", meta = (AllowPrivateAccess = "true"))
	TArray<FPlayerScoreEntry> PlayerData;
	
	UPROPERTY(BlueprintReadOnly, Category = "InGame | Scoring & Progression", meta = (AllowPrivateAccess = "true"))
	int32 MaxPointsForWin = 0;
	
	UPROPERTY(BlueprintReadOnly, Category = "InGame | Scoring & Progression", meta = (AllowPrivateAccess = "true"))
	bool bRoundOver = false;
};