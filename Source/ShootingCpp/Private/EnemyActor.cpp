// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "PlayerPawn.h"
#include "GameOverUI.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

// Sets default values
AEnemyActor::AEnemyActor()
{
	PrimaryActorTick.bCanEverTick = true;
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(boxComp);

	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("Enemy"));

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnBoxCompBeginOverlap);
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	// 태어날 때(BeginPlay) 방향을 정하고싶다.
	// 30% 확률로 플레이어방향
	// 나머지 확률로 앞방향으로 정하고싶다.
	int randValue = FMath::RandRange(0, 9);
	if (randValue < 3) { // 30%
		// 방향 = 타겟 - 나
		auto target = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (nullptr == target) {
			dir = GetActorForwardVector();
		}
		else {
			FVector targetLoc = target->GetActorLocation();

			dir = targetLoc - GetActorLocation();
			dir.Normalize();
		}
	}
	else { // 70%
		dir = GetActorForwardVector();
	}
	// Ctrl + K + C // 주석하기
	// Ctrl + K + U // 주석풀기
	SetActorRotation(UKismetMathLibrary::MakeRotFromXZ(dir, GetActorUpVector()));

}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 살아가면서(Tick) 그 방향으로 이동하고싶다.
	// P = P0 + v(velocity : dir * speed) * t(순간의시간)
	SetActorLocation(GetActorLocation() + dir * speed * DeltaTime);
}

void AEnemyActor::OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 부딪힌 상대가 플레이어라면
	auto player = Cast<APlayerPawn>(OtherActor);
	if (player != nullptr)
	{
		// 폭발 VFX를 만들어서 플레이어 위치에 배치하고싶다.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, player->GetActorLocation());

		// 너죽고
		player->Destroy();

		// GameOverUI를 생성해서 보이게하고싶다.
		auto ui = CreateWidget(GetWorld(), gameOverUIFactory);
		if (ui)
		{
			ui->AddToViewport();
		}
		// 마우스 커서도 보이게 하고싶다.
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		// InputMode를 UI모드로 하고싶다.
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController());
	}
	// 나죽자
	Destroy();
}

