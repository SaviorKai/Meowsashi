// All rights reserved © 2019 Ivan Carl Engelbrecht

#include "../Public/CatCharacter.h"
#include "Components/PawnNoiseEmitterComponent.h" // UPawnNoiseEmitterComponent
#include "Components/InputComponent.h" //GetAxisValue()
#include "Components/SkeletalMeshComponent.h"   // USkeletalMeshComponent
#include "Components/PrimitiveComponent.h"    // UPrimitiveComponent
#include "Components/CapsuleComponent.h" // UCapsuleComponent


// Sets default values
ACatCharacter::ACatCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Noise Emitter
	NoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitterComp"));

	//Create Damage Collision Component
	
	DamageCapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DamageCollision_Comp"));
	if (GetMesh())
	{
		DamageCapsuleCollision->SetupAttachment(GetMesh());
	}
	DamageCapsuleCollision->SetCapsuleHalfHeight(62.0f);
	DamageCapsuleCollision->SetCapsuleRadius(5.0f);
	DamageCapsuleCollision->AttachTo(GetMesh(), FName("FX_Staff_Mid"));
	DamageCapsuleCollision->SetRelativeLocation(FVector(51, 0, 0));
	DamageCapsuleCollision->SetRelativeRotation(FRotator(90, 0, 0));
	DamageCapsuleCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	//DamageCollision->SetCollisionResponseToChannel(ECC_Team2, ECR_Overlap); // TODO: Need to figure out how to set this up in C++
	DamageCapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	

}

// Called when the game starts or when spawned
void ACatCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/// Setup the movement bindings and the functions to call (remember, don't use () when referencing '&' a function)
	PlayerInputComponent->BindAxis("MoveVertical", this, &ACatCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &ACatCharacter::MoveRight);
	
}

void ACatCharacter::MoveForward(float Amount)
{
	// Move the character (Forwards and backwards)
	AddMovementInput(GetActorForwardVector() * Amount);

	RotateCharacter();
	
	MakeNoise(1.0f, this);
}



void ACatCharacter::MoveRight(float Amount)
{
	// Move the character (Right and Left)
	AddMovementInput(GetActorRightVector() * Amount);
	
	RotateCharacter();
	
	MakeNoise(1.0f, this);
}

// Rotate the character to direction
void ACatCharacter::RotateCharacter() 
{
	/// Get the Input Axis Values
	auto MyPlayerInputComponent = FindComponentByClass<UInputComponent>();
	auto VertMoveAmount = MyPlayerInputComponent->GetAxisValue("MoveVertical");
	auto HoriMoveAmount = MyPlayerInputComponent->GetAxisValue("MoveHorizontal");

	/// Calculate the new direction rotation
	auto MovementDirection = FVector(HoriMoveAmount, -VertMoveAmount, 0).Rotation();

	/// Rotate the character
	auto MyMesh = FindComponentByClass<USkeletalMeshComponent>();
	Cast<UPrimitiveComponent>(MyMesh)->SetRelativeRotation(MovementDirection);
}


void ACatCharacter::DamageSwingOn()
{
	UE_LOG(LogTemp, Warning, TEXT("DamageSwingOn()"));

	DamageCapsuleCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ACatCharacter::DamageSwingOff()
{
	UE_LOG(LogTemp, Warning, TEXT("DamageSwingOff()"));
	DamageCapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACatCharacter::DealDamage()
{
	UE_LOG(LogTemp, Warning, TEXT("DEALING DAMAGE()"));
}
