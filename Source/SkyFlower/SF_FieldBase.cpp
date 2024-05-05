#include "SF_FieldBase.h"

ASF_FieldBase::ASF_FieldBase()
	: TriggerComponent(nullptr)
	, FieldEventType(ESF_FieldEventType::None)
	, BattleDataAsset(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}