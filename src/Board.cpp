#include "Board.hpp"

PIECE_TYPE Board::ToType(char s) { 
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

void Board::LoadPieces() {
    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;
    int coll = 0;
    int row = 8;
    int i = 0;

    while ((pos = fen.find(delimiter)) != std::string::npos) {
        token = fen.substr(0, pos);
        for( auto& t : token) {
            if(isdigit(t)) {
                coll += (int)t;
            } else {
                int pieceColor = (isupper(t)) ? WHITE_PIECE : BLACK_PIECE;
                int pieceType = ToType(tolower(t));

                pieces[i].id = pieceColor | pieceType;
                pieces[i].x = coll * PIECE_SIZE + gameSize.x / 2 - PIECE_SIZE*8/2;
                pieces[i].y = row * PIECE_SIZE + gameSize.y / 2 - PIECE_SIZE*8/2 - PIECE_SIZE;

                i++;
                coll++;
            }
        }
        row--;
        coll = 0;
        fen.erase(0, pos + delimiter.length());
    }
}

void Board::LoadBoard() {
    for(int i = 0; i < 64; i++) {
        int x = i / 8;
        int y = i % 8;

        if((x + y) % 2 == 0) boardPieces[i].isWhite = true;
        else boardPieces[i].isWhite = false;

        x = x * PIECE_SIZE + gameSize.x / 2 - PIECE_SIZE*8/2;
        y = y * PIECE_SIZE + gameSize.y / 2 - PIECE_SIZE*8/2;

        boardPieces[i].x = x;
        boardPieces[i].y = y;
    }
}

void Board::DrawBoard() {
    Color color;
    for(int i = 0; i < 64; i++) {
        if(boardPieces[i].isWhite) color = WHITE;
        else color = GRAY;
        DrawRectangle(boardPieces[i].x, boardPieces[i].y, PIECE_SIZE, PIECE_SIZE, color);
    } 
}

void Board::DrawPieces() {
    int amountOfPieces = sizeof(pieces)/sizeof(pieces[0]);
    int x = 0;
    int y = 0;
    for (int i = 0; i < amountOfPieces; i++) {
        x = PIECE_SIZE;
        y = PIECE_SIZE;

        // Look what texture to render
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
        std::cout << pieces[i].x << std::endl;

        DrawTextureRec(pieceTexture, Rectangle{(float)x, (float)y, (float)PIECE_SIZE, (float)PIECE_SIZE}, Vector2{(float)pieces[i].x, (float)pieces[i].y}, WHITE);
    }
}

void Board::ChangeGameSize(Vector2 size) {
    gameSize = size;
}