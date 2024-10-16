#include "cgame.h"
cgame::cgame() {
    _ISEXIT1 = _ISEXIT2 = false;
}
void cgame::startGame() {
    system("cls");
    _map.drawMap();
}