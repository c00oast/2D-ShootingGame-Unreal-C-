// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TailActor.generated.h"

UCLASS()
class SHOOTINGCPP_API ATailActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATailActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	// 외관을 담당할 StaticMeshComponent를 선언하고싶다.
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;
	// 시작할 때 만약 target이 nullptr이라면 플레이어를 찾아서 target에 대입하고싶다.
	// 살아가면서 타겟을 향해 이동하고싶다. P = P0 + vt
	// 필요속성
	// - 타겟
	UPROPERTY(EditAnywhere)
	AActor* target = nullptr;
	// - 속력
	UPROPERTY(EditAnywhere)
	float speed;
};
