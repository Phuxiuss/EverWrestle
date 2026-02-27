// EverWrestle - A Peak Entertainment Production (2025)


#include "Checkpoint.h"

#include "EverWrestleCharacter.h"

ACheckpoint::ACheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
}

void ACheckpoint::SetPlayerCheckPoint_Implementation(AEverWrestleCharacter* Player) const
{
	Player->SetCheckpoint(GetActorLocation());
}