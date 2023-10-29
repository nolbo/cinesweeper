#ifndef POSITION_H
#define POSITION_H

class Position {
    private:
        int x;
        int y;
        int maxX;
        int maxY;

    public:
        Position();
        Position(int _x, int _y);
        Position(int _maxX, int _maxY, int _x, int _y);
        int getX();
        int getY();
        void setX(int _x);
        void setY(int _y);
        void moveX(int distance);
        void moveY(int distance);

        bool Position::operator==(Position& pos);
};

#endif