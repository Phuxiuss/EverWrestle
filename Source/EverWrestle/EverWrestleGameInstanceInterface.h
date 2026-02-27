#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EverWrestleGameInstanceInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UEverWrestleGameInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

class EVERWRESTLE_API IEverWrestleGameInstanceInterface
{
	GENERATED_BODY()
	
public:
	// Scoring & Progression
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InGame | Point Management")
	void SetPersistantRoundNum(uint8 NewNumber);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InGame | Point Management")
	uint8 GetPersistantRoundNum();
};