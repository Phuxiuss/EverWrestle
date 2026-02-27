// EverWrestle - A Peak Entertainment Production (2025)

#pragma once

#include "CoreMinimal.h"
#include "SessionPlayerState.h"
#include "GameFramework/PlayerState.h"
#include "EverWrestlePlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreNumberChanged, int32, NewScore);

USTRUCT(BlueprintType)
struct FCharacterMeshData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USkeletalMesh> CharacterMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UMaterialInterface> CharacterMaterial;
};

UCLASS()
class EVERWRESTLE_API AEverWrestlePlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AEverWrestlePlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OverrideWith(APlayerState* PlayerState) override;

	// Scoring & Progression
	UFUNCTION(BlueprintCallable, Category = "InGame | Scoring & Progression")
	int32 GetCurrentPoints() const { return PlayerPoints; }

	void AddScore(const uint16 Amount);
	void SubScore(const uint16 Amount);
	void SetScore(const uint16 NewScore);

	UPROPERTY(BlueprintAssignable, Category = "InGame | Scoring & Progression")
	FOnScoreNumberChanged OnScoreNumberChanged;

	// Player Appearance
	UFUNCTION(BlueprintCallable, Category = "InGame | Player Appearance")
	void SetCharacter(const ECharacterType& CharacterType);

	void ApplyCharacterMesh();

	UPROPERTY(ReplicatedUsing=OnRep_CurrentCharacterType, BlueprintReadOnly, Category = "InGame | Player Appearance")
	ECharacterType CurrentCharacterType = ECharacterType::AXOLOTLE;

	// World Interaction
	UFUNCTION(BlueprintCallable, Category = "InGame | World Interaction")
	void SetLastCheckpointLocation(const FVector NewLocation) { LastCheckpointLocation_CPP = NewLocation; }

protected:
	virtual void CopyProperties(APlayerState* PlayerState) override;

	// RepNotifies
	UFUNCTION()
	void OnRep_PlayerPointsChanged();

	UFUNCTION()
	void OnRep_CurrentCharacterType();

private:
	UFUNCTION()
	void LoadCharacterDataAsync(FCharacterMeshData Data);
	
	UFUNCTION()
	void OnCharacterDataLoaded(FCharacterMeshData Data);
	// Internal State
	UPROPERTY(ReplicatedUsing=OnRep_PlayerPointsChanged, BlueprintReadOnly, Category="InGame | Scoring & Progression", meta=(AllowPrivateAccess="true"))
	int32 PlayerPoints = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="InGame | Player Appearance", meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterType, FCharacterMeshData> CharacterTextureMap;

	UPROPERTY()
	FVector LastCheckpointLocation_CPP;
};