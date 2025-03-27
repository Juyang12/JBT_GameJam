// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include"C_CP_BaseComp.h"

#include"Components/Inputcomponent.h"
#include"EnhancedInputComponent.h"
#include"EnhancedInputSubsystems.h"
#include"Engine/LocalPlayer.h"


#include "CPP_BaseCharacter.generated.h"

UCLASS()
class JBT_GAMEJAM_API ACPP_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|BasicComp")
	UC_CP_BaseComp* ActorComp;

	//处理玩家移动和推动箱子的输入
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* Move_Action;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* StickBox_Action;

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
	void Move();

	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void OnStickBox();

	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void OnLeaveBox();

};
