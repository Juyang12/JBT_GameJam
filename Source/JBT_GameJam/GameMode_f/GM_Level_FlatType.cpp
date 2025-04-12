// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Level_FlatType.h"
#include "GameFramework/DefaultPawn.h" // 默认Pawn
#include "GameFramework/PlayerController.h" // 默认PlayerController
#include "GameFramework/HUD.h" // 自定义HUD（可选）
#include "Kismet/GameplayStatics.h"//
#include"CPP_UIInterface.h"
#include "AssetRegistry/AssetRegistryModule.h"

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

    InitArray();

}

void AGM_Level_FlatType::InitArray()
{
    Array_checkpoint.Init(false, checkpointCount); // 初始化数组，大小为checkpointCount，初始值为false
}

void AGM_Level_FlatType::goBackMainLevel()
{
    ClearAllWD(); // 清除所有UI
    UGameplayStatics::OpenLevel(this, FName(*LevelPathString), true); // 返回主关卡
}

void AGM_Level_FlatType::loseAndReset()
{

    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);
}

TArray<UClass*> AGM_Level_FlatType::GetAllClassesWithInterface()
{
    TArray<UClass*> ClassesWithInterface;

    // 获取 AssetRegistry 模块
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

    // 搜索所有蓝图类
    TArray<FAssetData> BlueprintAssets;
    AssetRegistry.GetAssetsByClass(UBlueprint::StaticClass()->GetClassPathName(), BlueprintAssets);

    for (const FAssetData& AssetData : BlueprintAssets)
    {
        // 获取生成的类
        UBlueprint* Blueprint = Cast<UBlueprint>(AssetData.GetAsset());
        if (Blueprint && Blueprint->GeneratedClass)
        {
            UClass* BlueprintClass = Blueprint->GeneratedClass;

            // 检查是否实现了接口
            if (BlueprintClass->ImplementsInterface(UCPP_UIInterface::StaticClass()))
            {
                ClassesWithInterface.Add(BlueprintClass);
            }
        }
    }
    return TArray<UClass*>();
}

void AGM_Level_FlatType::ClearAllWD()
{
    TArray<UClass*> ClassesWithInterface = GetAllClassesWithInterface();

	for (UClass* Class : ClassesWithInterface)
	{
		// 获取所有实现了接口的对象
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Class, Actors);

		for (AActor* Actor : Actors)
		{
			ICPP_UIInterface* UIInterface = Cast<ICPP_UIInterface>(Actor);
			if (UIInterface)
			{
				UIInterface->FUNC_ClearAllWD();
			}
		}
	}
}


