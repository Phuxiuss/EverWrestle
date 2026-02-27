// EverWrestle - A Peak Entertainment Production (2025)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EverWrestleTaskZone.generated.h"

class UWidget;
class AEverWrestleCharacter;

UCLASS()
class EVERWRESTLE_API AEverWrestleTaskZone : public AActor
{
	GENERATED_BODY()

private:
	UFUNCTION(BlueprintCallable, Category="InGame | TaskZone", meta = (AllowPrivateAccess = "true"))
	void UpdateProgressTimer();
	UFUNCTION()
	void OnSkipTimerSecondOver();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="InGame | TaskZone", meta = (AllowPrivateAccess = "true", Units = "s"))
	float MaxTimeForSkip = 15.f;
	UPROPERTY(BlueprintReadOnly, Category="InGame | TaskZone", meta = (AllowPrivateAccess = "true", Units = "s"))
	float CurrentSkipTime = 0.f;
	
	FTimerHandle SkipTimerHandle;
};
