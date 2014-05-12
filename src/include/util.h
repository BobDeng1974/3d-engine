#ifndef UGINE_UTIL_H
#define UGINE_UTIL_H

template <typename T, typename U, typename... Others>
bool AllEqual( const T &t, const U &u, Others const &... args )
{
    return (t == u) && AllEqual(u, args...);
}

#endif // UGINE_UTIL_H