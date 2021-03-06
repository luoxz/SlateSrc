#include "MySlate.h"
#include "BehavInter.h"

#include "./Effect/Effects/BehavElem.h"

UBehavInterface::UBehavInterface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

IBehavInterface::IBehavInterface()
{

}

void IBehavInterface::BehavTick(float DeltaSeconds)
{
	for (auto Iter = mBehavMap.CreateConstIterator(); Iter; ++Iter)
	{
		for (auto Iter2 = Iter->Value.CreateConstIterator(); Iter2; ++Iter2)
		{
			(*Iter2)->Tick(DeltaSeconds);
		}
	}
}

void IBehavInterface::AddBehavElem(int32 _groupId, TArray<UBehavElem*> _elemVec)
{
	TArray<UBehavElem*>* srcVec = mBehavMap.Find(_groupId);
	if (srcVec != nullptr)
	{
		srcVec->Append(_elemVec);
	}
	else
	{
		mBehavMap.Add(_groupId, _elemVec);
	}
}

void IBehavInterface::RemoveBehavElem(UBehavElem* _elem)
{
	int32 groupId = _elem->mGroupId;
	TArray<UBehavElem*>* srcVec = mBehavMap.Find(groupId);
	if (srcVec != nullptr)
	{
		srcVec->RemoveAll([&](const UBehavElem* behavElem)->bool {
			return behavElem == _elem;
		});

		if (srcVec->Num() == 0)
		{
			mBehavMap.Remove(groupId);
		}

		UE_LOG(SkillLogger, Warning, TEXT("--- IBehavInterface::RemoveBehavElem, map num:%d "), mBehavMap.Num());
	}
}

void IBehavInterface::RemoveBehavElemAll(int32 _groupId /* = 0 */)
{
	if (_groupId > 0)
	{
		TArray<UBehavElem*>* srcVec = mBehavMap.Find(_groupId);
		if (srcVec != nullptr)
		{
			for (UBehavElem* elem : *srcVec)
			{
				elem->MyDestroy(false);
			}
			mBehavMap.Remove(_groupId);
		}
	}
	else
	{
		for (auto Iter = mBehavMap.CreateConstIterator(); Iter; ++Iter)
		{
			for (UBehavElem* elem : Iter->Value)
			{
				elem->MyDestroy(false);
			}
		}
		mBehavMap.Empty();
	}
}