#include "LobbyCreationWidget.h"

#include "Components/EditableTextBox.h"

void ULobbyCreationWidget::CheckForNameLength(const FText& ChangedText, const uint8 MaxLength,
                                              UEditableTextBox* InputFieldToCheck)
{
	if (!InputFieldToCheck) return;
	
	FString CleanedText = ChangedText.ToString();
	
	CleanedText.ReplaceInline(TEXT("ä"), TEXT("ae"));
	CleanedText.ReplaceInline(TEXT("ö"), TEXT("oe"));
	CleanedText.ReplaceInline(TEXT("ü"), TEXT("ue"));
	
	if (CleanedText.Len() > MaxLength)
		CleanedText = CleanedText.Left(MaxLength);
	
	if (!ChangedText.EqualTo(FText::FromString(CleanedText)))
		InputFieldToCheck->SetText(FText::FromString(CleanedText));
}
