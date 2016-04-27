// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "BufflTemplate.h"

#include "../Utils/CommonDef.h"
#include "../Function/Funcs/AbsPkEvent.h"
#include "../Function/FuncFactory.h"

UBufflTemplate::UBufflTemplate() : Super()
{
		mId = 0;
		mName = "";
		mDescr = "";
		mBuffTime = 0;
		mCanDisperse = false;
		mCanAdd = false;

		mAttrsStr = "";
		mBeforePkStr = "";
		mEndPkStr = "";
}

UBufflTemplate::~UBufflTemplate()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- UBufflTemplate::~UBufflTemplate"));
}

void UBufflTemplate::BeginDestroy()
{


	UE_LOG(SkillLogger, Warning, TEXT("--- UBufflTemplate::BeginDestroy"));
	Super::BeginDestroy();
}

const TArray<UAbsPkEvent*>& UBufflTemplate::GetAttrs()
{
	if (mAttrs.Num() == 0 && mAttrsStr.Len() > 0)
	{
		ParseFuncStr(mAttrsStr, mAttrs);
	}
	return mAttrs;
}

const TArray<UAbsPkEvent*>& UBufflTemplate::GetBeforePk()
{
	if (mBeforePk.Num() == 0 && mBeforePkStr.Len() > 0)
	{
		ParseFuncStr(mBeforePkStr, mBeforePk);
	}
	return mBeforePk;
}

const TArray<UAbsPkEvent*>& UBufflTemplate::GetEndPk()
{
	if (mEndPk.Num() == 0 && mEndPkStr.Len() > 0)
	{
		ParseFuncStr(mEndPkStr, mEndPk);
	}
	return mEndPk;
}

void UBufflTemplate::ParseFuncStr(const FString& _funcStr, TArray<UAbsPkEvent*>& _funcArr)
{
	FString paramStr = _funcStr.ToLower();
	TArray<FString> params;
	paramStr.ParseIntoArray(params, Split_Line, true);
	for (TArray<FString>::TConstIterator iter = params.CreateConstIterator(); iter; ++iter)
	{
		UAbsPkEvent* func = UFuncFactory::GetInstance()->createFunction(*iter);
		if (func != nullptr)
		{
			func->AddToRoot();
			_funcArr.Add(func);
		}
	}
}

