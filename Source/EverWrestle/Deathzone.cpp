// EverWrestle - A Peak Entertainment Production (2025)


#include "Deathzone.h"

#include "Components/BoxComponent.h"

ADeathzone::ADeathzone()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("PlayerDeathCollider"));
	RootComponent = BoxCollision;
}

void ADeathzone::BeginPlay()
{
	Super::BeginPlay();
}