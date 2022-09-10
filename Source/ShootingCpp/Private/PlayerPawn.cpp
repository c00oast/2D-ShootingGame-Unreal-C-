

#include "PlayerPawn.h"
#include <Components/BoxComponent.h>
#include <Components/ArrowComponent.h>
#include "BulletActor.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
APlayerPawn::APlayerPawn()
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체를 생성하고 루트컴포넌트로 설정하고싶다.
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);

	// 외관을 담당할 Static Mesh Component를 생성하고싶다.
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));

	// meshComp를 Root에 붙이고싶다.
	meshComp->SetupAttachment(RootComponent);

	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("firePosition"));

	firePosition->SetRelativeLocation(FVector(0, 0, 100));
	firePosition->SetRelativeRotation(FRotator(90, 0, 0));

	firePosition->SetupAttachment(RootComponent);

	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("Player"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), h);

	// 1. 사용자의 입력을 받고
	// 2. 그 입력값으로 방향을 만들고
	FVector dir = FVector(0, h, v);
	dir.Normalize(); // 벡터의 길이를 1로 만들고싶다.
	// 3. 그 방향으로 이동하고싶다.
	// P = P0 + vt;
	FVector P0 = GetActorLocation();
	FVector vt = dir * speed * DeltaTime;
	SetActorLocation(P0 + vt);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerPawn::OnAxisHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerPawn::OnAxisVertical);

	//PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerPawn::OnActionFire);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerPawn::OnActionFirePressed);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &APlayerPawn::OnActionFireReleased);
}

void APlayerPawn::OnAxisHorizontal(float value)
{
	h = value;
}

void APlayerPawn::OnAxisVertical(float value)
{
	v = value;
}

// 버튼이 눌러진 순간
void APlayerPawn::OnActionFire()
{
	// 총알공장에서 총알을 만들어서 총구위치에 배치하고싶다.
	// SpawnActor
	GetWorld()->SpawnActor<ABulletActor>(bulletFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation());

	// 총알소리를 출력하고싶다.
	UGameplayStatics::PlaySound2D(GetWorld(), soundFire);
}

void APlayerPawn::OnActionFirePressed()
{
	// 알람을 등록하고싶다.
	GetWorldTimerManager().SetTimer(timerHandleAutoFire, this, &APlayerPawn::OnActionFire, fireTime, true, 0);
}
void APlayerPawn::OnActionFireReleased()
{
	// 알람을 해제하고싶다.
	GetWorldTimerManager().ClearTimer(timerHandleAutoFire);
}

