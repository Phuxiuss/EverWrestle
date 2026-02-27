// EverWrestle - A Peak Entertainment Production (2025)


#include "EverWrestleTaskZone.h"

#include "Kismet/KismetMathLibrary.h"

void AEverWrestleTaskZone::UpdateProgressTimer()
{
	FTimerManager& TimerManager = GetWorldTimerManager();
	
	if (TimerManager.IsTimerActive(SkipTimerHandle))
	{
		TimerManager.ClearTimer(SkipTimerHandle);
	}
	
	TimerManager.SetTimer(SkipTimerHandle, this, &AEverWrestleTaskZone::OnSkipTimerSecondOver, MaxTimeForSkip);
}

void AEverWrestleTaskZone::OnSkipTimerSecondOver()
{
	if (CurrentSkipTime < MaxTimeForSkip)
	{
		CurrentSkipTime++;
		float ProgressBarPercentage = UKismetMathLibrary::NormalizeToRange(CurrentSkipTime, 0, MaxTimeForSkip);
		ProgressBarPercentage = FMath::Clamp(ProgressBarPercentage, 0.f, 1.f);
	}
}
