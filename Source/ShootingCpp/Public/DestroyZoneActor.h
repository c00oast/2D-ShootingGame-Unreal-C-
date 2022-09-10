// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyZoneActor.generated.h"

UCLASS()
class SHOOTINGCPP_API ADestroyZoneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyZoneActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 충돌체 만들고 충돌 Preset설정하고싶다.
	// 상대방과 충돌시 상대를 파괴하고싶다.
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
