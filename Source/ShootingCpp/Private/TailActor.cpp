// Fill out your copyright notice in the Description page of Project Settings.


#include "TailActor.h"
#include <Components/StaticMeshComponent.h>

// Sets default values
ATailActor::ATailActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 외관을 담당할 StaticMeshComponent를 생성하고싶다.
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));

	meshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATailActor::BeginPlay()
{
	Super::BeginPlay();
	// 시작할 때
	// 1. 만약 target이 nullptr이라면
	if (target == nullptr)
	{
		// 2. target = 플레이어를 찾아서 
		target = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
}

// Called every frame
void ATailActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	// 살아가면서 
	// 1. 타겟을 향하는 방향을 구하고싶다.
	FVector dir = target->GetActorLocation() - GetActorLocation();
	// 이슈! dir의 크기는 두 물체간의 거리이기 때문에 크기를 1로 만들고싶다.
	dir.Normalize();
	// 2. 그 방향으로 이동하고싶다. P = P0 + v(dir * speed)t
	FVector vt = dir * speed * DeltaTime;
	SetActorLocation(GetActorLocation() + vt);

}

