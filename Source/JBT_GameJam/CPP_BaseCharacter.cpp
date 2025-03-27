// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BaseCharacter.h"

// Sets default values
ACPP_BaseCharacter::ACPP_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorComp = CreateDefaultSubobject<UC_CP_BaseComp>(TEXT("ActorComp"));

}

// Called when the game starts or when spawned
void ACPP_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	
}

// Called every frame
void ACPP_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext, 0);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(Move_Action, ETriggerEvent::Triggered, this, &ACPP_BaseCharacter::Move);
	Input->BindAction(StickBox_Action, ETriggerEvent::Triggered, this, &ACPP_BaseCharacter::OnStickBox);
	Input->BindAction(StickBox_Action,ETriggerEvent::Completed, this, &ACPP_BaseCharacter::OnLeaveBox);
}



