#pragma once
#include <raylib.h>

// x, y, id = id is type of piece like pawn rock king etc.
struct Piece {
    unsigned short x;
    unsigned short y;
    unsigned char id;
};
