// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUI.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

void UGameOverUI::NativeConstruct()
{
	Button_Restart->OnClicked.AddDynamic(this, &UGameOverUI::OnClickRestart);
	Button_Quit->OnClicked.AddDynamic(this, &UGameOverUI::OnClickQuit);
}

void UGameOverUI::OnClickRestart()
{
	FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), FName(*levelName));
}

void UGameOverUI::OnClickQuit()
{
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit,
		true
	);
}
