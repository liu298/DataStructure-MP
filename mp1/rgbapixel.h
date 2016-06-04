#ifndef rgbapixel_h
#define rgbapixel_h

#include <cstdint>
using std::uint8_t;

#include <cstdint>
#include <ostream>
class RGBAPixel {
public:
    RGBAPixel ();
    RGBAPixel (uint8_t red, uint8_t green, uint8_t blue);
    
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
private:
    
};

#endif /* rgbapixel_h */

