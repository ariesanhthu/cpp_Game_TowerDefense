#include "ctower.h"
void ctower::setMapForBullet(cpoint a[][cpoint::MAP_SIZE])
{
    for (int i = 0; i < cpoint::MAP_SIZE; i++) {
        for (int j = 0; j < cpoint::MAP_SIZE; j++) {
            _cb.updateMap(i, j, a[i][j]);
        }
    }
}