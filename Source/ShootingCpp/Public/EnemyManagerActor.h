// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManagerActor.generated.h"

UCLASS()
class SHOOTINGCPP_API AEnemyManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//1. 시간이 흐르다가
	//2. 만약 현재시간이 생성시간을 초과하면
	//3. 적공장에서 적을 생성해서 화살표 위치에 배치하고싶다.
	//4. 현재시간을 0으로 초기화 하고싶다.
	// 필요 속성
	// - 화살표
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* arrowComp;
	// - 적 공장
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyActor> enemyFactory;
	// - 현재시간
	float currentTime;
	// - 생성시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float makeTime = 1;

	void MakeEnemy();
};
