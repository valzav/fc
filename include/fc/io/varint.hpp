#pragma once
#include <stdint.h>

namespace fc {

struct unsigned_int {
    unsigned_int( uint32_t v = 0 ):value(v){}

    template<typename T>
    unsigned_int( T v ):value(v){}

    //operator uint32_t()const { return value; }
    //operator uint64_t()const { return value; }

    template<typename T>
    operator T()const { return static_cast<T>(value); }

    unsigned_int& operator=( int32_t v ) { value = v; return *this; }
    
    uint32_t value;

    friend bool operator==( const unsigned_int& i, const uint32_t& v ) { return v == i.value; }
    friend bool operator!=( const unsigned_int& i, const uint32_t& v ) { return v != i.value; }
    friend bool operator<( const unsigned_int& i, const uint32_t& v ) { return v < i.value; }
    friend bool operator>=( const unsigned_int& i, const uint32_t& v ) { return v >= i.value; }
    friend bool operator<( const unsigned_int& i, const unsigned_int& v ) { return v < i.value; }
    friend bool operator>=( const unsigned_int& i, const unsigned_int& v ) { return v >= i.value; }
};

/**
 *  @brief serializes a 32 bit signed interger in as few bytes as possible
 *
 *  Uses the google protobuf algorithm for seralizing signed numbers
 */
struct signed_int {
    signed_int( int64_t v = 0 ):value(v){}
    operator int32_t()const { return value; }
    template<typename T>
    signed_int& operator=( const T& v ) { value = v; return *this; }
    signed_int& operator++(int){ ++value; return *this; }
    signed_int& operator++(){ ++value; return *this; }

    int32_t value;
};

class variant;

void to_variant( const signed_int& var,  variant& vo );
void from_variant( const variant& var,  signed_int& vo );
void to_variant( const unsigned_int& var,  variant& vo );
void from_variant( const variant& var,  unsigned_int& vo );

}  // namespace fc

#include <unordered_map>
namespace std
{
   template<>
   struct hash<fc::signed_int>
   {
       public:
         size_t operator()(const fc::signed_int &a) const 
         {
            return std::hash<int32_t>()(a.value);
         }
   };
}
