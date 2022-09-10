// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class SHOOTINGCPP_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 충돌했을 때 폭발 VFX를 상대방 위치에 배치하고싶다.
	UPROPERTY(EditAnywhere, Category = VFX)
	class UParticleSystem* explosionFactory;

	// 태어날 때(BeginPlay) 방향을 앞방향으로 정하고싶다.
	// 살아가면서(Tick) 그 방향으로 이동하고싶다.
	FVector dir;
	float speed = 500;
	// (생성자)충돌을 담당할 boxComp, 외관을 담당할 meshComp
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;

	// 플레이어와 부딪히면 GameOverUI를 생성해서 보이게하고싶다.
	// 마우스 커서도 보이게 하고싶다.
	// InputMode를 UI모드로 하고싶다.

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameOverUI> gameOverUIFactory;
};
