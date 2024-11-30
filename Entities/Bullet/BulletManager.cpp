#include "BulletManager.h"

void BulletManager::addBullet(BulletModel* model, cpoint pos) {
	bulllets_.emplace_back(model, pos);
}

void BulletManager::addBullet(BulletBase bullet) {
	bulllets_.emplace_back(bullet);
}

void BulletManager::renderBullets() {

}

void BulletManager::update() {

	if (!bulllets_.empty()) {
		for (vector<BulletBase>::iterator it = bulllets_.begin(); it != bulllets_.end();) {
			BulletBase& bullet = *it;

			bullet.update();

			EnemyBase* e = bullet.checkCollision();
			if (e == NULL) {
				++it;
			}
			else {
				e->hit(bullet.getDame());
				it = bulllets_.erase(it);
			}
			e = nullptr;
			//++it;
		}
	}
}