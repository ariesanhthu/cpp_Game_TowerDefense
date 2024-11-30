#pragma once
#ifndef __TOWER_MANAGER_h__
#define __TOWER_MANAGER_h__

#include"TowerModel.h"
#include"TowerBase.h"

class TowerManager
{
public:
    void addTower(TowerModel* model, cpoint pos);
    void addTower(TowerBase tower);
    void renderTowers();

    void updateAllTower(std::vector<EnemyBase> &enemies_, std::vector<BulletBase>& bulllets_);

private:
    std::vector<TowerBase> towers_;

};

#endif