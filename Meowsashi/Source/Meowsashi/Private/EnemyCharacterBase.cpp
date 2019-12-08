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

}

// Called to bind functionality to input
void AEnemyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AEnemyCharacterBase::HandleOnPawnSeen(APawn* SeenPawn)
{
	//UE_LOG(LogTemp, Warning, TEXT("I SEE YOU: %s"), *SeenPawn->GetName());
}

void AEnemyCharacterBase::HandleOnHearNoise(APawn* HeardPawn, const FVector& Location, float Volume)
{
	UE_LOG(LogTemp, Warning, TEXT("I HEAR YOU"));

	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Red, false, 10.0f);
}
