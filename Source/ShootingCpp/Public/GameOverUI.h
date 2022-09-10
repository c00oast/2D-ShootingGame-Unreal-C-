// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UGameOverUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 연결된 버튼이 눌러졌을 때 호출할 함수를 등록하고싶다.
	virtual void NativeConstruct() override;

	// UI와 연결된 버튼 속성을 만들고싶다.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Restart;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Quit;

	UFUNCTION()
	void OnClickRestart();
	
	UFUNCTION()
	void OnClickQuit();
};
