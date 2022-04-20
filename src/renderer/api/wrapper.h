#ifndef __RENDERER_API_WRAPPER__
#define __RENDERER_API_WRAPPER__

namespace renderer::api {
    class IWrapper
    {
    public:
        virtual IWrapper* getWeapRef() { return nullptr; };
    };
}

#endif // !__RENDERER_API_WRAPPER__
