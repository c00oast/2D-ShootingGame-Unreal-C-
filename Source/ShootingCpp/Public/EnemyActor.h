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

	// �浹���� �� ���� VFX�� ���� ��ġ�� ��ġ�ϰ�ʹ�.
	UPROPERTY(EditAnywhere, Category = VFX)
	class UParticleSystem* explosionFactory;

	// �¾ ��(BeginPlay) ������ �չ������� ���ϰ�ʹ�.
	// ��ư��鼭(Tick) �� �������� �̵��ϰ�ʹ�.
	FVector dir;
	float speed = 500;
	// (������)�浹�� ����� boxComp, �ܰ��� ����� meshComp
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;

	// �÷��̾�� �ε����� GameOverUI�� �����ؼ� ���̰��ϰ�ʹ�.
	// ���콺 Ŀ���� ���̰� �ϰ�ʹ�.
	// InputMode�� UI���� �ϰ�ʹ�.

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameOverUI> gameOverUIFactory;
};
