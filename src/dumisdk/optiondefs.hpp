

#ifdef FOCUS_SPEED

#include <unordered_map>
template<typename T, typename U>
using optmap = std::unodered_map<T,U>;

#else

#include <map>
template<typename T, typename U>
using optmap = std::map<T,U>;

#endif