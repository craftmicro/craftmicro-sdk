#pragma once

/**
 * 2D Vector
 **/
namespace craft {

    /**
     * Floating point Vector2D class
     */
    class Vector2F {

    public:

        /**
         * Constructor
         */
        Vector2F();
        Vector2F(float_t x, float_t y);

        /**
         * Angle in radians
         */
        float_t a;

        /**
         * Magnitude
         */
        float_t m;

        /**
         * Vector X
         */
        float_t x;

        /**
         * Vector y
         */
        float_t y;

        /**
         * Set the vector by angle and magnitude
         */
        void set(float_t x, float_t y);

        /**
         * Calculate the angle and magnitude based on x and y. Note that this
         * is done automatically after any of the methods that adust x and y, and
         * should only be called if you have manually changed x or y.
         */
        void calc();

        /**
         * Calculate the x and y based on angle and magnitude. Note that this
         * is done automatically after any of the methods that adust the angle or
         * magnitude, and should only be called if you have manually changed these.
         */
        void calcXY();

        /**
         * Add a vector to this one
         */
        void add(Vector2F* v);
        Vector2F* getAdded(Vector2F* v);

        /**
         * Subtract a vector from this one
         */
        void subtract(Vector2F* v);
        Vector2F* getSubtracted(Vector2F* v);

        /**
         * Normalise the vector
         */
        void normalize();
        Vector2F* getNormalized();

        /**
         * Rotate the vector
         */
        void rotate(float_t a);
        Vector2F* getRotated(float_t a);

    };



} // namespace craft
