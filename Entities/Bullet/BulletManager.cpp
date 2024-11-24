#include "BulletManager.h"

void BulletManager::addBullet(BulletModel* model, cpoint pos) {
	bulllets_.emplace_back(model, pos);
}

void BulletManager::addBullet(BulletBase bullet) {
	bulllets_.emplace_back(bullet);
}

void BulletManager::renderBullets() {

}
