// EverWrestle - A Peak Entertainment Production (2026)


#include "SessionPlayerState.h"

#include "EverWrestlePlayerState.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

void ASessionPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		if (const FUniqueNetIdRepl& NetId = GetUniqueId(); NetId.IsValid())
		{
			if (const IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld(), STEAM_SUBSYSTEM))
			{
				if (const IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface())
				{
					SetPlayerName(Identity->GetPlayerNickname(*NetId));
				}
			}
		}
	}
}

void ASessionPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);
	
	if (AEverWrestlePlayerState* TargetPS = Cast<AEverWrestlePlayerState>(PlayerState))
	{
		TargetPS->SetCharacter(this->CharacterType);
	}
}

void ASessionPlayerState::SetCharacter(const ECharacterType& NewCharacterType)
{
	CharacterType = NewCharacterType;
}