// EverWrestle - A Peak Entertainment Production (2026)


#include "EverWrestleMovingTrap.h"

#include "EverWrestleCharacterInterface.h"
#include "Net/UnrealNetwork.h"

AEverWrestleMovingTrap::AEverWrestleMovingTrap()
{
	TrapMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("TrapMesh"));
	RootComponent = TrapMesh;
	
	TrapMesh->SetCollisionProfileName(FName("PhysicsActor"));
	TrapMesh->PlayAnimation(TrapAnimation, true);
	TrapMesh->OnComponentHit.AddUniqueDynamic(this, &AEverWrestleMovingTrap::OnActorCollisionWithTrap);
}

void AEverWrestleMovingTrap::OnActorCollisionWithTrap(UPrimitiveComponent* HitComponent, AActor* OtherActor,
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

void AEverWrestleMovingTrap::Server_HandlePlayerCollision_Implementation(AActor* PlayerToHandle)
{
	if (!HasAuthority()) return;
	
	HandlePlayerCollision(PlayerToHandle);
}

void AEverWrestleMovingTrap::OnKnockoutEnd()
{
	bHasBeenHit = false;
}

void AEverWrestleMovingTrap::HandlePlayerCollision(AActor* PlayerToHandle)
{
	if (bHasBeenHit) return;
	
	bHasBeenHit = true;
	
	IEverWrestleCharacterInterface::Execute_LoseConsciousness(PlayerToHandle, KnockedOutDuration);
	
	GetWorldTimerManager().SetTimer(KnockedOutTimerHandle, this, &AEverWrestleMovingTrap::OnKnockoutEnd, KnockedOutDuration);
}

void AEverWrestleMovingTrap::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AEverWrestleMovingTrap, bHasBeenHit);
}
