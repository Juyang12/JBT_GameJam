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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classes")
	TSubclassOf<APawn> CustomPawnClass;  // 用于指定蓝图Pawn

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classes")
	TSubclassOf<AHUD> CustomHUDClass;    // 用于指定蓝图HUD

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rules")
	int32 checkpointCount = 0; // 关卡检查点数量

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rules")
	TArray<bool> Array_checkpoint;

	FString LevelPathString = TEXT("/Content/Maps/TestLevel.umap");//主关卡

	int32 curCount = 0; // 当前check过的检查点数量

public:
	AGM_Level_FlatType();

	virtual void BeginPlay() override;

	void InitArray();
	
	UFUNCTION(BlueprintCallable, Category = "Rules")
	void goBackMainLevel();

	UFUNCTION(BlueprintImplementableEvent, Category = "Rules")
	void Success();

	UFUNCTION(BlueprintCallable, Category = "Rules")
	void upadteCheckpointCount(int32 count, bool check)
	{
		UE_LOG(LogTemp, Warning, TEXT("箱子"));
		UE_LOG(LogTemp, Warning, TEXT("%d"), checkpointCount);
		if (check)
		{
			if (curCount < checkpointCount-1)
			{
				//Array_checkpoint[count] = true; // 设置当前检查点为true
				UE_LOG(LogTemp, Warning, TEXT("%d"),curCount);
				curCount++;
			}
			else
			{
				//退回到主界面
				UE_LOG(LogTemp, Warning, TEXT("玩家推完了所有箱子"));
				Success();
			}
		}
		else//意味着这个箱子失去位置，检查点失效
		{
			if (curCount > 0)
			{
				//Array_checkpoint[count] = false; // 设置当前检查点为false
				curCount--;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No checkpoints to remove!"));
			}
		}
	}

	UFUNCTION(BlueprintCallable, Category = "Rules")
	void loseAndReset();

	TArray<UClass*> GetAllClassesWithInterface();
	
	UFUNCTION(BlueprintCallable, Category = "Rules")
	void ClearAllWD();
};
