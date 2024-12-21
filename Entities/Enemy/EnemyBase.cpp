#include "EnemyBase.h"

EnemyBase::EnemyBase(const EnemyBase& other) {
	model = other.model;
	currentPosition = other.currentPosition;
	health = other.health;
	path = other.path;
}

EnemyBase::EnemyBase(EnemyModel* nModel, int nPath) {
	model = nModel;
	health = model->getDefaultHealth();
	path = nPath;
	
}

EnemyBase::EnemyBase(EnemyModel* nModel, int nPath, int nHealth) {
	model = nModel;
	health = nHealth;
	path = nPath;
}
//EnemyBase();
EnemyBase::EnemyBase(const wchar_t* link, float factor, EnemyModel* nModel, int npath, int nHealth) : UIElement(link, factor, {0, 0}) {
	model = nModel;
	health = nHealth;
	path = npath;
}

EnemyBase::EnemyBase(const wchar_t* link, float factor, EnemyModel* nModel, int npath) : UIElement(link, factor, { 0, 0 }) {
	model = nModel;
	health = model->getDefaultHealth();
	path = npath;
	health = model->getDefaultHealth();
}
//----------------- animation ------------------------
EnemyBase::EnemyBase(const std::vector<std::wstring>& imagePaths, float factor, EnemyModel* nModel, int npath)
	:UIElement(imagePaths, factor, { 0, 0 })
{
	model = nModel;
	health = model->getDefaultHealth();
	path = npath;
	health = model->getDefaultHealth();
}

EnemyBase::EnemyBase(const std::vector<std::wstring>& imagePaths, float factor, shared_ptr<EnemyModel> nModel, int npath)
	: EnemyBase::EnemyBase(imagePaths, factor, nModel.get(), npath) {}

// ---------------------------------------------------
void EnemyBase::setCurrentPosition(const cpoint& p) { 
	currentPosition = p; 
}
void EnemyBase::setHealth(int hp) { 
	health = hp; 
}

int EnemyBase::getPath() {
	return this->path;
}

// get model attribute
int EnemyBase::getSpeed() {
	return model->getSpeed();
}
//getTexture();

//get private attribute
cpoint EnemyBase::getCurrentPosition() {
	return currentPosition;
}
int EnemyBase::getHealth() {
	return health;
}

int EnemyBase::getIndex() {
	return index;
}

bool EnemyBase::isOnRoad() {
	return onRoad;
}


// file
void EnemyBase::writeFile(ostream& o) {
	o.write((char*)&health, sizeof(int));
	o.write((char*)&currentPosition, sizeof(cpoint));
	o.write((char*)&index, sizeof(int));
	o.write((char*)&path, sizeof(int));
}
void EnemyBase::readFile(istream& i) {
	i.read((char*)&health, sizeof(int));
	i.read((char*)&currentPosition, sizeof(cpoint));
	i.read((char*)&index, sizeof(int));
	i.read((char*)&path, sizeof(int));
}

//update
bool EnemyBase::update(float delta) {
	updateUI(delta); // update animation texture
	
	// update position
	if (index < model->getPath(path).size() - model->getSpeed()) {
		currentPosition = model->getPath(path)[index += model->getSpeed()];

		// for test
		/*if (index >= model->getPath(path).size() - 5) {
			index = 0;
		}*/

		return false;
	}
	else {
		return true;
	}
}

void EnemyBase::render(HDC hdc) {
	/* DON'T PUT update onroad in update func because it won't work*/
	// update onroad
	if (health > 0
		&& index < model->getPath(path).size() - model->getSpeed()
		&& index > 0
		) {
		onRoad = true;
	}
	else {
		onRoad = false;
	}


	if (onRoad) {
		Graphic::DrawBitmap(image, { currentPosition.getX(), currentPosition.getY() }, hdc);
	}
}

void EnemyBase::hit(int n){
	if (health < n) onRoad = false;
	health -= n;
}