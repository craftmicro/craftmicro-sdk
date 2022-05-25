#pragma once
#ifndef _PACKEDBDF_H_
#define _PACKEDBDF_H_

 /**
  * This is the original ILI9341_t3_font_t data structure by Paul Stoffregen,
  * renamed as packedbdf_t. This is an attempt to make a generic name that
  * is not dependend on any specific display or any specific microprocessor.
  *
  * Documentation on the packedbdf_t font data format:
  * https://github.com/projectitis/packedbdf
  *
  * Original documentation on the ILI9341_t3 font data format:
  * https://forum.pjrc.com/threads/54316-ILI9341_t-font-structure-format
  */
typedef struct {
	const unsigned char* index;
	const unsigned char* unicode;
	const unsigned char* data;
	unsigned char version;
	unsigned char reserved;
	unsigned char index1_first;
	unsigned char index1_last;
	unsigned char index2_first;
	unsigned char index2_last;
	unsigned char bits_index;
	unsigned char bits_width;
	unsigned char bits_height;
	unsigned char bits_xoffset;
	unsigned char bits_yoffset;
	unsigned char bits_delta;
	unsigned char line_space;
	unsigned char cap_height;
} packedbdf_t;
typedef packedbdf_t ILI9341_t3_font_t;

#endif
