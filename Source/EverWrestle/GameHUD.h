// EverWrestle - A Peak Entertainment Production (2026)

#pragma once

#include "CoreMinimal.h"
#include "EverWrestleHUD.h"
#include "GameHUD.generated.h"

struct FPlayerScoreEntry;

UCLASS()
class EVERWRESTLE_API AGameHUD : public AEverWrestleHUD
{
	GENERATED_BODY()
	
public:
	// UI Management
	UFUNCTION(BlueprintCallable, Category = "InGame | UI Management")
	void SwitchToGameUI();

	UFUNCTION(BlueprintCallable, Category = "InGame | UI Management")
	void SwitchToScoreboard(const TArray<FPlayerScoreEntry>& FinalScores, const int32 MaxPoints, const bool bHasWinner);
	
private:
	// Configuration
	UPROPERTY(EditDefaultsOnly, Category = "InGame | UI Management", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ScoreboardUIWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "InGame | UI Management", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> GameUIWidget;
};