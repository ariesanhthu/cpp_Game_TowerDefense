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
    void renderTowers();

    void updateAllTower(std::vector<shared_ptr<EnemyBase>>& enemies_);

private:
    std::vector<shared_ptr<TowerBase>> towers_;

};

#endif