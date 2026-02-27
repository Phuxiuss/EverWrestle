// EverWrestle - A Peak Entertainment Production (2026)


#include "EverWrestleCrushTrap.h"

#include "EverWrestleCharacterInterface.h"
#include "Net/UnrealNetwork.h"

AEverWrestleCrushTrap::AEverWrestleCrushTrap()
{
	PrimaryActorTick.bCanEverTick = false;

	TrapMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("TrapMesh"));
	RootComponent = TrapMesh;
}

void AEverWrestleCrushTrap::BeginPlay()
{
	Super::BeginPlay();
	
	TrapMesh->PlayAnimation(TrapAnimation, true);
	TrapMesh->OnComponentHit.AddUniqueDynamic(this, &AEverWrestleCrushTrap::OnActorCollisionWithTrap);
}

void AEverWrestleCrushTrap::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AEverWrestleCrushTrap, bHasBeenHit);
}

void AEverWrestleCrushTrap::OnActorCollisionWithTrap(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!bHasBeenHit)
	{
		if (IsValid(OtherActor) && OtherActor->GetClass()->ImplementsInterface(UEverWrestleCharacterInterface::StaticClass()))
		{
			Server_HandlePlayerCollision(OtherActor);
		}
	}
}

void AEverWrestleCrushTrap::OnKnockoutEnd()
{
	bHasBeenHit = false;
}

void AEverWrestleCrushTrap::Server_HandlePlayerCollision_Implementation(AActor* PlayerToHandle)
{
	if (bHasBeenHit) return;
	
	bHasBeenHit = true;
	
	IEverWrestleCharacterInterface::Execute_LoseConsciousness(PlayerToHandle, KnockedOutDuration);
	
	GetWorldTimerManager().SetTimer(KnockedOutTimerHandle, this, &AEverWrestleCrushTrap::OnKnockoutEnd, KnockedOutDuration);
}
