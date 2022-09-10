// Fill out your copyright notice in the Description page of Project Settings.


#include "CodingActor.h"

// Sets default values
ACodingActor::ACodingActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	number = 10;
	UE_LOG(LogTemp, Warning, TEXT("%d"), number);

	fNumber = 3.14f;
	UE_LOG(LogTemp, Warning, TEXT("%f"), fNumber);

	myName = TEXT("이영훈");
	UE_LOG(LogTemp, Warning, TEXT("%s"), *myName);

	bGood = false;
	UE_LOG(LogTemp, Warning, TEXT("%d"), bGood);


}

// Called when the game starts or when spawned
void ACodingActor::BeginPlay()
{
	Super::BeginPlay();

	// 조건문
	int32 money = 5000000;
	// 만약 돈이 300만원 이상 500만원이하 있다면
	// 논리연산자 && || !
	if (money >= 3000000 && money <= 5000000)
	{
		// 맥북을 사겠다.
		UE_LOG(LogTemp, Warning, TEXT("맥북을 사겠다."));
	}
	// 그렇지 않다면
	else
	{
		// 아이디어패드를 사겠다.
		UE_LOG(LogTemp, Warning, TEXT("아이디어패드를 사겠다."));
	}
	
	// 반복문
	for (int i = 0; i < 10 ; i++)
	{
		if (i % 2 == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("%d"), i);
		}
	}

	int value = Plus(10, 20);
	UE_LOG(LogTemp, Warning, TEXT("%d + %d = %d"), 10, 20, value);
}

// Called every frame
void ACodingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 함수의 정의(구현)
// int num1, int num2 : 매개변수
int ACodingActor::Plus(int num1, int num2)
{
	int result = num1 + num2;
	return result;
}

