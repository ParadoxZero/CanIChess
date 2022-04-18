#ifndef __CHESS_ENGINE_CHESS_BOARD_LISTENER__
#define __CHESS_ENGINE_CHESS_BOARD_LISTENER__

#include <cstddef>

namespace chess_engine {

    typedef size_t ObserverRegistrationToken;

    class IObserver
    {
    public:
        virtual bool NextTurnEvent() = 0;
    };

    class IChessBoardNotifier
    {
    public:
        virtual ObserverRegistrationToken SubscribeToTurnNotification(IObserver* observer) = 0;
        virtual void UnsubscribeToTurnNotification(ObserverRegistrationToken token) = 0;
    };
}

#endif // __CHESS_ENGINE_CHESS_BOARD_LISTENER__