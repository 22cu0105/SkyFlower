// ==================================================
// Filename	:	SF_DamageableInterface.h
// Author	:	22cu0214 JinWener
// Description: �_���[�W���󂯂���Actor�p�C���^�t�F�[�X
// Notes:		
//				
// Update:		2024/04/23 22cu0214 
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SF_DamageableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USF_DamageableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SKYFLOWER_API ISF_DamageableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void GetDamage(int32 damage) = 0;
};