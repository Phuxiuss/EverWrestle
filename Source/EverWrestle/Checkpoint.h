// EverWrestle - A Peak Entertainment Production (2025)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

class AEverWrestleCharacter;

UCLASS()
class EVERWRESTLE_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ACheckpoint();

	// World Interaction
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "InGame | World Interaction")
	void SetPlayerCheckPoint(AEverWrestleCharacter* Player) const;

protected:
	virtual void BeginPlay() override;
};