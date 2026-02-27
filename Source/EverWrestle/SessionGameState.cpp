// EverWrestle - A Peak Entertainment Production (2026)


#include "SessionGameState.h"

void ASessionGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
	
	OnPlayerArrayChanged.Broadcast(PlayerArray);
}

void ASessionGameState::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);
	
	OnPlayerArrayChanged.Broadcast(PlayerArray);
}
