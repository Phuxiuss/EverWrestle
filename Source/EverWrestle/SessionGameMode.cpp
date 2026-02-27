#include "SessionGameMode.h"

#include "EverWrestleMapData.h"
#include "GameMapsSettings.h"

void ASessionGameMode::InitiateServerTravel()
{
	FString LevelName;
	if (MapData)
	{
		LevelName = MapData->GetRandomMapFromPool(this).GetLongPackageName();
	}
	else
	{
		if (const UGameMapsSettings* Settings = GetDefault<UGameMapsSettings>())
		{
			LevelName = Settings->GetGameDefaultMap();
		}
	}
	
	if (LevelName.IsEmpty())
	{
		ReturnToMainMenuHost();
		return;
	}
	
	FTimerHandle TravelTimerHandle;
	GetWorldTimerManager().SetTimer(TravelTimerHandle, [this, LevelName]()
	{
		GetWorld()->ServerTravel(LevelName);
	}, 1.f, false);
}
