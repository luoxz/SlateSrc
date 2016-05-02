
#pragma once

#include "../../Common/ISingleton.h"

#include "ResMgr.generated.h"

struct FStreamableManager;
class UResDataBase;

UCLASS()
class UResMgr : public UObject, public USingleton<UResMgr>
{
	GENERATED_BODY()

public:
	UResMgr();
	virtual ~UResMgr();
	virtual void BeginDestroy() override;

public:
	UFUNCTION(BlueprintCallable, Category = "UResMgr")
		void TestAsyncLoad();
	void AsyncCallback();


	UFUNCTION(BlueprintCallable, Category = "UResMgr")
		void TestloadCSV();

	FStreamableManager*		GetAssetLoader() const { return mAssetLoader; }
	UParticleSystem*		GetParticle(int32 _id);

private:
	FStreamableManager*		mAssetLoader;
	UResDataBase*			mResDB;

	//TMap<int32, UBehaviorData*>		mBehaviorDataMap;//存放技能数据
};
