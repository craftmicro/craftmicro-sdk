#include "../Bitmap.h"

namespace craft {

    /**
     * Check whether a pixel format includes an alpha channel or not
     * @param  pixelFormat The pixel format to check
     * @return             Return true if the pixel format has an alpha channel, otherwise false
     */
    bool pixelFormatHasAlpha(PixelFormat pixelFormat) {
        switch (pixelFormat) {
            case PixelFormat::ARGB4444: return true;
            case PixelFormat::ARGB6666: return true;
            case PixelFormat::ARGB8565: return true;
            case PixelFormat::ARGB8888: return true;
            default: return false;
        }
    }

    /**
     * Return the width, in bits, of a pixel stored in this format
     * @param  pixelFormat The pixel format to check
     * @return             The width in number of bits
     */
    uint8_t pixelFormatBitWidth(PixelFormat pixelFormat) {
        switch (pixelFormat) {
            case PixelFormat::RGB565: return 16;
            case PixelFormat::ARGB4444: return 16;
            case PixelFormat::ARGB6666: return 24;
            case PixelFormat::ARGB8565: return 24;
            case PixelFormat::RGB888: return 24;
            case PixelFormat::ARGB8888: return 32;
            case PixelFormat::Grayscale8: return 8;
            case PixelFormat::Grayscale4: return 4;
            case PixelFormat::Grayscale2: return 2;
            case PixelFormat::Mono: return 1;
            case PixelFormat::Indexed: return 8;
            case PixelFormat::Unknown: return 0;
            default: return 0;
        }
    }

    /**
     * Return the width, in bytes, of a pixel stored in this format
     * @param  pixelFormat The pixel format to check
     * @return             The width in number of bytes
     */
    uint8_t pixelFormatByteWidth(PixelFormat pixelFormat) {
        return pixelFormatBitWidth(pixelFormat) >> 3;
    }

    /**
     *  ######   #####  ######
     *  ##      ##      ##
     *  #####   #####   #####
     *      ##  ##  ##      ##
     *  #####    ####   #####
     */

     /*
      * ### BITMAP ACCESS
      */

      /**
       * The following functions get a pixel from a bitmap and convert to RGB565 and 5-bit alpha.
       * Use these functions if you are using the fast alpha-blending function below that requires
       * 5-bit alpha (0-31). If you are using libraries that require 8-bit alpha, use the ...as8565
       * functions instead.
       */
    void get565as5565(uint8_t* p, uint16_t& c, uint8_t& a) {
        c = (p[0] << 8) | p[1];
    }
    void get4444as5565(uint8_t* p, uint16_t& c, uint8_t& a) {
        a = ((p[0] >> 3) & 0b11110) | ((p[0] >> 7) & 0b1); // 5-bit alpha
        c = ((p[0] & 0b1111) << 12) | ((p[0] & 0b1000) << 8)
            | ((p[1] & 0b11110000) << 3) | ((p[1] & 0b11000000) >> 1)
            | ((p[1] & 0b1111) << 1) | ((p[1] & 0b1000) >> 3);
    }
    void get6666as5565(uint8_t* p, uint16_t& c, uint8_t& a) {
        a = (p[0] >> 3); // 5-bit alpha
        c = (p[0] << 14) | ((p[1] << 6) & 0b0011100000000000) | ((p[1] << 7) & 0b0000011110000000) | ((p[1] >> 1) & 0b0000000001111111);
    }
    void get8565as5565(uint8_t* p, uint16_t& c, uint8_t& a) {
        a = (p[0] >> 3); // 8-bit to 5-bit alpha
        c = (p[1] << 8) | p[2];
    }
    void get888as5565(uint8_t* p, uint16_t& c, uint8_t& a) {
        c = ((p[0] & 0b11111000) << 8) | ((p[1] & 0b11111100) << 3) | ((p[1] & 0b11111000) >> 3);
    }
    void get8888as5565(uint8_t* p, uint16_t& c, uint8_t& a) {
        a = (p[0] >> 3); // 8-bit to 5-bit alpha
        c = ((p[1] & 0b11111000) << 8) | ((p[2] & 0b11111100) << 3) | ((p[3] & 0b11111000) >> 3);
    }
    void get8as5565(uint8_t* p, uint16_t& c, uint8_t& a) {
        c = ((p[0] & 0xF8) << 8) | ((p[0] & 0xFC) << 3) | ((p[0] & 0xF8) >> 3);
    }
    void get4as5565(uint8_t* p, uint16_t& c, uint8_t& a) {
        // Hijack 'a' as nibble index (0-1 from left to right)
        c = ((p[0] >> (1 - a) * 4) & 0b1111) * 17;
        c = ((c & 0xF8) << 8) | ((c & 0xFC) << 3) | ((c & 0xF8) >> 3);
    }
    void get2as5565(uint8_t* p, uint16_t& c, uint8_t& a) {
        // Hijack 'a' as bit-pair index (0-3 from left to right)
        c = ((p[0] >> (3 - a) * 2) & 0b11) * 85;
        c = ((c & 0xF8) << 8) | ((c & 0xFC) << 3) | ((c & 0xF8) >> 3);
    }
    void get1as5565(uint8_t* p, uint16_t& c, uint8_t& a) {
        // Hijack 'a' as bit index (0-7 from left to right)
        c = ((p[0] >> (7 - a)) & 0b1) ? Color565::White : Color565::Black;
    }

    /**
     * Use getAccessor5565 on a tilemap to choose the correct data access function.
     */
    access5565 getAccessor5565(PixelFormat pixelFormat) {
        switch (pixelFormat) {
            case PixelFormat::RGB565: return get565as5565;
            case PixelFormat::ARGB4444: return get4444as5565;
            case PixelFormat::ARGB6666: return get6666as5565;
            case PixelFormat::ARGB8565: return get8565as5565;
            case PixelFormat::RGB888: return get888as5565;
            case PixelFormat::ARGB8888: return get8888as5565;
            case PixelFormat::Grayscale8: return get8as5565;
            case PixelFormat::Grayscale4: return get4as5565;
            case PixelFormat::Grayscale2: return get2as5565;
            case PixelFormat::Mono: return get1as5565;
            case PixelFormat::Indexed: return 0;	// XXX: Handle indexed colors
            case PixelFormat::Unknown: return 0;
        }
        return 0;
    }

    /**
     * The following functions get a pixel from a bitmap and convert to RGB565 and 8-bit alpha.
     */
    void get565as8565(uint8_t* p, uint16_t& c, uint8_t& a) {
        c = (p[0] << 8) | p[1];
    }
    void get4444as8565(uint8_t* p, uint16_t& c, uint8_t& a) {
        a = (p[0] & 0b11110000) | (p[0] >> 4); // 8-bit alpha
        c = ((p[0] & 0b1111) << 12) | ((p[0] & 0b1000) << 8)
            | ((p[1] & 0b11110000) << 3) | ((p[1] & 0b11000000) >> 1)
            | ((p[1] & 0b1111) << 1) | ((p[1] & 0b1000) >> 3);
    }
    void get6666as8565(uint8_t* p, uint16_t& c, uint8_t& a) {
        a = (p[0] & 0b11111100) | ((p[0] >> 6) & 0b11);
        c = (p[0] << 14) | ((p[1] << 6) & 0b0011100000000000) | ((p[1] << 7) & 0b0000011110000000) | ((p[1] >> 1) & 0b0000000001111111);
    }
    void get8565as8565(uint8_t* p, uint16_t& c, uint8_t& a) {
        a = p[0]; // Already 8-bit alpha
        c = (p[1] << 8) | p[2];
    }
    void get888as8565(uint8_t* p, uint16_t& c, uint8_t& a) {
        c = ((p[0] & 0b11111000) << 8) | ((p[1] & 0b11111100) << 3) | ((p[1] & 0b11111000) >> 3);
    }
    void get8888as8565(uint8_t* p, uint16_t& c, uint8_t& a) {
        a = p[0]; // Already 8-bit alpha
        c = ((p[1] & 0b11111000) << 8) | ((p[2] & 0b11111100) << 3) | ((p[3] & 0b11111000) >> 3);
    }
    void get8as8565(uint8_t* p, uint16_t& c, uint8_t& a) {
        c = ((p[0] & 0xF8) << 8) | ((p[0] & 0xFC) << 3) | ((p[0] & 0xF8) >> 3);
    }
    void get4as8565(uint8_t* p, uint16_t& c, uint8_t& a) {
        // Hijack 'a' as nibble index (0-1 from left to right)
        c = ((p[0] >> (1 - a) * 4) & 0b1111) * 17;
        c = ((c & 0xF8) << 8) | ((c & 0xFC) << 3) | ((c & 0xF8) >> 3);
    }
    void get2as8565(uint8_t* p, uint16_t& c, uint8_t& a) {
        // Hijack 'a' as bit-pair index (0-3 from left to right)
        c = ((p[0] >> (3 - a) * 2) & 0b11) * 85;
        c = ((c & 0xF8) << 8) | ((c & 0xFC) << 3) | ((c & 0xF8) >> 3);
    }
    void get1as8565(uint8_t* p, uint16_t& c, uint8_t& a) {
        // Hijack 'a' as bit index (0-7 from left to right)
        c = ((p[0] >> (7 - a)) & 0b1) ? Color565::White : Color565::Black;
    }

    /**
     * Use getAccessor8565 on a tilemap to choose the correct data access function.
     */
    access8565 getAccessor8565(PixelFormat pixelFormat) {
        switch (pixelFormat) {
            case PixelFormat::RGB565: return get565as8565;
            case PixelFormat::ARGB4444: return get4444as8565;
            case PixelFormat::ARGB6666: return get6666as8565;
            case PixelFormat::ARGB8565: return get8565as8565;
            case PixelFormat::RGB888: return get888as8565;
            case PixelFormat::ARGB8888: return get8888as8565;
            case PixelFormat::Grayscale8: return get8as8565;
            case PixelFormat::Grayscale4: return get4as8565;
            case PixelFormat::Grayscale2: return get2as8565;
            case PixelFormat::Mono: return get1as8565;
            case PixelFormat::Indexed: return 0;	// XXX: Handle indexed colors
            case PixelFormat::Unknown: return 0;
        }
        return 0;
    }

    /**
     *  #####    #####   #####
     *  ##  ##  ##       ##  ##
     *  #####   ##  ###  #####
     *  ##  ##  ##   ##  ##  ##
     *  ##  ##   ######  #####
     */

     /*
      * ### BITMAP ACCESS
      */

      /**
       * The following functions get a pixel from the bitmap and convert to 8-bit per channel A,R,G,B components.
       */
    void get565asARGB(uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b) {
        r = (p[0] & 0b11111000) | ((p[0] & 0b11100000) >> 5);
        g = ((p[0] & 0b111) << 5) | ((p[1] & 0b11100000) >> 3) | ((p[0] & 0b11) >> 6);
        b = ((p[1] & 0b11111) << 3) | ((p[1] & 0b11100) >> 2);
    }
    void get4444asARGB(uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b) {
        a = (p[0] & 0b11110000) | (p[0] >> 4);
        r = (p[0] << 4) | (p[0] & 0b1111);
        g = (p[1] & 0b11110000) | (p[1] >> 4);
        b = (p[1] << 4) | (p[1] & 0b1111);
    }
    void get6666asARGB(uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b) {
        a = (p[0] & 0b11111100) | ((p[0] >> 6) & 0b11);
        r = ((p[0] << 6) & 0b11000000) | (p[0] & 0b11) | ((p[1] >> 2) & 0b111100);
        g = ((p[1] << 4) & 0b11110000) | ((p[1] >> 2) & 0b11) | ((p[2] >> 4) & 0b1100);
        b = ((p[2] << 2) & 0b11111100) | ((p[2] >> 4) & 0b11);
    }
    void get8565asARGB(uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b) {
        a = p[0];
        r = (p[1] & 0b11111000) | ((p[1] >> 5) & 0b111);
        g = ((p[1] << 5) & 0b11100000) | ((p[1] >> 1) & 0b11) | ((p[2] >> 3) & 0b11100);
        b = ((p[2] << 3) & 0b11111000) | ((p[2] >> 2) & 0b111);
    }
    void get888asARGB(uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b) {
        r = p[0];
        g = p[1];
        b = p[2];
    }
    void get8888asARGB(uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b) {
        a = p[0];
        r = p[1];
        g = p[2];
        b = p[3];
    }
    void get8asARGB(uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b) {
        r = g = b = p[0];
    }
    void get4asARGB(uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b) {
        // Hijack 'a' as bit-nibble index (0-1 from left to right)
        r = g = b = ((p[0] >> (1 - a) * 4) & 0b1111) * 17;
    }
    void get2asARGB(uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b) {
        // Hijack 'a' as bit-pair index (0-3 from left to right)
        r = g = b = ((p[0] >> (3 - a) * 2) & 0b11) * 85;
    }
    void get1asARGB(uint8_t* p, uint8_t& a, uint8_t& r, uint8_t& g, uint8_t& b) {
        // Hijack 'a' as bit index (0-7 from left to right)
        r = g = b = ((p[0] >> (7 - a)) & 0b1) ? 255 : 0;
    }

    /**
     * Use getAccessorARGB on a tilemap to choose the correct data access function.
     */
    typedef void (*accessARGB)(uint8_t*, uint8_t&, uint8_t&, uint8_t&, uint8_t&);
    accessARGB getAccessorARGB(PixelFormat pixelFormat) {
        switch (pixelFormat) {
            case PixelFormat::RGB565: return get565asARGB;
            case PixelFormat::ARGB4444: return get4444asARGB;
            case PixelFormat::ARGB6666: return get6666asARGB;
            case PixelFormat::ARGB8565: return get8565asARGB;
            case PixelFormat::RGB888: return get888asARGB;
            case PixelFormat::ARGB8888: return get8888asARGB;
            case PixelFormat::Grayscale8: return get8asARGB;
            case PixelFormat::Grayscale4: return get4asARGB;
            case PixelFormat::Grayscale2: return get2asARGB;
            case PixelFormat::Mono: return get1asARGB;
            case PixelFormat::Indexed: return 0;	// XXX: Handle indexed colors
            case PixelFormat::Unknown: return 0;
        }
        return 0;
    }

    /**
     *   #####    #####    #####
     *  ##   ##  ##   ##  ##   ##
     *   #####    #####    #####
     *  ##   ##  ##   ##  ##   ##
     *   #####    #####    #####
     */

     /*
      * ### BITMAP ACCESS
      */

      /**
       * The following functions get a pixel from the bitmap and convert to 32-bit ARGB value
       */
    void get565as8888(uint8_t* p, uint32_t i, uint32_t& c) {
        p += i * 2;
        c = (255 << 24)
            | ((p[0] & 0b11111000) << 16) | ((p[0] & 0b11100000) << 11) // R
            | ((p[0] & 0b111) << 13) | ((p[1] & 0b11100000) << 5) | ((p[0] & 0b11) << 2) // G
            | ((p[1] & 0b11111) << 3) | ((p[1] & 0b11100) >> 2); // B
    }
    void get4444as8888(uint8_t* p, uint32_t i, uint32_t& c) {
        p += i * 2;
        c = ((p[0] & 0b11110000) << 24) | (p[0] << 20) | ((p[0] & 0b1111) << 16) | ((p[1] & 0b11110000) << 8) | (p[1] << 4) | (p[1] & 0b1111);
    }
    void get6666as8888(uint8_t* p, uint32_t i, uint32_t& c) {
        p += i * 3;
        c = ((p[0] & 0b11111100) << 24) | ((p[0] & 0b11000000) << 18) // A
            | ((p[0] & 0b11) << 22) | ((p[0] & 0b11) << 16) | ((p[1] & 0b11110000) << 14) // R
            | ((p[1] & 0b1111) << 12) | ((p[1] & 0b1100) << 6) | ((p[2] & 0b11000000) << 4) // G
            | ((p[2] & 0b111111) << 2) | ((p[2] & 0b110000) >> 4); // B
    }
    void get8565as8888(uint8_t* p, uint32_t i, uint32_t& c) {
        p += i * 3;
        c = (p[0] << 24) // A
            | ((p[1] & 0b11111000) << 16) | ((p[1] & 0b11100000) << 11) // R
            | ((p[1] & 0b111) << 13) | ((p[1] & 0b110) << 7) | ((p[2] & 0b11100000) << 5) // G
            | ((p[2] << 3) & 0b11111000) | ((p[2] >> 2) & 0b111); // B
    }
    void get888as8888(uint8_t* p, uint32_t i, uint32_t& c) {
        p += i * 3;
        c = (255 << 24) | (p[0] << 16) | (p[1] << 8) | p[2];
    }
    void get8888as8888(uint8_t* p, uint32_t i, uint32_t& c) {
        p += i * 4;
        c = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
    }
    void get8as8888(uint8_t* p, uint32_t i, uint32_t& c) {
        p += i;
        c = (255 << 24) | (p[0] << 16) | (p[0] << 8) | p[0];
    }
    void get4as8888(uint8_t* p, uint32_t i, uint32_t& c) {
        p += (i >> 1);
        i = i - ((i >> 1) << 1); // rem 0 or 1
        c = ((p[0] >> (1 - i) * 4) & 0b1111) * 17;
        c = (255 << 24) | (c << 16) | (c << 8) | c;
    }
    void get2as8888(uint8_t* p, uint32_t i, uint32_t& c) {
        p += (i >> 2);
        i = i - ((i >> 2) << 2); // rem 0-3
        c = ((p[0] >> (3 - i) * 2) & 0b11) * 85;
        c = (255 << 24) | (c << 16) | (c << 8) | c;
    }
    void get1as8888(uint8_t* p, uint32_t i, uint32_t& c) {
        p += (i >> 3);
        i = i - ((i >> 3) << 3); // rem 0-7
        c = ((p[0] >> (7 - i)) & 0b1) ? Color8888::White : Color8888::Black;
    }

    /**
     * Use getAccessor8888 on a tilemap to choose the correct data access function.
     */
    access8888 getAccessor8888(PixelFormat pixelFormat) {
        switch (pixelFormat) {
            case PixelFormat::RGB565: return get565as8888;
            case PixelFormat::ARGB4444: return get4444as8888;
            case PixelFormat::ARGB6666: return get6666as8888;
            case PixelFormat::ARGB8565: return get8565as8888;
            case PixelFormat::RGB888: return get888as8888;
            case PixelFormat::ARGB8888: return get8888as8888;
            case PixelFormat::Grayscale8: return get8as8888;
            case PixelFormat::Grayscale4: return get4as8888;
            case PixelFormat::Grayscale2: return get2as8888;
            case PixelFormat::Mono: return get1as8888;
            case PixelFormat::Indexed: return 0;	// XXX: Handle indexed colors
            case PixelFormat::Unknown: return 0;
        }
        return 0;
    }

} // amespace craft
