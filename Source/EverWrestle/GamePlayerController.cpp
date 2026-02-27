// EverWrestle - A Peak Entertainment Production (2026)


#include "GamePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EverWrestleHUD.h"
#include "GameHUD.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicsEngine/PhysicalAnimationComponent.h"

void AGamePlayerController::Client_InitiateSwitchToScoreboard_Implementation(
	const TArray<FPlayerScoreEntry>& FinalScores, const int32 MaxPoints, const bool bHasWinner)
{
	if (AGameHUD* HUD = Cast<AGameHUD>(this->GetHUD()))
	{
		HUD->SwitchToScoreboard(FinalScores, MaxPoints, bHasWinner);
	}
}

void AGamePlayerController::Client_PrepareForTravel_Implementation()
{
	SetIgnoreLookInput(true);
	SetIgnoreMoveInput(true);
	FlushPressedKeys();
	
	if (APawn* P = GetPawn())
	{
		P->SetActorEnableCollision(false);
		P->DisableComponentsSimulatePhysics();
		P->SetActorHiddenInGame(true);
		
		if (UActorComponent* RagdollComp = P->GetComponentByClass(StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Script/AnimReplicatedRagdoll.ReplicatedRagdollComponent"), nullptr, LOAD_None, nullptr)))
		{
			RagdollComp->Deactivate();
		}
		
		if (const ACharacter* Char = Cast<ACharacter>(P))
		{
			if (UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement())
			{
				MoveComp->StopMovementImmediately();
				MoveComp->DisableMovement();
				MoveComp->Deactivate();
			}
			
			if (USkeletalMeshComponent* Mesh = Char->GetMesh())
			{
				Mesh->SetSimulatePhysics(false);
				Mesh->PutRigidBodyToSleep();
				Mesh->Deactivate();
				Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Mesh->SetAllBodiesSimulatePhysics(false);
				Mesh->SetAllBodiesBelowPhysicsBlendWeight("pelvis", 0.f, false, false);
				Mesh->SetAllBodiesBelowSimulatePhysics("pelvis", false, false);
				Mesh->SetComponentTickEnabled(false);
				Mesh->bNoSkeletonUpdate = true;
			}
			
			if (UPhysicalAnimationComponent* PhysComp = Char->FindComponentByClass<UPhysicalAnimationComponent>())
			{
				PhysComp->SetSkeletalMeshComponent(nullptr);
				PhysComp->Deactivate();
			}
		}
	}
}

void AGamePlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	
	OnControllerPossessed();
}

void AGamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	OnControllerPossessed();
}
