// EverWrestle - A Peak Entertainment Production (2026)

#pragma once

#include "CoreMinimal.h"
#include "EverWrestlePlayerController.h"
#include "GamePlayerController.generated.h"

struct FPlayerScoreEntry;

UCLASS()
class EVERWRESTLE_API AGamePlayerController : public AEverWrestlePlayerController
{
	GENERATED_BODY()
	
public:
	// UI Management
	UFUNCTION(Client, Reliable, Category = "InGame | UI Management")
	void Client_InitiateSwitchToScoreboard(const TArray<FPlayerScoreEntry>& FinalScores, const int32 MaxPoints, const bool bHasWinner = false);
	
	// Round Management
	UFUNCTION(Client, Reliable, Category = "InGame | Round Management")
	void Client_PrepareForTravel();
	
protected:
	virtual void OnRep_Pawn() override;
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "InGame | Player Management")
	void OnControllerPossessed();
};