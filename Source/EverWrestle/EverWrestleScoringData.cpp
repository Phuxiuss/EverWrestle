// EverWrestle - A Peak Entertainment Production (2026)


#include "EverWrestleScoringData.h"

int32 UEverWrestleScoringData::GetPointsForPlacement(uint8 Placement)
{
	return GetPointsOutOfMap(PlacementPointsMap, Placement);
}

int32 UEverWrestleScoringData::GetPointsForKnockout(uint8 Knockouts)
{
	return GetPointsOutOfMap(KnockoutPointsMap, Knockouts);
}

int32 UEverWrestleScoringData::GetPointsOutOfMap(TMap<uint8, int32> MapToCheck, uint8 Num) const
{
	Num = FMath::Clamp(Num, 1, MapToCheck.Num());
	
	if (const int32 FoundPoints = MapToCheck.FindRef(Num))
	{
		return FoundPoints;
	}
	else
	{
		return 0;
	}
}