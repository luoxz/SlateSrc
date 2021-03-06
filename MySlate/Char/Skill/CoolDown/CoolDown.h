
#pragma once

#include "../SkillTypes.h"
#include "../../Object/ObjInter.h"
#include "CoolDown.generated.h"

class UCoolDown;
DECLARE_DELEGATE_OneParam(FCDFinishDlg, UCoolDown*);

class AMyChar;
class USkillTemplate;
class UCoolDownComp;
class USkillFunction;

UCLASS()
class UCoolDown : public UObject, public IObjInterface
{
	GENERATED_BODY()

public:
	UCoolDown();
	virtual ~UCoolDown();
	virtual void BeginDestroy() override; //调用ConditionalBeginDestroy();会立即调用，这个函数不允许外部调用
	virtual void Reset() override;
	virtual void Recycle() override;

public:
	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		bool		IsOK() const { return mIsOK; }
	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		float		GetCDTimer() const { return mCDTime; }
	void			SetCDTimer(float timer) { mCDTime = timer; }

	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		int32		GetSkillId() const { return mSkillId; }

	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		void		SetSkillTemplate(USkillTemplate* _skillTemp);

	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		USkillFunction*	GetSkillFunc();

	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		void		SetChar(AMyChar* _char);

	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		void		SetRatio(float _ratio) { mRatio = _ratio; }



	void			Restart();
	bool			IsNull() const { return mSkillId == 0 ? true : false; }

	virtual void Tick(float DeltaTime);

public:
	int32		mSkillId;
	float		mCDTime;//cd时间
	float		mTimer;//cd计时
	float		mRatio;//比例，用于加快cd
	bool		mIsOK;//

	USkillTemplate*		mSkillTemplate;
	USkillFunction*		mSkillFunc;
	AMyChar*			mOwnerChar;

	FCDFinishDlg				mCDFinishDlg;//通知代理
};