# Fonts

All fonts here are available under the OFL. Craft Micro is not the creator of the fonts, but have converted them to Packed BDF.

## Packed BDF font format

Packed BDF (`packedbdf_t` or `ILI9341_t3_font_t`) is a font format based on BDF for use in c/c++ applications - most notably for the [Teensy](https://www.pjrc.com/teensy/) microprocessor development boards.

---
## Definition
```
typedef struct {
	const unsigned char *index;
	const unsigned char *unicode;
	const unsigned char *data;
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
```
---
## Explanation

For full details, including how to generate these fonts yourself, visit [github.com/projectitis/packedbdf](https://github.com/projectitis/packedbdf).
