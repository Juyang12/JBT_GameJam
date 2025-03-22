// Fill out your copyright notice in the Description page of Project Settings.


#include "C_CP_BaseComp.h"

// Sets default values for this component's properties
UC_CP_BaseComp::UC_CP_BaseComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UC_CP_BaseComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UC_CP_BaseComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

