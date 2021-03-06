#pragma once

#include "typelist.h"

template<typename TList>
struct Length;

template<typename Head, typename Tail>
struct Length<TypeList<Head, Tail>> { 
    const static int length = 1 + Length<Tail>::length;
};

template<>
struct Length<NullType> {
    const static int length = 0;
};