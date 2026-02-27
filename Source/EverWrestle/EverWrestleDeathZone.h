// EverWrestle - A Peak Entertainment Production (2026)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EverWrestleDeathZone.generated.h"

UCLASS()
class EVERWRESTLE_API AEverWrestleDeathZone : public AActor
{
	GENERATED_BODY()
	
public:	
	AEverWrestleDeathZone();

private:
	// World Interaction
	UFUNCTION(BlueprintCallable, Category = "InGame | World Interaction", meta = (AllowPrivateAccess = "true"))
	void ResetPlayerToCheckpoint(AActor* OtherActor);
};