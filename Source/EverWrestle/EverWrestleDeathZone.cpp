// EverWrestle - A Peak Entertainment Production (2026)


#include "EverWrestleDeathZone.h"

#include "EverWrestleCharacterInterface.h"

AEverWrestleDeathZone::AEverWrestleDeathZone()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEverWrestleDeathZone::ResetPlayerToCheckpoint(AActor* OtherActor)
{
	if (IsValid(OtherActor) && OtherActor->GetClass()->ImplementsInterface(UEverWrestleCharacterInterface::StaticClass()))
	{
		IEverWrestleCharacterInterface::Execute_ResetToLastCheckpoint(OtherActor);
	}
}