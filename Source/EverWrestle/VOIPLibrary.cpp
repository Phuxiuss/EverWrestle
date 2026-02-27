// EverWrestle - A Peak Entertainment Production (2026)


#include "VOIPLibrary.h"

#include "AdvancedFriendsInterface.h"
#include "EverWrestleMacros.h"
#include "OnlineSubsystem.h"

void UVOIPLibrary::ClearVoicePackets(UObject* WorldContextObject)
{
	UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World))
	{
		return;
	}
	
	IOnlineVoicePtr VoiceInterface = Online::GetVoiceInterface(World);
	if (!VoiceInterface.IsValid())
	{
		PRINT_STRING("Couldn't find the Voice Interface.");
		return;
	}
	
	VoiceInterface->ClearVoicePackets();
}
