// EverWrestle - A Peak Entertainment Production (2026)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SessionGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerArrayChangedDelegate, const TArray<APlayerState*>&, PlayerList);

UCLASS()
class EVERWRESTLE_API ASessionGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	// Player Management
	UPROPERTY(BlueprintAssignable, Category = "InGame | Player Management")
	FOnPlayerArrayChangedDelegate OnPlayerArrayChanged;
	
protected:
	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;
};