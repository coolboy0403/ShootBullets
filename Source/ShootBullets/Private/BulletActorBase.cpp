// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActorBase.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

const float ABulletActorBase::ArrowHalfLength = 40.0f;

// Sets default values
ABulletActorBase::ABulletActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InitialLifeSpan = 3.0f;
	ArrowScale = 1.0f;
	ArrowColor = FLinearColor::Red;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	if (nullptr == BoxComp)
		return;

	BoxComp->BodyInstance.SetCollisionProfileName(TEXT("Bullets"));
	BoxComp->OnComponentHit.AddDynamic(this, &ABulletActorBase::OnHit);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABulletActorBase::OnBeginOverlap);
	BoxComp->SetBoxExtent(FVector(ArrowHalfLength, 2.5f, 2.5f));
	RootComponent = BoxComp;

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrowComp"));
	if (nullptr == ArrowComp)
		return;

	ArrowComp->SetHiddenInGame(false);
	ArrowComp->SetRelativeLocation(FVector(ArrowHalfLength * -1, 0.0f, 0.0f));
	ArrowComp->SetupAttachment(BoxComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	if (nullptr == MovementComp)
		return;

	MovementComp->SetUpdatedComponent(BoxComp);
	MovementComp->InitialSpeed = 100.0f;
	MovementComp->MaxSpeed = 100.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bShouldBounce = true;
	MovementComp->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void ABulletActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	FVector Direction = FRotationMatrix(GetActorRotation()).GetUnitAxis(EAxis::X);
	SetActorLocation(GetActorLocation() + Direction * ArrowHalfLength * ArrowScale);

	if (nullptr == BoxComp)
		return;

	BoxComp->SetBoxExtent(FVector(ArrowHalfLength * ArrowScale, 2.5f * ArrowScale, 2.5f * ArrowScale));

	if (nullptr == ArrowComp)
		return;

	ArrowComp->SetRelativeScale3D(FVector(ArrowScale, ArrowScale, ArrowScale));
	ArrowComp->SetRelativeLocation(FVector(ArrowHalfLength * ArrowScale * -1, 0.0f, 0.0f));
	ArrowComp->SetArrowColor(ArrowColor);

	ChangeDirection(Direction);
}

void ABulletActorBase::ChangeDirection(const FVector& Direction)
{
	if (nullptr == MovementComp)
		return;

	MovementComp->Velocity = Direction * MovementComp->InitialSpeed;
}

void ABulletActorBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, __FUNCTIONW__);
	
	if (GetOwner() == OtherActor)
		return;
	
	OnCollisionDetected();
}

void ABulletActorBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, __FUNCTIONW__);

	if (GetOwner() == OtherActor)
		return;

	OnCollisionDetected();
}

void ABulletActorBase::OnCollisionDetected()
{
	Destroy();
}