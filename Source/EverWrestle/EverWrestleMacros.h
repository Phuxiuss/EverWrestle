// EverWrestle - A Peak Entertainment Production (2026)

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"

// Development | Debug
#define PRINT_STRING(text, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT(text), ##__VA_ARGS__));}