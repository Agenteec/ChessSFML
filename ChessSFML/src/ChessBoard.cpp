#include <ChessBoard.h>
std::string ChessPieceStr(int piece)
{
    std::string pieceNames[] = { "WPawn", "WKnight", "WBishop", "WRook", "WQueen", "WKing", "BPawn", "BKnight", "BBishop", "BRook", "BQueen", "BKing", "EMPTYPiece" };
    return pieceNames[piece];

}