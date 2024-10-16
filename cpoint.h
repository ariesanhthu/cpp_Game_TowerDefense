#pragma once
class cpoint {
    public:
        // Constants and data
        const static int MAP_SIZE = 10;// Map matrix size
        const static int LEFT = 3;// Left–coordinates of the map screen
        const static int TOP = 1;// Top-coordinates of map screen
        private:
        int x, y, c;
        public:
        cpoint() { x = y = c = 0; }
        cpoint(int tx, int ty, int tc) { x = tx;y = ty;c = tc; }
        int getX() { return x; }
        int getY() { return y; }
        int getC() { return c; }
        void setC(int tc) { c = tc; }
        static cpoint fromXYToRowCol(cpoint v);
        static cpoint fromRowColToXY(cpoint s);
};