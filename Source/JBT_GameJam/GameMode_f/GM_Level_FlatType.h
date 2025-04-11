// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Level_FlatType.generated.h"

/**
 * 
 */
UCLASS()
class JBT_GAMEJAM_API AGM_Level_FlatType : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Classes")
	TSubclassOf<APawn> CustomPawnClass;  // 用于指定蓝图Pawn

	UPROPERTY(EditDefaultsOnly, Category = "Classes")
	TSubclassOf<AHUD> CustomHUDClass;    // 用于指定蓝图HUD


public:
	AGM_Level_FlatType();

	virtual void BeginPlay() override;


	
};
