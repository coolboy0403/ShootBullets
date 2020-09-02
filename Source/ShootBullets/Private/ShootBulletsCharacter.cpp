// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootBulletsCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AShootBulletsCharacter::AShootBulletsCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AShootBulletsCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShootBulletsCharacter::MoveRight);

	PlayerInputComponent->BindAction("FireDefault", IE_Pressed, this, &AShootBulletsCharacter::FireDefaultPressed);
	PlayerInputComponent->BindAction("FireDefault", IE_Released, this, &AShootBulletsCharacter::FireDefaultReleased);
	PlayerInputComponent->BindAction("FireSpecial", IE_Released, this, &AShootBulletsCharacter::FireSpecialReleased);
}

void AShootBulletsCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AShootBulletsCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (m_bFireDefaultPressed)
	{
		m_fFireDefaultPressTime += DeltaSeconds;
		m_fFireDefaultPressTime = FMath::Min(m_fFireDefaultPressTime, 3.0f);
	}
}

void AShootBulletsCharacter::FireDefaultPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), __FUNCTIONW__);
	
	m_bFireDefaultPressed = true;
}

void AShootBulletsCharacter::FireDefaultReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("%s : %.2f"), __FUNCTIONW__, m_fFireDefaultPressTime);
	ResetFireStates();
}

void AShootBulletsCharacter::FireSpecialReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), __FUNCTIONW__);
	ResetFireStates();
}

void AShootBulletsCharacter::ResetFireStates()
{
	m_bFireDefaultPressed = false;
	m_fFireDefaultPressTime = 0.0f;
}