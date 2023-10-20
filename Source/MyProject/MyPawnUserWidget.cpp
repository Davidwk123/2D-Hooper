// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnUserWidget.h"
#include "Components/TextBlock.h"

// The "if" and "define" allows the use of the "LOCTEXT" in the function
#if WITH_EDITOR
#define LOCTEXT_NAMESPACE "UMG"
void UMyPawnUserWidget::SetLives(int PawnLives)
{
	if (Lives)
	{
		Lives->SetText(FText::Format(LOCTEXT("CombinedTextKey", "Lives: {0}"), PawnLives));
	}
}
void UMyPawnUserWidget::SetScore(int PawnScore)
{

}
#undef LOCTEXT_NAMESPACE
#endif