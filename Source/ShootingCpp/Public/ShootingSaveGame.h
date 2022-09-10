// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ShootingSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UShootingSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	//저장소 그릇을 만들고싶다.
	UPROPERTY(EditAnywhere) // UPROPERTY는 필수!!!
	int highScoreSave;
};
