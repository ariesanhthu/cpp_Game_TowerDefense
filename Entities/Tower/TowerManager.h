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

    void setLoadTower(std::vector<shared_ptr<TowerBase>>);


    void setNOfTower(int x);
    int getNOfTower();

    void setNOfTowerType(vector<int> setType);

private:
    std::vector<shared_ptr<TowerBase>> towers_;

    vector<int> MaxOfEachType = { 4, 3, 2 }; //test
    vector<int> NOfEachType = { 0, 0, 0 };   // test

    int nOfTower = 5;
};

#endif