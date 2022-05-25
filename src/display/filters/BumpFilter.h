#pragma once
#ifndef _CRAFTMICRO_BUMPFILTER_H
#define _CRAFTMICRO_BUMPFILTER_H 1

#include "Filter.h"
#include "display/Sprite.h"
#include "display/Light.h"

namespace craft {

    /**
     * Bump (normal map) filter
     */
    class BumpFilter : public Filter, public MemoryPool<BumpFilter> {
    public:

        /**
         * @brief Construct a new Bump Filter object or grab one from, the pool
         *
         * @param tilemap 	The tilemap to use
         * @param tileIndex The index of the active tile
         * @param lightSource The light source
         * @return BumpFilter* The new bunmp filter object
         */
        static BumpFilter* Create( const TilemapData* tilemapData, uint16_t tileIndex, Light* lightSource ) {
            BumpFilter* f = MemoryPool<BumpFilter>::Create();
            f->map->set( tilemapData, tileIndex );
            f->light = lightSource;
            return f;
        }

        /**
         * @brief Construct a new Bump Filter object
         */
        BumpFilter() {
            map = MemoryPool<Sprite>::Create();
        }

        /**
         * @brief Destroy the bump Filter object
         */
        ~BumpFilter() {
            map->recycle();
        }

        /**
         * @brief Reset filter back to defaults for recycling
         */
        virtual void reset() override {
            map->reset();
            light = nullptr;
        }

        /**
         * @brief Start the render process for the given line
         *
         * @param ry The line
         */
        void beginLine( int16_t ry ) override {
            map->beginLine( ry + map->y() );
        }

        /**
         * @brief Apply the filter to the specified pixel
         *
         * @param rx The current X position in local coordinates
         * @param ry The current Y position in local coordinates
         * @param a (in/out) The alpha value of the pixel being filtered
         * @param c (in/out) The color value of the pixel being filtered
         */
        void filterPixel( int16_t rx, int16_t ry, float_t& a, color888& c ) override {
            map->calcPixel( rx, ry );
            color8888 fc = map->getCalcColor();
            float_t s, dx, dy;
            light->calc( rx, ry, s, dx, dy );
            // Horizontal (R)
            float_t r = red( fc ) / 255.0 - 0.5;
            r *= dx;

            // Vertical (G)
            float_t g = green( fc ) / 255.0 - 0.5;
            g *= dy;

            // Amount of brightness
            float_t fa = r * s + g * s;
            if ( fa < 0 ) c = darken( c, -fa );
            else c = lighten( c, fa );

            // XXX: light->color is currently unused
        }

        /**
         * @brief The light source
         * The caller must ensure that the light is destroyed (it is not owned by the filter)
         */
        Light* light;

        /**
         * @brief The normal map
         */
        Sprite* map;

    };



} // namespace

#endif
