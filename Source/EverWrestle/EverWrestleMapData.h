// EverWrestle - A Peak Entertainment Production (2026)

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EverWrestleMapData.generated.h"

UCLASS()
class EVERWRESTLE_API UEverWrestleMapData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// Round Management
	UFUNCTION(BlueprintCallable, Category = "InGame | Round Management", meta = (WorldContext = "WorldContextObject"))
	TSoftObjectPtr<UWorld> GetRandomMapFromPool(const UObject* WorldContextObject) const;
	
	UFUNCTION(BlueprintCallable, Category = "InGame | Round Management")
	FORCEINLINE TArray<TSoftObjectPtr<UWorld>> GetMapRotationPool() const { return MapRotationPool; }
	
private:
	// Configuration
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InGame | Round Management", meta = (AllowPrivateAccess = "true"))
	TArray<TSoftObjectPtr<UWorld>> MapRotationPool;
};