// EverWrestle - A Peak Entertainment Production (2026)

#include "EverWrestleMovingObject.h"

#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"

AEverWrestleMovingObject::AEverWrestleMovingObject()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;

	MoveTimeline = CreateDefaultSubobject<UTimelineComponent>("MoveTimeline");
	MoveTimeline->SetLooping(false);
	MoveTimeline->SetNetAddressable();
}

#if WITH_EDITOR
void AEverWrestleMovingObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!MeshComponent)
	{
		return;
	}

	const FVector StartWorld = MeshComponent->GetComponentLocation();
	const FVector TargetWorld = Transform.TransformPosition(TargetRelativeLocation);

	DrawDebugLine(
		GetWorld(),
		StartWorld,
		TargetWorld,
		FColor::Emerald,
		false,
		-1.f,
		0,
		3.f
	);

	DrawDebugDirectionalArrow(
		GetWorld(),
		StartWorld,
		TargetWorld,
		150.f,
		FColor::Cyan,
		false,
		-1.f,
		0,
		4.f
	);
}
#endif

void AEverWrestleMovingObject::BeginPlay()
{
	Super::BeginPlay();

	if (!MoveCurve)
	{
		UE_LOG(LogTemp, Error, TEXT("MoveCurve missing on %s"), *GetName());
		return;
	}

	FOnTimelineFloat UpdateDelegate;
	UpdateDelegate.BindUFunction(this, "OnTimelineUpdate");

	FOnTimelineEvent FinishedDelegate;
	FinishedDelegate.BindUFunction(this, "OnTimelineFinished");

	MoveTimeline->AddInterpFloat(MoveCurve, UpdateDelegate);
	MoveTimeline->SetTimelineFinishedFunc(FinishedDelegate);
	MoveTimeline->SetPlayRate(1.f / MoveDuration);

	if (HasAuthority())
	{
		InitialWorldLocation = GetActorLocation();
		TargetWorldLocation =
			GetActorTransform().TransformPosition(TargetRelativeLocation);

		MovementDirection = EMovementDirection::Forward;
		StartMovement_Server();
	}
}

void AEverWrestleMovingObject::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(PauseTimerHandle);
	Super::EndPlay(EndPlayReason);
}

void AEverWrestleMovingObject::StartMovement_Server()
{
	if (!HasAuthority())
	{
		return;
	}

	ReplicatedStartLocation =
		(MovementDirection == EMovementDirection::Forward)
		? InitialWorldLocation
		: TargetWorldLocation;

	ReplicatedTargetLocation =
		(MovementDirection == EMovementDirection::Forward)
		? TargetWorldLocation
		: InitialWorldLocation;

	OnRep_MoveData();
}

void AEverWrestleMovingObject::OnRep_MoveData()
{
	LocalStartLocation = ReplicatedStartLocation;
	LocalTargetLocation = ReplicatedTargetLocation;

	StartMovement_Local();
}

void AEverWrestleMovingObject::StartMovement_Local()
{
	MoveTimeline->PlayFromStart();
}

void AEverWrestleMovingObject::OnTimelineUpdate(float Alpha)
{
	const FVector NewLocation =
		FMath::Lerp(LocalStartLocation, LocalTargetLocation, Alpha);

	SetActorLocation(NewLocation);
}

void AEverWrestleMovingObject::OnTimelineFinished()
{
	if (!HasAuthority())
	{
		return;
	}

	MovementDirection =
		(MovementDirection == EMovementDirection::Forward)
			? EMovementDirection::Backward
			: EMovementDirection::Forward;

	if (PauseDuration <= 0.f)
	{
		StartMovement_Server();
	}
	else
	{
		GetWorldTimerManager().SetTimer(
			PauseTimerHandle,
			this,
			&AEverWrestleMovingObject::StartMovement_Server,
			PauseDuration,
			false
		);
	}
}

void AEverWrestleMovingObject::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps
) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEverWrestleMovingObject, ReplicatedStartLocation);
	DOREPLIFETIME(AEverWrestleMovingObject, ReplicatedTargetLocation);
}