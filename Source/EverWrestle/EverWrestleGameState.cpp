// EverWrestle - A Peak Entertainment Production (2025)


#include "EverWrestleGameState.h"

#include "EverWrestleGameMode.h"
#include "Net/UnrealNetwork.h"

void AEverWrestleGameState::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		if (AEverWrestleGameMode* GM = Cast<AEverWrestleGameMode>(GetWorld()->GetAuthGameMode()))
		{
			GM->OnAllPlayersReadyDelegate.AddUniqueDynamic(this, &AEverWrestleGameState::SetAllPlayersReady);
		}
	}
}

AEverWrestleGameState::AEverWrestleGameState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEverWrestleGameState::SetCurrentRoundNumber(const uint8 NewRoundNumber)
{
	CurrentRoundNum = NewRoundNumber;
	
	if (HasAuthority())
		OnRep_CurrentRoundNumber();
}

void AEverWrestleGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AEverWrestleGameState, CurrentRoundTime);
	DOREPLIFETIME(AEverWrestleGameState, CurrentRoundNum);
	DOREPLIFETIME(AEverWrestleGameState, bAreAllPlayersReady);
}

void AEverWrestleGameState::OnRep_CurrentRoundTime()
{
	OnRoundTimeSynchronizationRequest.Broadcast(CurrentRoundTime);
}

void AEverWrestleGameState::OnRep_CurrentRoundNumber()
{
	OnRoundNumberChanged.Broadcast(CurrentRoundNum);
}

void AEverWrestleGameState::SetAllPlayersReady()
{
	if (HasAuthority())
	{
		bAreAllPlayersReady = true;
		
		OnRep_bAreAllPlayersReady();
	}
}

void AEverWrestleGameState::Multicast_ChangeTalkingState_Implementation(APlayerState* Player, bool bIsTalking) const
{
	OnAnyPlayerTalkingStateChanged.Broadcast(Player, bIsTalking);
}

void AEverWrestleGameState::OnRep_bAreAllPlayersReady()
{
	if (bAreAllPlayersReady)
	{
		OnAllPlayersReadyDelegate.Broadcast();
	}
}

void AEverWrestleGameState::MultiCast_StartRound_Implementation(const float MaxRoundTime)
{
	OnRoundStarted.Broadcast(MaxRoundTime);
}

void AEverWrestleGameState::MultiCast_EndRound_Implementation()
{
	OnRoundEnded.Broadcast();
}

void AEverWrestleGameState::OnTimeSynchronizationReceived(float SyncTime)
{
	CurrentRoundTime = SyncTime;
	
	if (HasAuthority())
		OnRep_CurrentRoundTime();
}
