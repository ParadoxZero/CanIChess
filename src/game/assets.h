#ifndef __GAME_ASSETS__
#define __GAME_ASSETS__

#include <map>
#include <string>

namespace game
{
    enum AssetId
    {
        WhiteTile,
        BlackTile,

        WhitePawn,
        WhiteRook,
        WhiteKnight,
        WhiteBishop,
        WhiteQueen,
        WhiteKing,

        BlackPawn,
        BlackRook,
        BlackKnight,
        BlackBishop,
        BlackQueen,
        BlackKing
    };

    std::map<AssetId, std::string> AssetPath{
        {AssetId::WhiteTile, "assets/squareW.png"},
        {AssetId::BlackTile, "assets/squareB.png"},

        {AssetId::WhitePawn, "assets/pawnW.png"},
        {AssetId::WhiteRook, "assets/rookW.png"},
        {AssetId::WhiteKnight, "assets/knightW.png"},
        {AssetId::WhiteBishop, "assets/bishopW.png"},
        {AssetId::WhiteQueen, "assets/queenW.png"},
        {AssetId::WhiteKing, "assets/kingW.png"},

        {AssetId::BlackPawn, "assets/pawnB.png"},
        {AssetId::BlackRook, "assets/rookB.png"},
        {AssetId::BlackKnight, "assets/knightB.png"},
        {AssetId::BlackBishop, "assets/bishopB.png"},
        {AssetId::BlackQueen, "assets/queenB.png"},
        {AssetId::BlackKing, "assets/kingB.png"}};
}

#endif