#ifndef _CHESS_ENGINE_TRITMAP_
#define _CHESS_ENGINE_TRITMAP_

#include <array>

namespace chess_engine
{
    static const int8_t TRITMAP_BLACK = -1;
    static const int8_t TRITMAP_WHITE = 1;
    static const int8_t TRITMAP_EMPTY = 0;

    typedef std::array<std::array<int8_t, 8>, 8> Tritmap;
}
#endif // !_CHESS_ENGINE_TRITMAP_