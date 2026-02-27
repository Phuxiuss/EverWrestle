// EverWrestle - A Peak Entertainment Production (2026)

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VOIPLibrary.generated.h"

UCLASS()
class EVERWRESTLE_API UVOIPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// Steam Services
	UFUNCTION(BlueprintCallable, Category="Networking | Steam Services", meta = (WorldContext = "WorldContextObject"))
	static void ClearVoicePackets(UObject* WorldContextObject);
};