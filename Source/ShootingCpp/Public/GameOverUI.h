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
	// ����� ��ư�� �������� �� ȣ���� �Լ��� ����ϰ�ʹ�.
	virtual void NativeConstruct() override;

	// UI�� ����� ��ư �Ӽ��� �����ʹ�.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Restart;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Quit;

	UFUNCTION()
	void OnClickRestart();
	
	UFUNCTION()
	void OnClickQuit();
};
