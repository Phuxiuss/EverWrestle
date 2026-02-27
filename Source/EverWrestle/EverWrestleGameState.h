// EverWrestle - A Peak Entertainment Production (2025)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "EverWrestleGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllPlayersReadyDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundTimeSychronizationRequest, float, NewTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundNumberChanged, uint8, NewRound);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundStarted, float, MAX_ROUND_TIME);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyPlayerTalkingStateChanged, APlayerState*, Player, bool, bIsTalking);

UCLASS()
class EVERWRESTLE_API AEverWrestleGameState : public AGameState
{
	GENERATED_BODY()

public:
	AEverWrestleGameState();

	// Round Management
	UFUNCTION(BlueprintGetter, BlueprintCallable, Category ="InGame | Round Management")
	FORCEINLINE uint8 GetCurrentRoundNumber() const { return CurrentRoundNum; }
	
	UFUNCTION(BlueprintGetter, BlueprintCallable, Category ="InGame | Round Management")
	FORCEINLINE float GetCurrentRoundTime() const { return CurrentRoundTime; }
	
	UFUNCTION(BlueprintSetter, BlueprintCallable, Category ="InGame | Round Management")
	void SetCurrentRoundNumber(uint8 NewRoundNumber);

	UFUNCTION(NetMulticast, Reliable, Category="InGame | Round Management")
	void MultiCast_StartRound(const float MaxRoundTime);
	
	UFUNCTION(NetMulticast, Reliable, Category="InGame | Round Management")
	void MultiCast_EndRound();

	// Session Logistics
	UFUNCTION(BlueprintCallable, Category="Networking | Session Logistics")
	FORCEINLINE bool GetIsGameReady() { return bAreAllPlayersReady; }
	
	UFUNCTION(BlueprintCallable, Category="Networking | Session Logistics")
	void SetAllPlayersReady();

	// Voice Chat
	UFUNCTION(NetMulticast, Unreliable, BlueprintCallable, Category="Networking | Voice Chat")
	void Multicast_ChangeTalkingState(APlayerState* Player, bool bIsTalking) const;

	// Callbacks
	UFUNCTION()
	void OnTimeSynchronizationReceived(float SyncTime);

	// Delegates
	UPROPERTY(BlueprintAssignable, Category ="InGame | Round Management")
	FOnRoundTimeSychronizationRequest OnRoundTimeSynchronizationRequest;
	UPROPERTY(BlueprintAssignable, Category ="InGame | Round Management")
	FOnRoundNumberChanged OnRoundNumberChanged;
	UPROPERTY(BlueprintAssignable, Category ="InGame | Round Management")
	FOnRoundStarted OnRoundStarted;
	UPROPERTY(BlueprintAssignable, Category ="InGame | Round Management")
	FOnRoundEnded OnRoundEnded;
	UPROPERTY(BlueprintAssignable, Category ="Networking | Session Logistics")
	FOnAllPlayersReadyDelegate OnAllPlayersReadyDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Networking | Voice Chat")
	FOnAnyPlayerTalkingStateChanged OnAnyPlayerTalkingStateChanged;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(ReplicatedUsing=OnRep_CurrentRoundTime)
	float CurrentRoundTime;
	
	UPROPERTY(ReplicatedUsing=OnRep_CurrentRoundNumber)
	uint8 CurrentRoundNum = 0;

	UPROPERTY(ReplicatedUsing=OnRep_bAreAllPlayersReady)
	bool bAreAllPlayersReady = false;

private:
	// RepNotifies
	UFUNCTION()
	void OnRep_CurrentRoundTime();
	UFUNCTION()
	void OnRep_CurrentRoundNumber();
	UFUNCTION()
	void OnRep_bAreAllPlayersReady();
};