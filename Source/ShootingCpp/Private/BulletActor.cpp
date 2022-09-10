// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "EnemyActor.h"
#include <Kismet/GameplayStatics.h>
#include "ShootingGameModeBase.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	// 박스를 루트로
	SetRootComponent(boxComp);
	// 외관을 박스의 자식으로 하고싶다.
	meshComp->SetupAttachment(boxComp);

	boxComp->SetBoxExtent(FVector(37.5f, 12.5f, 50));
	meshComp->SetRelativeScale3D(FVector(0.75f, 0.25f, 1));

	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("Bullet"));

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABulletActor::OnBoxCompBeginOverlap);

	/*
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	// Ctrl + K + D 자동 들여쓰기
	// Ctrl + K + C 주석하기
	// Ctrl + K + U 주석풀기
//ECC_GameTraceChannel1: Player
//ECC_GameTraceChannel2 : Bullet
//ECC_GameTraceChannel3 : Enemy
//ECC_GameTraceChannel4 : DestroyZone

	boxComp->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);

	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	boxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECR_Overlap);
	boxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECR_Overlap);
	*/
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 1. 앞 방향을 만들고
	FVector dir = GetActorForwardVector();
	FVector p0 = GetActorLocation();
	// 2. 그 방향으로 이동하고싶다. (P = P0 + vt)
	SetActorLocation(p0 + dir * speed * DeltaTime);
}

void ABulletActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	//if (enemy != nullptr)
	//{
	//	// 너죽고
	//	enemy->Destroy();
	//}
	//
	//// 나죽자
	//Destroy();
}

void ABulletActor::OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	if (enemy != nullptr)
	{
		// 폭발 VFX를 만들어서 플레이어 위치에 배치하고싶다.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, enemy->GetActorLocation());
		// 너죽고
		enemy->Destroy();

		// 점수를 1점 증가시키고싶다.
		// 1. AShootingGameModeBase인스턴스를 가져오고싶다.
		auto gameMode = GetWorld()->GetAuthGameMode();
		auto realGameMode = Cast<AShootingGameModeBase>(gameMode);
		// 2. 그 녀석의 AddScore함수를 호출하고싶다.
		realGameMode->AddScore(1);
	}
	//if (OtherActor->IsA<AEnemyActor>())
	//{
	//}
	
	// 나죽자
	Destroy();
}

