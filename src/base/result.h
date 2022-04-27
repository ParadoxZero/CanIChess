#ifndef _BASE_RESULT_H_
#define _BASE_RESULT_H_

namespace base
{
    namespace internal
    {
        const unsigned int SUCCESS_MASK = 0x00000000;
        const unsigned int FAILURE_MASK = 0x10000000;
    }
    enum Result 
    {
        Success = internal::SUCCESS_MASK,
        Promote,
        Check,
        Checkmate,

        Failed = internal::FAILURE_MASK,
        InvalidArgument,
        Forbidden,
        PendingPromotion
    };
}

typedef base::Result __Result;

bool inline __succeeded(base::Result code)
{
    if (code & base::internal::SUCCESS_MASK) return true;
    else return false;
}

bool inline __failed(base::Result code)
{
    if (code & base::internal::FAILURE_MASK) return true;
    else return false;
}

#define SUCCEEDED(res)          _succeeded(res)     
#define FAILLED(res)            _failed(res)

#define RETURN_IF_FAILED(res)               {__Result __res = res; if(FAILED(_res) {return;}}
#define RETURN_RESULT_IF_FAILED(res)        {__Result __res = res; if(FAILED(_res) {return _res;}}
#define RETURN_VALUE_IF_FAILED(res, value)  {__Result __res = res; if(FAILED(_res) {return value;}}

// Usage e.g. RETURN_IF_FAILED(getNextMoves(moves));

#endif // !_BASE_RESULT_H_