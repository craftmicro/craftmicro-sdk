#pragma once

#include "geom/Point.h"
#include "geom/ClipRect.h"

using namespace std;

/**
 * Transformation matrix
 **/
namespace craft {

    /**
     * @brief A class that describes a transformation matrix
     *
     */
    class Matrix {
    public:
        /**
         * @brief X scale/rotate factor
         */
        float_t a = 1.0;

        /**
         * @brief Y skew/rotate factor
         */
        float_t b = 0.0;

        /**
         * @brief X skew/rotate factor
         */
        float_t c = 0.0;

        /**
         * @brief Y scale/rotate factor
         */
        float_t d = 1.0;

        /**
         * @brief X translate amount
         */
        float_t tx = 0.0;

        /**
         * @brief Y translate amount
         */
        float_t ty = 0.0;

        /**
         * @brief Construct a new identity Matrix object
         *
         */
        Matrix();

        /**
         * @brief Construct a new Matrix object with the specified transformations
         *
         * @param scaleX Scale along the X axis
         * @param scaleY Scale along the Y axis
         * @param rotation Rotation in radians
         * @param tx Translation along the X axis
         * @param ty Translation along the Y axis
         * @param ox Origin X coordinate
         * @param oy Origin Y coordinate
         */
        Matrix(float_t scaleX, float_t scaleY, float_t rotation, float_t tx, float_t ty, float_t ox = 0.0, float_t oy = 0.0);

        /**
         * @brief Destroy the Point object
         *
         */
        virtual ~Matrix() {}

        /**
         * @brief Apply the transformations to the current matrix
         *
         * @param scaleX Scale along the X axis
         * @param scaleY Scale along the Y axis
         * @param rotation Rotation in radians
         * @param tx Translation along the X axis
         * @param ty Translation along the Y axis
         * @param ox Origin X coordinate
         * @param oy Origin Y coordinate
         */
        void apply(float_t scaleX, float_t scaleY, float_t rotation, float_t tx, float_t ty, float_t ox = 0.0, float_t oy = 0.0);

        /**
         * @brief Transform a point using the matrix
         *
         * @param p (out) The point to transform
         */
        void transform(Point* p);

        /**
         * @brief Transform an offset point using the matrix
         *
         * @param p (out) The point to transform
         */
        void transform(Point* p, float_t originX, float_t originY);

        /**
         * @brief Transform a point using the matrix
         *
         * @param from The point to transform
         * @param to (out) The transformed point
         */
        void transform(Point* from, Point* to);

        /**
         * @brief Transform a point using the matrix and return a Point with the new values
         *
         * @param x The X coordinate
         * @param x The Y coordinate
         */
        Point* transform(float_t x, float_t y);

        /**
         * @brief Transform a ClipRect using the matrix
         *
         * @param r (out) The ClipRect to transform
         */
        void transform(ClipRect* r);

        /**
         * @brief Transform a ClipRect using the matrix
         *
         * @param from The ClipRect to transform
         * @param to (out) The transformed ClipRect
         */
        void transform(ClipRect* from, ClipRect* to);

        /**
         * @brief Transform a point using the inverse matrix
         *
         * @param p (out) The point to transform
         */
        void inverseTransform(Point* p);

        /**
         * @brief Transform an offset point using the inverse matrix
         *
         * @param p (out) The point to transform
         */
        void inverseTransform(Point* p, float_t ox, float_t oy);

        /**
         * @brief Transform a point using the inverse matrix
         *
         * @param from The point to transform
         * @param to (out) The transformed point
         */
        void inverseTransform(Point* from, Point* to);

        /**
         * @brief Transform the point using the inverse matrix and return a Point with the new values
         *
         * @param x The X coordinate
         * @param x The Y coordinate
         */
        Point* inverseTransform(float_t x, float_t y);

        /**
         * @brief Set the matrix to the identity matrix
         *
         */
        void identity();

        /**
         * @brief Concatenate a matrix to this one (combine)
         *
         * @param m The matrix to concatenate
         */
        void concat(Matrix* m);

        /**
         * @brief Invert the matrix
         *
         */
        void invert();

        /**
         * @brief Rotate the matrix
         *
         * @param angle The angle in radians
         */
        void rotate(float_t angle);

        /**
         * @brief Rotate the matrix about a point
         *
         * @param angle The angle in radians
         * @param ox The rotation point X coordinate
         * @param oy The rotation point Y coordinate
         */
        void rotate(float_t angle, float_t ox, float_t oy);

        /**
         * @brief Scale the matrix
         *
         * @param sx
         * @param sy
         */
        void scale(float_t sx, float_t sy);

        /**
         * @brief Translatet the matrix
         *
         * @param dx The distance along the X axis
         * @param dy The distance along the Y axis
         */
        void translate(float_t dx, float_t dy);

        /**
         * @brief Copy the details from the supplied matrix to this one
         *
         * @param from The matrix to copy from
         */
        void copy(Matrix* from);

        /**
         * @brief Return a clone of this matrix
         *
         * @return Matrix* The new matrix that clones this one
         */
        Matrix* clone();

    };

} // namespace craft
