#pragma once

#include <cstdlib>
#include <string>
#include <vector>


namespace NEvenFound::NMeta {

template <typename T>
struct TTypeInfo {
    static constexpr bool ConstantSize = true;

    static constexpr size_t Size(const T&) {
        return sizeof(T);
    }

    static constexpr size_t Size() {
        return sizeof(T);
    }
};


template <>
struct TTypeInfo<std::string> {
    static constexpr bool ConstantSize = false;

    static size_t Size(const std::string &s) {
        return TTypeInfo<size_t>::Size() + s.size();
    }
};


template <typename T>
struct TTypeInfo<std::vector<T>> {
    static constexpr bool ConstantSize = false;

    static size_t Size(const std::vector<T> &v) {
        size_t size = TTypeInfo<size_t>::Size();

        if constexpr (TTypeInfo<T>::ConstantSize) {
            size +=  TTypeInfo<T>::Size() * v.size();
        } else {
            for (const T &value : v) {
                size += TTypeInfo<T>::Size(value);
            }
        }

        return size;
    }
};

}   // namespace NEvenFound::NMeta
