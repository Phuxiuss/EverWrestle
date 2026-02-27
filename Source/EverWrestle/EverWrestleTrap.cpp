// EverWrestle - A Peak Entertainment Production (2026)


#include "EverWrestleTrap.h"

AEverWrestleTrap::AEverWrestleTrap()
{
	PrimaryActorTick.bCanEverTick = false;
	
	bReplicates = true;
}

void AEverWrestleTrap::BeginPlay()
{
	Super::BeginPlay();
}
