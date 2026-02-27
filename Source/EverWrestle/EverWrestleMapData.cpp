// EverWrestle - A Peak Entertainment Production (2026)


#include "EverWrestleMapData.h"

#include "GameMapsSettings.h"

TSoftObjectPtr<UWorld> UEverWrestleMapData::GetRandomMapFromPool(const UObject* WorldContextObject) const
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World) return TSoftObjectPtr<UWorld>();
	
	FString LevelName;
	
	if (MapRotationPool.Num() == 0)
	{
		if (const UGameMapsSettings* Settings = GetDefault<UGameMapsSettings>())
		{
			LevelName = Settings->GetGameDefaultMap();
		}
	}
	else
	{
		TArray<TSoftObjectPtr<UWorld>> PossibleLevels = MapRotationPool;
		
		FString CurrentLevelName = World->GetMapName();
		CurrentLevelName.RemoveFromStart(World->StreamingLevelsPrefix);
		
		FString ShortCurrentMapName = FPackageName::GetShortName(CurrentLevelName);
		
		PossibleLevels.RemoveAll([&ShortCurrentMapName](const TSoftObjectPtr<UWorld>& LevelPtr)
		{
			return LevelPtr.GetAssetName() == ShortCurrentMapName;
		});
		
		if (PossibleLevels.Num() > 0)
		{
			int32 RandIndex = FMath::RandRange(0, PossibleLevels.Num() - 1);
			LevelName = PossibleLevels[RandIndex].GetLongPackageName();
		}
		else
		{
			LevelName = MapRotationPool[0].GetLongPackageName();
		}
	}
	
	return TSoftObjectPtr<UWorld>(FSoftObjectPath(LevelName));
}
