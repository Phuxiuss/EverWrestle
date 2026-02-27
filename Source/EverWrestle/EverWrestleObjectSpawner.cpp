// EverWrestle - A Peak Entertainment Production (2026)


#include "EverWrestleObjectSpawner.h"

#include "EverWrestleMacros.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AEverWrestleObjectSpawner::AEverWrestleObjectSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollider"));
	Arrow = CreateDefaultSubobject<UArrowComponent>(FName("Arrow"));
	RootComponent = BoxCollider;
	Arrow->SetupAttachment(BoxCollider);
	
	Arrow->SetUsingAbsoluteScale(true);
	Arrow->SetArrowSize(5.f);
	Arrow->SetArrowLength(100.f);
}


void AEverWrestleObjectSpawner::BeginPlay()
{
	Super::BeginPlay();
	Server_StartSpawnCycle();
}

void AEverWrestleObjectSpawner::Server_StartSpawnCycle_Implementation()
{
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AEverWrestleObjectSpawner::SpawnObjects, SpawnInterval, true);
} 

void AEverWrestleObjectSpawner::SpawnObjects()
{
	if (ObjectsToSpawn.IsEmpty()) return;
	
	for (int i = 0; i < FMath::RandRange(MinObjectSpawn, MaxObjectSpawn); ++i)
	{
		const uint8 Index = FMath::RandRange(0, ObjectsToSpawn.Num() - 1);
		const FVector ScaleExtent = BoxCollider->GetScaledBoxExtent();
		
		FVector ChosenTransformAbs = ScaleExtent.GetAbs();
		FVector ChosenTransformNeg = -ScaleExtent;
		
		// set random Transform
		const float x = FMath::RandRange(ChosenTransformNeg.X, ChosenTransformAbs.X);
		const float y = FMath::RandRange(ChosenTransformNeg.Y, ChosenTransformAbs.Y);
		const float z = FMath::RandRange(ChosenTransformNeg.Z, ChosenTransformAbs.Z);
		const FVector ChosenTransform = FVector(x, y, z) + BoxCollider->GetComponentLocation();
			
		// set random rotation
		FRotator RandomRotation = FRotator(
		FMath::RandRange(0.f, 360.f),
		FMath::RandRange(0.f, 360.f), 
		 FMath::RandRange(0.f, 360.f)
        );
		
		// set random scale
		FVector RandomScale = FVector(
		FMath::RandRange(MinObjectScale, MaxObjectScale),
		FMath::RandRange(MinObjectScale, MaxObjectScale), 
		FMath::RandRange(MinObjectScale, MaxObjectScale)
		);
		
		FTransform RandomTransform;
		RandomTransform.SetLocation(ChosenTransform);
		RandomTransform.SetRotation(RandomRotation.Quaternion());
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.TransformScaleMethod = ESpawnActorScaleMethod::OverrideRootScale;
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
		ObjectsToSpawn[Index], 
		RandomTransform, 
		SpawnParams
		);
		
		if (SpawnedActor)
		{
			UPrimitiveComponent* PrimitiveComponent = SpawnedActor->FindComponentByClass<UPrimitiveComponent>();
			SpawnedActor->SetActorScale3D(RandomScale);
			if (PrimitiveComponent && PrimitiveComponent->IsSimulatingPhysics() == true)
			{

				FVector Impulse = Arrow->GetForwardVector() * ImpulseStrength;

				PrimitiveComponent->AddImpulse(
					Impulse,
					NAME_None,
					true
				);
			}
			
			if (SpawnedActor->GetClass()->ImplementsInterface(UInitiateSelfDestructInterface::StaticClass()))
			{
				IInitiateSelfDestructInterface::Execute_InitiateSelfDestruct(SpawnedActor, ObjectDespawnDuration);
			}
		}
		
	}
	
}