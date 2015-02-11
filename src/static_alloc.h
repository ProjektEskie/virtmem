#ifndef STATIC_ALLOC_H
#define STATIC_ALLOC_H

// allocator using static array; for testing

#include "alloc.h"

// UNDONE: settings below
struct SStaticAllocProperties
{
    static const uint8_t smallPageCount = 4, smallPageSize = 64;
    static const uint8_t mediumPageCount = 4, mediumPageSize = 255;
    static const uint8_t bigPageCount = 4;
    static const uint16_t bigPageSize = 1024;
    static const uint32_t poolSize = 1024 * 64;
};

template <typename TProperties=SStaticAllocProperties>
class CStaticVirtMemAlloc : public CVirtMemAlloc<TProperties, CStaticVirtMemAlloc<TProperties> >
{
    char staticData[TProperties::poolSize];

    void doStart(void) { }
    void doSuspend(void) { }
    void doStop(void) { }

    void doRead(void *data, TVirtPtrSize offset, TVirtPtrSize size)
    {
        memcpy(data, &staticData[offset], size);
    }

    void doWrite(const void *data, TVirtPtrSize offset, TVirtPtrSize size)
    {
        memcpy(&staticData[offset], data, size);
    }

public:
};

template <typename, typename> class CVirtPtr;
template <typename T> struct TStaticVirtPtr { typedef CVirtPtr<T, CStaticVirtMemAlloc<> > type; };


#endif // STATIC_ALLOC_H
