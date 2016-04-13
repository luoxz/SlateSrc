// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CommonDef.generated.h"

//UEmpty只是为了引入引擎的类，比如FString
UCLASS()
class UEmpty : public UObject
{
	GENERATED_BODY()

public:
	UEmpty() {}
	virtual ~UEmpty() {}
};

#define  Split_Com		TEXT(",")
#define  Split_Line		TEXT("_")
#define  Split_Pound	TEXT("#")
#define  Split_Sem		TEXT(";")
