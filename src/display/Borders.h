#pragma once
#ifndef _CRAFTMICRO_BORDERS_H
#define _CRAFTMICRO_BORDERS_H 1

#include "display/Border.h"

namespace craft {

	/**
	 * Border class
	 */
	class Borders {
	public:

		/**
		 * Constructor
		 */
		Borders();
		Borders( float_t size, color888 color, float_t alpha );
		~Borders();

		Border* top;
		Border* bottom;
		Border* left;
		Border* right;

		boolean inset = false;

	};

} // namespace

#endif
