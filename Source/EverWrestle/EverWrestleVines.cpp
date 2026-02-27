// EverWrestle - A Peak Entertainment Production (2026)


#include "EverWrestleVines.h"

#include "EverWrestleCharacterInterface.h"
#include "Components/BoxComponent.h"

AEverWrestleVines::AEverWrestleVines()
{
	PrimaryActorTick.bCanEverTick = false;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	
	RootComponent = MeshComponent;
	BoxCollision->SetupAttachment(MeshComponent);
}

void AEverWrestleVines::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (IsValid(OtherActor) && OtherActor->GetClass()->ImplementsInterface(UEverWrestleCharacterInterface::StaticClass()))
	{
		IEverWrestleCharacterInterface::Execute_LoseConsciousness(OtherActor, KnockoutDuration);
	}
}
