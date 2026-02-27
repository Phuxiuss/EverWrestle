// EverWrestle - A Peak Entertainment Production (2026)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SessionPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerNameReceivedDelegate);

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	RED_PANDA,
	GEKKO,
	LEMUR,
	AXOLOTLE
};

UCLASS()
class EVERWRESTLE_API ASessionPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	// Player Appearance
	UFUNCTION(BlueprintCallable, Category = "InGame | Player Appearance")
	void SetCharacter(const ECharacterType& NewCharacterType);

	UPROPERTY(BlueprintReadWrite, Category = "InGame | Player Appearance", meta = (AllowPrivateAccess = "true"))
	ECharacterType CharacterType = ECharacterType::AXOLOTLE;
	
protected:
	virtual void CopyProperties(APlayerState* PlayerState) override;
};