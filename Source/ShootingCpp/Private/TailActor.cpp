// Fill out your copyright notice in the Description page of Project Settings.


#include "TailActor.h"
#include <Components/StaticMeshComponent.h>

// Sets default values
ATailActor::ATailActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ܰ��� ����� StaticMeshComponent�� �����ϰ�ʹ�.
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));

	meshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATailActor::BeginPlay()
{
	Super::BeginPlay();
	// ������ ��
	// 1. ���� target�� nullptr�̶��
	if (target == nullptr)
	{
		// 2. target = �÷��̾ ã�Ƽ� 
		target = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
}

// Called every frame
void ATailActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	// ��ư��鼭 
	// 1. Ÿ���� ���ϴ� ������ ���ϰ�ʹ�.
	FVector dir = target->GetActorLocation() - GetActorLocation();
	// �̽�! dir�� ũ��� �� ��ü���� �Ÿ��̱� ������ ũ�⸦ 1�� �����ʹ�.
	dir.Normalize();
	// 2. �� �������� �̵��ϰ�ʹ�. P = P0 + v(dir * speed)t
	FVector vt = dir * speed * DeltaTime;
	SetActorLocation(GetActorLocation() + vt);

}

