// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameModeBase.h"
#include <Blueprint/UserWidget.h>
#include "ScoreUI.h"
#include <Components/TextBlock.h>
#include "Kismet/GameplayStatics.h"
#include "ShootingSaveGame.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

AShootingGameModeBase::AShootingGameModeBase()
{
	score = 0;
}

void AShootingGameModeBase::BeginPlay()
{
	// 태어날 때(BeginPlay) 점수UI공장에서 점수UI를 만들어서 보이게 하고싶다.
	auto ui = CreateWidget(GetWorld(), scoreUIFactory);
	scoreUI = Cast<UScoreUI>(ui);
	if (nullptr != scoreUI)
	{
		scoreUI->AddToViewport();

		GameLoad();

		// 태어날 때 최고점수를 UI에 출력하고싶다.
		scoreUI->textBlockHighScore->SetText(FText::AsNumber(highScore));
	}

	// 마우스 커서도 보이게 하고싶다.
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	// InputMode를 UI모드로 하고싶다.
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());

}

void AShootingGameModeBase::AddScore(int amount)
{
	// score에 amount를 누적하고싶다.
	score += amount;

	// 최고점수 처리를 하고싶다.
	// 현재점수가 바뀌는 순간에
	// 만약 현재점수가 최고점수를 초과하면
	if (score > highScore)
	{
		//  최고점수 = 현재점수
		highScore = score;
		scoreUI->textBlockHighScore->SetText(FText::AsNumber(highScore));
		UE_LOG(LogTemp, Warning, TEXT("highScore : %d"), highScore);
		GameSave();
	}

	// 점수를 UI로 표현하고싶다.
	scoreUI->textBlockScore->SetText(FText::AsNumber(score));
	UE_LOG(LogTemp, Warning, TEXT("score : %d"), score);
}

void AShootingGameModeBase::GameSave()
{
	// 저장할 SaveGame인스턴스 만들기
	auto saveInstance =
		Cast<UShootingSaveGame>(UGameplayStatics::CreateSaveGameObject(UShootingSaveGame::StaticClass()));
	// 인스턴스에 값을 대입하기
	saveInstance->highScoreSave = highScore;
	// 파일에 쓰기(슬롯에 인스턴스 넘겨줘서 저장하기)
	UGameplayStatics::SaveGameToSlot(saveInstance, slotName, 0);
}

void AShootingGameModeBase::GameLoad()
{
	// 슬롯을 읽어서  SaveGame을 가져오고싶다.
	auto inst = UGameplayStatics::LoadGameFromSlot(slotName, 0);
	if (nullptr == inst)
	{
		// 저장된 슬롯이 없다.
		highScore = 0;
		return;
	}
	auto saveInstance = Cast<UShootingSaveGame>(inst);
	// saveInstance안의 변수인 highScoreSave를 가져와서 highScore에 대입하고싶다.
	highScore = saveInstance->highScoreSave;

}
