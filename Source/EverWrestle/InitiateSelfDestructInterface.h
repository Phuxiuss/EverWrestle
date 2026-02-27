// EverWrestle - A Peak Entertainment Production (2026)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InitiateSelfDestructInterface.generated.h"

UINTERFACE(Blueprintable)
class UInitiateSelfDestructInterface : public UInterface
{
	GENERATED_BODY()
};

class EVERWRESTLE_API IInitiateSelfDestructInterface
{ 
	GENERATED_BODY()
	
public:
	// World Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InGame | World Interaction")
	void InitiateSelfDestruct(const float Countdown);
};