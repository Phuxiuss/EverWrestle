#pragma once

#include "CoreMinimal.h"
#include "EverWrestleGameInstanceInterface.h"
#include "Engine/GameInstance.h"
#include "EverWrestleGameInstance.generated.h"

UCLASS()
class EVERWRESTLE_API UEverWrestleGameInstance : public UGameInstance, public IEverWrestleGameInstanceInterface
{
	GENERATED_BODY()
	
protected:
	virtual void Init() override;
	virtual void Shutdown() override;
	
private:
	UPROPERTY(BlueprintReadWrite, Category = "InGame | Round Management", meta = (AllowPrivateAccess))
	uint8 PersistantRoundNumber = 0;
};