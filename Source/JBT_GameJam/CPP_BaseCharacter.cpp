// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BaseCharacter.h"

// Sets default values
ACPP_BaseCharacter::ACPP_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorComp = CreateDefaultSubobject<UC_CP_BaseComp>(TEXT("ActorComp"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);


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

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), bShouldResetCamera));

	if (bShouldResetCamera)
	{
		FRotator CurrentRot = Camera->GetRelativeRotation();
		FRotator TargetRot = FRotator::ZeroRotator;
		FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, 10.0f);
		Camera->SetRelativeRotation(NewRot);

		// 检查是否完成
		if (NewRot.Equals(TargetRot, 2.0f))
		{
			Camera->SetRelativeRotation(TargetRot);
			bShouldResetCamera = false;
		}
	}

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
	Input->BindAction(Rotation_Action, ETriggerEvent::Triggered, this, &ACPP_BaseCharacter::RotateView);
	Input->BindAction(RightMouse_Action, ETriggerEvent::Started, this, &ACPP_BaseCharacter::RightButtonTriggered);
	Input->BindAction(RightMouse_Action, ETriggerEvent::Completed, this, &ACPP_BaseCharacter::RightButtonTriggered);

}

void ACPP_BaseCharacter::RotateView(const FInputActionValue& rotateVector)
{
	if(!bIsRotating)
	{
		return;
	}

	float x = (rotateVector.Get<float>()+1.0f)/2.0f;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), x));
	if(x==0.5f)
	{
		return;
	}
	FRotator rot = Camera->GetRelativeTransform().Rotator();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f,%f,%f"), rot.Roll,rot.Pitch,rot.Yaw));
	rot.Yaw = FMath::Clamp(rot.Yaw + x*RotationSpeed* GetWorld()->GetDeltaSeconds(), -90.0f, 90.0f);
	Camera->SetRelativeRotation(rot);
}

void ACPP_BaseCharacter::RightButtonTriggered(const FInputActionValue& rotateVector)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), &bIsRotating));
	bIsRotating = (!bIsRotating)?true:false;
	bShouldResetCamera = !bIsRotating;
}



