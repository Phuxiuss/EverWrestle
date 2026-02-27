// EverWrestle - A Peak Entertainment Production (2026)

#pragma once

#include "CoreMinimal.h"
#include "EverWrestleCharacterInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UEverWrestleCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

class EVERWRESTLE_API IEverWrestleCharacterInterface
{
	GENERATED_BODY()
	
public:
	// World Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InGame | World Interaction")
	void ResetToLastCheckpoint();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InGame | World Interaction")
	void SetPlayerCheckpoint(FVector CheckpointPosition);

	// Combat & Health
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InGame | Combat & Health")
	void LoseConsciousness(const float KnockedOutDuration);
	
	// Physics & Animation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InGame | Physics & Animation")
	void SetRagdolled(bool MakeRagdolled);
};