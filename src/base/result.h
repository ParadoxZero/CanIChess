#ifndef _BASE_RESULT_H_
#define _BASE_RESULT_H_

namespace base
{
    enum Result 
    {
        Success,
        Promote,
        InvalidArgument,
        Forbidden,
    };
}

typedef base::Result __Result;

bool inline __succeeded(base::Result code)
{
    if (code == base::Result::Success) return true;
    else return false;
}

bool inline __failed(base::Result code)
{
    if (code != base::Result::Success) return true;
    else return false;
}

#define SUCCEEDED(res)          _succeeded(res)     
#define FAILLED(res)            _failed(res)

#define RETURN_IF_FAILED(res)               {__Result __res = res; if(FAILED(_res) {return;}}
#define RETURN_RESULT_IF_FAILED(res)        {__Result __res = res; if(FAILED(_res) {return _res;}}
#define RETURN_VALUE_IF_FAILED(res, value)  {__Result __res = res; if(FAILED(_res) {return value;}}

// Usage e.g. RETURN_IF_FAILED(getNextMoves(moves));

#endif // !_BASE_RESULT_H_