#include "Small.h"

Small::Small(EnemyModel* nModel, int path) : EnemyBase(nModel, path) {}
Small::Small(const Small& other) : EnemyBase(other) {}