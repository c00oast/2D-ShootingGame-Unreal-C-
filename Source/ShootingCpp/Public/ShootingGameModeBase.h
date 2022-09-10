// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API AShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AShootingGameModeBase();

	virtual void BeginPlay() override;
	// 점수처리를 하고싶다.'
	void AddScore(int amount);
	int score;
	int highScore;
	// 최고점수 처리를 하고싶다.
	// 현재점수가 최고점수를 초과하는 순간에 
	//  최고점수 = 현재점수

	// 태어날 때(BeginPlay) 점수UI공장에서 점수UI를 만들어서 보이게 하고싶다.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UScoreUI> scoreUIFactory;

	class UScoreUI* scoreUI;

	// highScore가 갱신될때 저장하기
	void GameSave();
	// 시작할 때(BeginPlay) 불러오기
	void GameLoad();
	// 저장할때 사용할 슬롯이름
	FString slotName = TEXT("ShootingGame");
};
