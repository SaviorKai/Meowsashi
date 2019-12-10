// All rights reserved © 2019 Ivan Carl Engelbrecht

#include "../Public/CatCharacter.h"
#include "Components/PawnNoiseEmitterComponent.h" // UPawnNoiseEmitterComponent
#include "Components/InputComponent.h" //GetAxisValue()
#include "Components/SkeletalMeshComponent.h"   // USkeletalMeshComponent
#include "Components/PrimitiveComponent.h"    // UPrimitiveComponent


// Sets default values
ACatCharacter::ACatCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Noise Emitter
	NoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitterComp"));

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
