#pragma once
#ifndef __TOWER_MANAGER_h__
#define __TOWER_MANAGER_h__

#include"TowerModel.h"
#include"TowerBase.h"
#include"TowerFactory.h"

class TowerManager
{
public:
    void addTower(TowerModel* model, cpoint pos);
    void addTower(shared_ptr<TowerBase> tower);
    void renderTowers(HDC hdc);

    void updateAllTower(std::vector<shared_ptr<EnemyBase>>& enemies_,float delta);
	std::vector<shared_ptr<TowerBase>> getAllTower() const;
	std::vector<shared_ptr<BulletBase>> getAllBullet() const;

private:
    std::vector<shared_ptr<TowerBase>> towers_;

};

#endif