// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreUI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UScoreUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* textBlockScoreTitle; // 현재점수 :

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* textBlockScore; // 0

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* textBlockHighScoreTitle; // 최고점수 :

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* textBlockHighScore; // 0
};
