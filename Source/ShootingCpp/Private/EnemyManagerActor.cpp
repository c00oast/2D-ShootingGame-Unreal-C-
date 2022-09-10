// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerActor.h"
#include <Components/ArrowComponent.h>
#include "EnemyActor.h"

// Sets default values
AEnemyManagerActor::AEnemyManagerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	arrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("arrowComp"));
	arrowComp->SetRelativeRotation(FRotator(-90, 0, 180));
	arrowComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyManagerActor::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle timerHanleMakeEnemy;
	GetWorldTimerManager().SetTimer(timerHanleMakeEnemy, this, &AEnemyManagerActor::MakeEnemy, makeTime, true);
}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	// 1. 시간이 흐르다가(현재시간에 DeltaTime을 누적하다가)
	currentTime += DeltaTime;
	// 2. 만약 현재시간 > 생성시간 라면
	if (currentTime > makeTime)
	{
		// 3. MekeEnemy함수를 호출하고싶다.
		MakeEnemy();
		// 4. 현재시간을 0으로 초기화 하고싶다.
		currentTime = 0;
	}
	*/
}

void AEnemyManagerActor::MakeEnemy()
{
	// 만약 플레이어가 존재하지 않는다면 함수를 바로 종료하고싶다.
	if (nullptr == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		return;
	}
	// 적공장에서 적을 만들어서 arrowComp에 배치하고싶다.
	GetWorld()->SpawnActor<AEnemyActor>(enemyFactory, arrowComp->GetComponentTransform());
}

