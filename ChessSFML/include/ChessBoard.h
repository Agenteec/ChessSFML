#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
struct SpritePiece
{
    sf::Sprite Piece;
    sf::Vector2i Pos;
    int Type;
    SpritePiece(sf::Sprite Piece, sf::Vector2i Pos, int Type) :Piece(Piece), Pos(Pos), Type(Type) {}
};
enum ChessPiece {
    WPawn,
    WKnight,
    WBishop,
    WRook,
    WQueen,
    WKing,
    BPawn,
    BKnight,
    BBishop,
    BRook,
    BQueen,
    BKing,
    EMPTYPiece
};
std::string ChessPieceStr(int piece);
/*
* Классика - 0
* Классика - 1
* Шахматы Фишера - 2
* 
*/
class ChessBoard
{
private:
    
public:
    __int8** board;
    int XMax;
    int YMax;
    int GameMode;
    //Конструктор классической игры(По умолчанию)
    ChessBoard(): XMax(8),YMax(8),GameMode(0) {
        board = new __int8*[8];
        for (int i = 0;i<8;i++)
            board[i] = new __int8[8];
        for (int i = 2; i < 6; i++)
            for (int j = 0; j < 8; j++)
            {
                board[i][j] = EMPTYPiece;
            }
               
        board[7][0] = BRook; board[7][1] = BKnight; board[7][2] = BBishop;  board[7][3] = BQueen;   board[7][4] = BKing; board[7][5] = BBishop; board[7][6] = BKnight;  board[7][7] = BRook;
        board[6][0] = BPawn; board[6][1] = BPawn;   board[6][2] = BPawn;    board[6][3] = BPawn;    board[6][4] = BPawn; board[6][5] = BPawn;   board[6][6] = BPawn;    board[6][7] = BPawn;
        //EMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTY//
        //EMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTY//
        //EMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTY//
        //EMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTY//
        board[1][0] = WPawn; board[1][1] = WPawn;   board[1][2] = WPawn;    board[1][3] = WPawn;    board[1][4] = WPawn; board[1][5] = WPawn;   board[1][6] = WPawn;    board[1][7] = WPawn;
        board[0][0] = WRook; board[0][1] = WKnight; board[0][2] = WBishop;  board[0][3] = WQueen;   board[0][4] = WKing; board[0][5] = WBishop; board[0][6] = WKnight;  board[0][7] = WRook;
    }
    ChessBoard(__int8** board,int XMax,int YMax,int GameMode = 0) : XMax(XMax), YMax(XMax),board(board),GameMode(GameMode) {}
    void SetGameMode(int GameMode,int XMax = 8,int YMax = 8)
    {
        if (this->GameMode != GameMode)
        {
            switch (GameMode)
            {
            case 0:
                ClassicBoard();
                break;
            case 2:
                break;
                Chess960();
            default:
                ClassicBoard();
                break;
            }


        }
    }
    void ClassicBoard()
    {
        for (int i = 0; i < this->XMax; i++)
            delete[] board[i];
        delete[] board;

        __int8** board = new __int8* [XMax];
        for (int i = 0; i < XMax; i++)
            board[i] = new __int8[YMax];
        if (GameMode == 0 && XMax >= 8 && YMax >= 8)
        {
            for (int i = 0; i < XMax; i++)
                for (int j = 0; j < YMax; j++)
                {
                    board[i][j] = EMPTYPiece;
                }

            board[7][0] = BRook; board[7][1] = BKnight; board[7][2] = BBishop;  board[7][3] = BQueen;   board[7][4] = BKing; board[7][5] = BBishop; board[7][6] = BKnight;  board[7][7] = BRook;
            board[6][0] = BPawn; board[6][1] = BPawn;   board[6][2] = BPawn;    board[6][3] = BPawn;    board[6][4] = BPawn; board[6][5] = BPawn;   board[6][6] = BPawn;    board[6][7] = BPawn;
            //EMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTY//
            //EMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTY//
            //EMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTY//
            //EMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTY//
            board[1][0] = WPawn; board[1][1] = WPawn;   board[1][2] = WPawn;    board[1][3] = WPawn;    board[1][4] = WPawn; board[1][5] = WPawn;   board[1][6] = WPawn;    board[1][7] = WPawn;
            board[0][0] = WRook; board[0][1] = WKnight; board[0][2] = WBishop;  board[0][3] = WQueen;   board[0][4] = WKing; board[0][5] = WBishop; board[0][6] = WKnight;  board[0][7] = WRook;
        }
        else
        {
            for (int i = 0; i < XMax; i++)
                for (int j = 0; j < YMax; j++)
                {
                    board[i][j] = EMPTYPiece;
                }
        }
    }
    void Chess960()
    {
        for (int i = 0; i < this->XMax; i++)
            delete[] board[i];
        delete[] board;

        __int8** board = new __int8* [XMax];
        for (int i = 0; i < XMax; i++)
            board[i] = new __int8[YMax];
        if (GameMode == 0 && XMax >= 8 && YMax >= 8)
        {
            for (int i = 0; i < XMax; i++)
                for (int j = 0; j < YMax; j++)
                {
                    board[i][j] = EMPTYPiece;
                }

            board[7][0] = BQueen; board[7][1] = BRook; board[7][2] = BBishop;  board[7][3] = BKnight;   board[7][4] = BKing; board[7][5] = BBishop; board[7][6] = BKnight;  board[7][7] = BRook;
            board[6][0] = BPawn; board[6][1] = BPawn;   board[6][2] = BPawn;    board[6][3] = BPawn;    board[6][4] = BPawn; board[6][5] = BPawn;   board[6][6] = BPawn;    board[6][7] = BPawn;
            //EMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTY//
            //EMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTY//
            //EMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTY//
            //EMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTYEMPTY//
            board[1][0] = WPawn; board[1][1] = WPawn;   board[1][2] = WPawn;    board[1][3] = WPawn;    board[1][4] = WPawn; board[1][5] = WPawn;   board[1][6] = WPawn;    board[1][7] = WPawn;
            board[0][0] = WQueen; board[0][1] = WRook; board[0][2] = WBishop;  board[0][3] = WKnight;   board[0][4] = WKing; board[0][5] = WBishop; board[0][6] = WKnight;  board[0][7] = WRook;
        }
        else
        {
            for (int i = 0; i < XMax; i++)
                for (int j = 0; j < YMax; j++)
                {
                    board[i][j] = EMPTYPiece;
                }
        }
    }
    ~ChessBoard()
    {
        for (int i = 0; i < XMax; i++)
            delete[] board[i];
        delete[] board;
    }

};

