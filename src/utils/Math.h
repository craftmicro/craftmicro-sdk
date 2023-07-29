#pragma once

#include <math.h>

namespace craft {

    /**
     * @brief Math helper functions
     *
     */
    class Math {
    public:
        /**
         * @brief Pi
         *
         */
        constexpr static const double Pi = 3.14159265358979323846;

        /**
         * @brief Pi / 180
         *
         */
        constexpr static const double Pi_180 = Math::Pi / 180.0;

        /**
         * @brief 1 / Pi
         *
         */
        constexpr static const double iPi = 1.0 / Math::Pi;

        /**
         * @brief 180 / Pi
         *
         */
        constexpr static const double _180_Pi = 180.0 / Math::Pi;

        /**
         * @brief Linear interpolation between two values
         * Note: Does not check if k is in correct range
         * @param a Start value
         * @param b End value
         * @param k Position (0.0 - 1.0)
         */
        static inline float_t lerp(float_t a, float_t b, float_t k) {
            return a + k * (b - a);
        }

        /**
         * @brief Convert angle in radians to degrees
         *
         * @param r The angle in radians
         * @return double The angle in degrees
         */
        static inline double radToDeg(double r) {
            return r * _180_Pi;
        }

        /**
         * @brief Convert angle in degrees to radians
         *
         * @param r The angle in degrees
         * @return double The angle in radians
         */
        static inline double degToRad(double r) {
            return r * Pi_180;
        }

    };

} // craft