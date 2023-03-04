#pragma once
#include <raylib.h>

// x, y, id = id is type of piece like pawn rock king etc.
struct Piece {
    int x;
    int y;
    int id;
};

static int PIECE_SIZE = 125;
static Texture2D pieceTexture;