// All rights reserved © 2019 Ivan Carl Engelbrecht


#include "../Public/EnemyCharacterBase.h"
#include "Perception/PawnSensingComponent.h" //UPawnSensingComponent
#include "DrawDebugHelpers.h"


// Sets default values
AEnemyCharacterBase::AEnemyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	/// Pawn Sensing
	SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));   ///Note: this doesn't need to be attached to anything.
	SensingComponent->OnSeePawn.AddDynamic(this, &AEnemyCharacterBase::HandleOnPawnSeen);
	SensingComponent->OnHearNoise.AddDynamic(this, &AEnemyCharacterBase::HandleOnHearNoise);
}

// Called when the game starts or when spawned
void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bHasTargetInSight) { return; }

	MoveToTarget();
	
	

}

// Called to bind functionality to input
void AEnemyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AEnemyCharacterBase::HandleOnPawnSeen(APawn* SeenPawn)
{
	auto SeenPawnLocation = SeenPawn->GetActorLocation();

	// Rotate Character to Noise Location
	auto NoiseLocation = SeenPawnLocation - GetActorLocation();
	auto NoiseDirection = NoiseLocation.Rotation();
	auto TargetRotation = FRotator(GetActorRotation().Pitch, NoiseDirection.Yaw, GetActorRotation().Roll); // THis keeps the current actor Pitch and Roll, and only replaced the yaw with the new value.
	//SetActorRotation(TargetRotation);

	/// Set the bool for vision to disable movement.
	bHasTargetInSight = true;
	MyTarget = SeenPawn;
	
	/*
	/// DEBUG ///
	UE_LOG(LogTemp, Warning, TEXT("I SEE YOU: %s"), *SeenPawn->GetName());
	DrawDebugSphere(GetWorld(), SeenPawnLocation, 32.0f, 12, FColor::Green, false, 10.0f);
	*/
}

void AEnemyCharacterBase::HandleOnHearNoise(APawn* HeardPawn, const FVector& Location, float Volume)
{
	// Rotate Character to Noise Location
	auto NoiseLocation = Location - GetActorLocation();
	auto NoiseDirection = NoiseLocation.Rotation();
	auto TargetRotation = FRotator(GetActorRotation().Pitch, NoiseDirection.Yaw, GetActorRotation().Roll); // THis keeps the current actor Pitch and Roll, and only replaced the yaw with the new value.
	SetActorRotation(TargetRotation);
		

	/// Set the bool for vision to disable movement.
	bHasTargetInSight = false;
	MyTarget = nullptr;

	/*
	/// DEBUG ///
	UE_LOG(LogTemp, Warning, TEXT("I HEAR YOU"));
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Red, false, 10.0f);
	*/
}


void AEnemyCharacterBase::MoveToTarget()
{
	if (!MyTarget) { return; } 

	if (GetDistanceTo(MyTarget) > AttackRange)
	{
		AddMovementInput(GetActorForwardVector() * MovementSpeed);
	}

	auto TargetLocation = MyTarget->GetActorLocation() - GetActorLocation();
	auto TargetRotation = TargetLocation.Rotation();

	SetActorRotation(FMath::Lerp(GetActorRotation(), TargetRotation, 1.0f));
}
