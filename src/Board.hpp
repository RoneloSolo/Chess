#pragma once
#include "Pieces.hpp"
#include <raylib.h>
#include <string>
#include <iostream>
#include <ctype.h>


static const int BOARD_PIECE_SIZE = 125;

// x, y, isLight
struct BoardPiece {
    int x;
    int y;
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

static BoardPiece* boardPieces = (BoardPiece*) MemAlloc(sizeof(BoardPiece) * 64);

static Piece pieces[32];

std::string fenB = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR/";
std::string fenW = "PPPPPPPP/RNBQKBNR/8/8/8/8/rnbqkbnr/pppppppp/";

PIECE_TYPE ToType(char s) {
    switch (s) {
        case 'p':
            return PAWN;
        case 'n':
            return KNIGHT;
        case 'b':
            return BISHOP;
        case 'r':
            return ROCK;
        case 'k':
            return KING;
        case 'q':
            return QUEEN;
    }
    return PAWN;
}

void LoadPieces(int gameSizeX, int gameSizeY) {
    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;
    int coll = 0;
    int row = 8;
    int i = 0;
    int gX = gameSizeX;
    int gY = gameSizeY;

    std::string fen = (GetRandomValue(0,2)%2==0) ? fenW : fenB;
    
    while ((pos = fen.find(delimiter)) != std::string::npos) {
        token = fen.substr(0, pos);
        for( auto& t : token) {
            if(isdigit(t)) {
                coll += (int)t;
            } else {
                int pieceColor = (isupper(t)) ? WHITE_PIECE : BLACK_PIECE;
                int pieceType = ToType(tolower(t));
                pieces[i].id = pieceColor | pieceType;
                pieces[i].x = coll * BOARD_PIECE_SIZE + gX / 2 - BOARD_PIECE_SIZE*8/2;
                pieces[i].y = (row * BOARD_PIECE_SIZE + gY / 2 - BOARD_PIECE_SIZE*8/2) - BOARD_PIECE_SIZE;
                i++;
                coll++;
            }
        }
        row--;
        coll = 0;
        fen.erase(0, pos + delimiter.length());
    }
}


// Create the board and the pieces need to run only once in the beggining
void GenerateBoard(int gameSizeX, int gameSizeY) {
    int gX = gameSizeX;
    int gY = gameSizeY;

    for(int i = 0; i < 64; i++) {
        int x = i / 8;
        int y = i % 8;

        if((x + y) % 2 == 0) boardPieces[i].isWhite = true;
        else boardPieces[i].isWhite = false;

        x = x * BOARD_PIECE_SIZE + gX / 2 - BOARD_PIECE_SIZE*8/2;
        y = y * BOARD_PIECE_SIZE + gY / 2 - BOARD_PIECE_SIZE*8/2;

        boardPieces[i].x = x;
        boardPieces[i].y = y;
    }

    LoadPieces(gX, gY);
}

// Drawing the board
void DrawBoard() {
    Color color;
    for(int i = 0; i < 64; i++) {
        if(boardPieces[i].isWhite) color = WHITE;
        else color = GRAY;
        DrawRectangle(boardPieces[i].x, boardPieces[i].y, BOARD_PIECE_SIZE, BOARD_PIECE_SIZE, color);
    } 
}

// Is there better way to do this?
void DrawPieces() {
    int amountOfPieces = sizeof(pieces)/sizeof(pieces[0]);
    for (int i = 0; i < amountOfPieces; i++){
        int x = PIECE_SIZE;
        int y = PIECE_SIZE;
        switch (pieces[i].id) {
            case 9:
                x *= 5;
                y = 0;
                break;
            case 10:
                x *= 3;
                y = 0;
                break;
            case 11:
                x *= 2;
                y = 0;
                break;
            case 12:
                x *= 4;
                y = 0;
                break;
            case 13:
                x = 0;
                y = 0;
                break;
            case 14:
                x *= 1;
                y = 0;
                break;

            case 17:
                x *= 5;
                y *= 1;
                break;
            case 18:
                x *= 3;
                y *= 1;
                break;
            case 19:
                x *= 2;
                y *= 1;
                break;
            case 20:
                x *= 4;
                y *= 1;
                break;
            case 21:
                x = 0;
                y *= 1;
                break;
            case 2:
                x *= 1;
                y *= 1;
                break;
        }

        DrawTextureRec(pieceTexture, Rectangle{(float)x, (float)y, (float)PIECE_SIZE, (float)PIECE_SIZE}, Vector2{(float)pieces[i].x, (float)pieces[i].y}, WHITE);
    }
}
