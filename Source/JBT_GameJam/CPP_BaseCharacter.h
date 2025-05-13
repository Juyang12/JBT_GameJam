// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include"C_CP_BaseComp.h"

#include"Components/Inputcomponent.h"
#include"EnhancedInputComponent.h"
#include"EnhancedInputSubsystems.h"
#include"Engine/LocalPlayer.h"

#include "Math/UnrealMathUtility.h"

#include "GameFramework/Character.h" // 角色基类
#include "GameFramework/PlayerController.h" // 玩家控制器
#include "Camera/CameraComponent.h" // 摄像机组件
#include "GameFramework/SpringArmComponent.h" // 弹簧臂组件（通常用于摄像机跟随）
#include "Kismet/GameplayStatics.h" 

#include "GameFramework/CharacterMovementComponent.h"//移动组件类

#include "CPP_BaseCharacter.generated.h"

UCLASS()
class JBT_GAMEJAM_API ACPP_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|BasicComp")
	UC_CP_BaseComp* ActorComp;

	//处理玩家移动和推动箱子的输入
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* Move_Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* StickBox_Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* Rotation_Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* RightMouse_Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float RotationSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bIsRotating = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* Camera;


public:
	// Sets default values for this character's properties
	ACPP_BaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void Move(const FInputActionValue& inputVector);

	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void OnStickBox(const FInputActionValue& bIsStick);

	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void OnLeaveBox(const FInputActionValue& bIsStick);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void RotateView(const FInputActionValue& rotateVector);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void RightButtonTriggered(const FInputActionValue& rotateVector);


private:
	

	bool bShouldResetCamera = false;

};
