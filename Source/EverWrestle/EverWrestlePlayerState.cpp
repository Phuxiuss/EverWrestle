// EverWrestle - A Peak Entertainment Production (2025)


#include "EverWrestlePlayerState.h"

#include "EverWrestleCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Net/UnrealNetwork.h"

AEverWrestlePlayerState::AEverWrestlePlayerState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEverWrestlePlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AEverWrestlePlayerState, PlayerPoints);
	DOREPLIFETIME(AEverWrestlePlayerState, CurrentCharacterType);
}

void AEverWrestlePlayerState::OverrideWith(APlayerState* PlayerState)
{
	Super::OverrideWith(PlayerState);
	
	if (const AEverWrestlePlayerState* OldPS = Cast<AEverWrestlePlayerState>(PlayerState))
	{
		this->PlayerPoints = OldPS->PlayerPoints;
	}
}

void AEverWrestlePlayerState::SetCharacter(const ECharacterType& CharacterType)
{
	CurrentCharacterType = CharacterType;
	
	ApplyCharacterMesh();
}

void AEverWrestlePlayerState::OnRep_PlayerPointsChanged()
{
	OnScoreNumberChanged.Broadcast(PlayerPoints);
}

void AEverWrestlePlayerState::CopyProperties(APlayerState* PlayerState)
{
	if (AEverWrestlePlayerState* NewPS = Cast<AEverWrestlePlayerState>(PlayerState))
	{
		NewPS->PlayerPoints = this->PlayerPoints;
		NewPS->CurrentCharacterType = this->CurrentCharacterType;
	}
	
	Super::CopyProperties(PlayerState);
}

void AEverWrestlePlayerState::OnRep_CurrentCharacterType()
{
	ApplyCharacterMesh();
}

void AEverWrestlePlayerState::LoadCharacterDataAsync(FCharacterMeshData Data)
{
	TArray<FSoftObjectPath> AssetsToLoad;
	AssetsToLoad.Add(Data.CharacterMesh.ToSoftObjectPath());
	AssetsToLoad.Add(Data.CharacterMaterial.ToSoftObjectPath());
	
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	
	Streamable.RequestAsyncLoad(
		AssetsToLoad,
		FStreamableDelegate::CreateUObject(this, &AEverWrestlePlayerState::OnCharacterDataLoaded, Data)
		);
}

void AEverWrestlePlayerState::OnCharacterDataLoaded(FCharacterMeshData Data)
{
	if (USkeletalMesh* LoadedMesh = Data.CharacterMesh.Get())
	{
		APawn* MyPawn = GetPawn();
		if (!MyPawn) return;
		
		const AEverWrestleCharacter* Char = Cast<AEverWrestleCharacter>(MyPawn);
		if (!Char) return;
		
		USkeletalMeshComponent* MeshComp = Char->GetMesh();
		if (!MeshComp) return;
		
		if (USkeletalMesh* MeshToApply = Data.CharacterMesh.Get())
		{
			MeshComp->SetSkeletalMesh(MeshToApply);
		}
		
		if (UMaterialInterface* MaterialToApply = Data.CharacterMaterial.Get())
		{
			MeshComp->SetMaterial(0, MaterialToApply);
		}
	}
}

void AEverWrestlePlayerState::ApplyCharacterMesh()
{
	FCharacterMeshData* FoundData = CharacterTextureMap.Find(CurrentCharacterType);

	if (FoundData)
	{
		LoadCharacterDataAsync(*FoundData);
	}
}

void AEverWrestlePlayerState::AddScore(const uint16 Amount)
{
	if (HasAuthority())
	{
		PlayerPoints = FMath::Clamp(PlayerPoints + Amount, 0, UINT16_MAX);
		
		OnRep_PlayerPointsChanged();
	}
}

void AEverWrestlePlayerState::SubScore(const uint16 Amount)
{
	if (HasAuthority())
	{
		PlayerPoints = FMath::Clamp(PlayerPoints - Amount, 0, UINT16_MAX);
		
		OnRep_PlayerPointsChanged();
	}
}

void AEverWrestlePlayerState::SetScore(const uint16 NewScore)
{
	if (HasAuthority())
	{
		PlayerPoints = NewScore;
		
		OnRep_PlayerPointsChanged();
	}
}