// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Level_FlatType.h"
#include "GameFramework/DefaultPawn.h" // 默认Pawn
#include "GameFramework/PlayerController.h" // 默认PlayerController
#include "GameFramework/HUD.h" // 自定义HUD（可选）

AGM_Level_FlatType::AGM_Level_FlatType()
{
    if (CustomPawnClass)
        DefaultPawnClass = CustomPawnClass;
    else
        DefaultPawnClass = ADefaultPawn::StaticClass(); // 默认回退

    if (CustomHUDClass)
        HUDClass = CustomHUDClass;
    else
        HUDClass = AHUD::StaticClass(); // 默认回退
}

void AGM_Level_FlatType::BeginPlay()
{
	Super::BeginPlay();

	
}
