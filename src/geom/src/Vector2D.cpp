#include <math.h>
#include "../Vector2D.h"

namespace craft {

	#define M_2PI M_PI*2
	#define M_1_2PI 1/(M_PI*2)
	#define M_PI_180 M_PI/180

	Vector2F::Vector2F() {
		this->a = 0;
		this->m = 0;
		this->x = 0;
		this->y = 0;
	}

	Vector2F::Vector2F( float_t x, float_t y ) {
		this->set( x, y );
	}

	void Vector2F::set( float_t x, float_t y ) {
		this->x = x;
		this->y = y;
		this->calc();
	}

	void Vector2F::calc() {
		this->m = sqrtf( this->x * this->x + this->y * this->y );
		this->a = atan2f( -this->y, -this->x );
	}

	void Vector2F::calcXY() {
		this->x = this->m * cosf( this->a );
		this->y = -this->m * sinf( this->a );
	}

	void Vector2F::add( Vector2F* v ) {
		this->x += v->x;
		this->y += v->y;
		this->calc();
	}
	Vector2F* Vector2F::getAdded( Vector2F* v ) {
		Vector2F* v2 = new Vector2F( this->x + v->x, this->y + v->y );
		return v2;
	}

	void Vector2F::subtract( Vector2F* v ) {
		this->x -= v->x;
		this->y -= v->y;
		this->calc();
	}
	Vector2F* Vector2F::getSubtracted( Vector2F* v ) {
		Vector2F* v2 = new Vector2F( this->x - v->x, this->y - v->y );
		return v2;
	}

	void Vector2F::normalize() {
		this->m = 1;
		this->calcXY();
	}
	Vector2F* Vector2F::getNormalized() {
		Vector2F* v = new Vector2F();
		v->m = 1;
		v->a = this->a;
		v->calcXY();
		return v;
	}

	void Vector2F::rotate( float_t a ) {
		this->a += a;
		this->a -= M_2PI * floor( this->a * M_1_2PI );
		this->calcXY();
	}
	Vector2F* Vector2F::getRotated( float_t a ) {
		Vector2F* v = new Vector2F();
		v->m = this->m;
		v->a = this->a + a;
		v->a -= M_2PI * floor( v->a * M_1_2PI );
		v->calcXY();
		return v;
	}

} // namespace
