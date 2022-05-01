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
        {AssetId::BlackTile, "assets/squareB.png"}};
}

#endif