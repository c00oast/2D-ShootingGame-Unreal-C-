// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodingActor.generated.h"

UCLASS()
class SHOOTINGCPP_API ACodingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
//	Edit / Visible
//  Anywhere / DefaultsOnly / InstanceOnly
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyVar)
	int32 number;

	float fNumber = 10.5f;
	FString myName;
	bool bGood;

public:
	// 함수 선언(Declare)
	//UFUNCTION(BlueprintPure)
	UFUNCTION(BlueprintCallable)
	int Plus(int num1, int num2); 
};
