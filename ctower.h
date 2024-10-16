#pragma once
#include "cbullet.h"
class ctower {
    cpoint _location;
    cbullet _cb;
    public:
        ctower() { _location = { 0,0,0 }; }
        cpoint getLocation() { return _location; }
        void setLocation(cpoint tl) {
        // if (...) 
            { _location = tl; }
        }
        void setMapForBullet(cpoint[][cpoint::MAP_SIZE]);
        void calcPathBullet() {
            _cb.calcPathBullet(_location);
        }
        // Returning references is quite dangerous.
        // You need to build test functions for the cbullet
        // class before changing the value of the internal
        // properties.
        cbullet& getBullet() { return _cb; }
};