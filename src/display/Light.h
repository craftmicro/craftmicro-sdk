#pragma once

#include "utils/MemoryPool.h"
#include "graphics/Color.h"

namespace craft {

    enum class LightType {
        Directional,
        /*
        Point,
        Spot,
        */
    };

    /**
     * Light class
     *
     * Used as a light source for any objects that require one (@see BumpFilter)
     */
    class Light : public MemoryPool<Light> {
    public:
        /**
         * Create a new light object or take one from the pool
         * @param type The light type
         * @return The new or recycled object
         */
        static Light* Create(LightType type);

        /**
         * @brief Reset light back to defaults
         */
        virtual void reset() override;

        /**
         * @brief The type of light
         */
        LightType type = LightType::Directional;

        /**
         * @brief The x-coordinate of the light
         */
        float_t x = 0;

        /**
         * @brief The y-coordinate of the light
         */
        float_t y = 0;

        /**
         * @brief The direction that the light is facing
         */
        float_t direction = 0;

        /**
         * @brief The strength of the light at the source (0.0 - 1.0)
         *
         */
        float_t strength = 1.0;

        /**
         * @brief The color of the light
         *
         */
        color8888 color = 0xffffffff;

        /**
         * @brief The amount the strength decreases with distance
         * For example, if the strength is 1.0 at the source and the strength should
         * be 0.0 when the light reaches 400 pixels away, the attenuation should
         * be 1/400 (0.0025).
         */
        float_t attenuation = 0;

        /**
         * @brief Calculate new internal values after changing public values
         */
        void update();

        /**
         * @brief Calculate the lighting values at a specific point
         *
         * @param rx The x-coordinate in light local space
         * @param ry The y-coordinate in light local space
         * @param s (out) The strength of the light at the given coordinate
         * @param dx (out) The x direction of the light at the given coordinate
         * @param dy (out) The y direction of the light at the given coordinate
         */
        void calc(int16_t rx, int16_t ry, float_t& s, float_t& dx, float_t& dy);

    protected:
        float_t _a = 0;
        float_t _dx = 0;
        float_t _dy = 0;
    };

} // namespace craft
