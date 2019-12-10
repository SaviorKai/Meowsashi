// All rights reserved © 2019 Ivan Carl Engelbrecht

#include "../Public/CatCharacter.h"
#include "Components/PawnNoiseEmitterComponent.h" // UPawnNoiseEmitterComponent


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

	MakeNoise(1.0f, this);

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
	AddMovementInput(GetActorForwardVector() * Amount);

	
}

void ACatCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector() * Amount);
	
	

}
