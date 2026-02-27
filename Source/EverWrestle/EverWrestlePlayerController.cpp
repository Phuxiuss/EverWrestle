#include "EverWrestlePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

void AEverWrestlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	ResetInputComponent();
}

void AEverWrestlePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	ResetInputComponent();
}

void AEverWrestlePlayerController::ClientRestart_Implementation(class APawn* NewPawn)
{
	Super::ClientRestart_Implementation(NewPawn);
	
	if (IsLocalController())
	{
		SetShowMouseCursor(false);
		FInputModeGameOnly GameInputMode;
		SetInputMode(GameInputMode);
	}
	
	ResetInputComponent();
}

void AEverWrestlePlayerController::ResetInputComponent()
{
	SetIgnoreMoveInput(false);
	SetIgnoreLookInput(false);
	
	if (!IsLocalController()) return;
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		
		for (const UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}