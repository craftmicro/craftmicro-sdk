#include "Common.h"
#include "../Matrix.h"
#include "utils/Math.h"

namespace craft {

    Matrix::Matrix() {
        identity();
    }

    Matrix::Matrix(float_t scaleX, float_t scaleY, float_t rotation, float_t tx, float_t ty, float_t ox, float_t oy) {
        if (rotation == 0) {
            a = 1.0; d = 1.0;
            b = 0.0; c = 0.0;
        }
        else {
            a = cosf(rotation);
            b = sinf(rotation);
            c = -b;
            d = a;
        }
        if (scaleX != 1) {
            a *= scaleX;
            c *= scaleX;
        }
        if (scaleY != 1) {
            b *= scaleY;
            d *= scaleY;
        }
        this->tx = tx + (ox * a + oy * c);
        this->ty = ty + (ox * b + oy * d);
    }

    void Matrix::apply(float_t scaleX, float_t scaleY, float_t rotation, float_t tx, float_t ty, float_t ox, float_t oy) {
        Matrix* m = new Matrix(scaleX, scaleY, rotation, tx, ty, ox, oy);
        concat(m);
        delete m;
    }

    void Matrix::transform(Point* p) {
        float_t px = a * p->x + c * p->y + tx;
        float_t py = b * p->x + d * p->y + ty;
        p->set(px, py);
    }

    void Matrix::transform(Point* from, Point* to) {
        to->set(a * from->x + c * from->y + tx, b * from->x + d * from->y + ty);
    }

    Point* Matrix::transform(float_t x, float_t y) {
        return new Point(a * x + c * y + tx, b * x + d * y + ty);
    }

    void Matrix::transform(Point* p, float_t originX, float_t originY) {
        transform(p);
    }

    void Matrix::inverseTransform(Point* p) {
        float_t det = a * d - b * c;
        float_t dd = (0.0 == det) ? 1.0 : 1.0 / det;

        float_t ta = d * dd;
        float_t tb = -b * dd;
        float_t tc = -c * dd;
        float_t td = a * dd;
        float_t ttx = -(ta * tx + tc * ty);
        float_t tty = -(tb * tx + td * ty);

        p->set(ta * p->x + tc * p->y + ttx, tb * p->x + td * p->y + tty);
    }

    void Matrix::inverseTransform(Point* from, Point* to) {
        to->copy(from);
        inverseTransform(to);
    }

    Point* Matrix::inverseTransform(float_t x, float_t y) {
        float_t det = a * d - b * c;
        float_t dd = (0.0 == det) ? 1.0 : 1.0 / det;

        float_t ta = d * dd;
        float_t tb = -b * dd;
        float_t tc = -c * dd;
        float_t td = a * dd;
        float_t ttx = -(ta * tx + tc * ty);
        float_t tty = -(tb * tx + td * ty);

        return new Point(ta * x + tc * y + ttx, tb * x + td * y + tty);
    }

    void Matrix::inverseTransform(Point* p, float_t ox, float_t oy) {
        translate(ox, oy);
        inverseTransform(p);
        translate(-ox, -oy);
    }

    void Matrix::concat(Matrix* m) {
        float_t ta = a;
        float_t tb = b;
        float_t tc = c;
        float_t td = d;
        float_t ttx = tx;
        float_t tty = ty;

        a = ta * m->a + tc * m->b;
        b = tb * m->a + td * m->b;
        c = ta * m->c + tc * m->d;
        d = tb * m->c + td * m->d;
        tx = ta * m->tx + tc * m->ty + ttx;
        ty = tb * m->tx + td * m->ty + tty;
    }

    void Matrix::identity() {
        a = 1.0; d = 1.0;
        b = 0.0; c = 0.0; tx = 0.0; ty = 0.0;
    }

    void Matrix::invert() {
        float_t det = a * d - b * c;
        float_t dd = (0.0 == det) ? 1.0 : 1.0 / det;

        float_t ta = a;
        float_t tb = b;
        float_t tc = c;
        float_t td = d;
        float_t ttx = tx;
        float_t tty = ty;

        a = td * dd;
        b = -tb * dd;
        c = -tc * dd;
        d = ta * dd;

        tx = -(a * ttx + c * tty);
        ty = -(b * ttx + d * tty);
    }

    void Matrix::rotate(float_t angle) {
        if (angle != 0) {
            float_t tcos = cosf(angle);
            float_t tsin = sinf(angle);

            float_t ta = a;
            float_t tb = b;
            float_t tc = c;
            float_t td = d;
            float_t ttx = tx;
            float_t tty = ty;

            a = ta * tcos - tb * tsin;
            b = ta * tsin + tb * tcos;
            c = tc * tcos - td * tsin;
            d = tc * tsin + td * tcos;
            tx = ttx * tcos - tty * tsin;
            ty = ttx * tsin + tty * tcos;
        }
    }

    void Matrix::rotate(float_t angle, float_t ox, float_t oy) {
        rotate(angle);
        this->tx = tx + (ox * a + oy * c);
        this->ty = ty + (ox * b + oy * d);
    }

    void Matrix::scale(float_t sx, float_t sy) {
        if (sx != 1.0) {
            a *= sx;
            c *= sx;
            tx *= sx;
        }
        if (sy != 1.0) {
            b *= sy;
            d *= sy;
            ty *= sy;
        }
    }

    void Matrix::translate(float_t dx, float_t dy) {
        tx += dx;
        ty += dy;
        //tx += a * dx + c * dy;
        //ty += b * dx + d * dy;
    }

    Matrix* Matrix::clone() {
        Matrix* m = new Matrix();
        m->a = a;
        m->b = b;
        m->c = c;
        m->d = d;
        m->tx = tx;
        m->ty = ty;
        return m;
    }

    void Matrix::copy(Matrix* from) {
        a = from->a;
        b = from->b;
        c = from->c;
        d = from->d;
        tx = from->tx;
        ty = from->ty;
    }

} // namespace craft