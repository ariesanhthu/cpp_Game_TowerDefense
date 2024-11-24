#pragma once
#ifndef __ENEMY_SMALL_h__
#define __ENEMY_SMALL_h__

#include "Enemy/EnemyBase.h"

class Small : public EnemyBase
{
public:
	Small(EnemyModel* nModel, int path);
	Small(const Small& other);
};

#endif