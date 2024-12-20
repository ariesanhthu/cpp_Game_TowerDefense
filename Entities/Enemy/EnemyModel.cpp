#include "EnemyModel.h"

EnemyModel::EnemyModel() {
	speed = 1;
	defaultHealth = 5;
}

EnemyModel::EnemyModel(int nSpeed, int hp) {
	speed = nSpeed;
	defaultHealth = hp;
}
//EnemyModel::EnemyModel(int nSpeed , texture);

void EnemyModel::setSpeed(int nSpeed){
	speed = nSpeed;
}
void EnemyModel::setDefaultHealth(int nHP) {
	defaultHealth = nHP;
}

int EnemyModel::getSpeed() {
	return speed;
}
int EnemyModel::getDefaultHealth() {
	return defaultHealth;
}

std::vector<cpoint> EnemyModel::getPath(int n) {
	return pathList[n];
}

void EnemyModel::calculatePath(std::vector< std::vector<cpoint>> pointsList) {
    pathList.clear();
    for (std::vector<cpoint> points : pointsList) 
    {
        vector<int> directionX;
        vector<int> directionY;

        cpoint currentPosition = points[0];

        for (int i = 0; i < points.size() - 1; i++) 
        {
            if (points[i].getX() < points[i + 1].getX())
            {
                directionX.push_back(1);
                directionY.push_back(0);
            }
            else if (points[i].getX() > points[i + 1].getX())
            {
                directionX.push_back(-1);
                directionY.push_back(0);
            }
            else if (points[i].getY() < points[i + 1].getY())
            {
                directionY.push_back(1);
                directionX.push_back(0);
            }
            else if (points[i].getY() > points[i + 1].getY())
            {
                directionY.push_back(-1);
                directionX.push_back(0);
            }
        }

        int currX = currentPosition.getX();
        int currY = currentPosition.getY();

        std::vector<cpoint> path;

        for (int i = 1; i < points.size(); i++)
        {
            while (currX != points[i].getX() || currY != points[i].getY()) 
            {
                path.push_back({ currX, currY, 0 });
                currX += directionX[i - 1];
                currY += directionY[i - 1];
            }
        }

        pathList.push_back(path);
        
    }

}
// getTexture();