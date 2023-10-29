#include "Position.h"
#include <limits>

Position::Position() {

}

Position::Position(int _x, int _y) {
    maxX = INT_MAX;
    maxY = INT_MAX;
    x = _x;
    y = _y;
}

Position::Position(int _maxX, int _maxY, int _x, int _y) {
    maxX = _maxX;
    maxY = _maxY;
    x = _x;
    y = _y;
}

int Position::getX() {
    return x;
}

int Position::getY() {
    return y;
}

void Position::setX(int _x) {
    x = _x;
}

void Position::setY(int _y) {
    y = _y;
}

void Position::moveX(int distance) {
    int to = (x + distance) % maxX;
    x = (to == 0) ? maxX : to;
}

void Position::moveY(int distance) {
    int to = (y + distance) % maxY;
    y = (to == 0) ? maxY : to;
}

bool Position::operator==(Position& pos) {
    return (x == pos.getX() && y == pos.getY());
}
