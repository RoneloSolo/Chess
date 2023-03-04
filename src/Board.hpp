#pragma once
#include "Pieces.hpp"
#include <string>
#include <iostream>
#include <ctype.h>
#include <memory> 

struct BoardPiece {
    unsigned short x;
    unsigned short y;
    bool isWhite;
};

enum PIECE_TYPE {
    PAWN = 1,
    KNIGHT = 2,
    BISHOP = 3,
    ROCK = 4,
    KING = 5,
    QUEEN = 6,

    WHITE_PIECE = 8,
    BLACK_PIECE = 16
};

class Board {
    public:
        void LoadPieces();
        void LoadBoard();
        void DrawBoard();
        void DrawPieces();
        void ChangeGameSize(Vector2);
        PIECE_TYPE ToType(char);
        Texture2D pieceTexture;
    
    private:
        Vector2 gameSize;
        BoardPiece boardPieces[64];
        Piece pieces[32];
        std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR/";
        const unsigned char PIECE_SIZE = 125;
};