#pragma once

#include "display/Sprite.h"

using namespace craft;

// Palette (12 entries)
static const uint32_t ninja_palette[] = {
	0x00000000,
	0xff010000,
	0xff3d3737,
	0xff887b73,
	0xffbda188,
	0xffd6b69c,
	0xfff6d1b4,
	0xffffffff,
	0xff322213,
	0xff603838,
	0xffd81919,
	0xffbe879a
};

// Body_1 (408 bytes)
static const uint8_t ninja_part0_data[] = {
	0x00,0x00,0x00,0x00,0x08,0x08,0x06,0x06,0x06,0x06,0x06,0x06,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x08,0x08,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x00,
	0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
	0x06,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
	0x06,0x06,0x06,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x06,0x06,0x06,0x06,0x06,0x06,
	0x06,0x06,0x06,0x06,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x06,0x06,0x06,0x06,0x06,
	0x06,0x06,0x06,0x06,0x06,0x06,0x00,0x00,0x08,0x08,0x06,0x08,0x06,0x06,0x06,0x06,
	0x06,0x06,0x06,0x0b,0x06,0x06,0x06,0x00,0x00,0x00,0x08,0x08,0x05,0x05,0x05,0x05,
	0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x00,0x00,0x00,0x00,0x05,0x05,0x05,0x05,
	0x05,0x05,0x05,0x05,0x04,0x04,0x05,0x05,0x05,0x00,0x00,0x00,0x07,0x05,0x05,0x05,
	0x05,0x05,0x05,0x05,0x04,0x05,0x05,0x05,0x05,0x05,0x00,0x00,0x07,0x07,0x07,0x05,
	0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x00,0x00,0x00,0x07,0x07,0x07,
	0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x04,0x04,0x05,0x00,0x00,0x07,0x07,0x07,
	0x07,0x07,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x00,0x00,0x00,0x07,0x07,
	0x07,0x07,0x07,0x07,0x05,0x05,0x05,0x05,0x05,0x05,0x00,0x00,0x00,0x00,0x07,0x07,
	0x07,0x07,0x07,0x07,0x07,0x07,0x05,0x05,0x05,0x05,0x05,0x00,0x00,0x00,0x00,0x07,
	0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x05,0x05,0x07,0x00,0x00,0x00,0x00,
	0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,0x00,0x00,
	0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,
	0x00,0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
	0x00,0x00,0x00,0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
	0x07,0x00,0x00,0x00,0x00,0x09,0x09,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
	0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x09,0x09,0x07,0x07,0x07,0x07,0x07,0x07,
	0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x09,0x09,0x09,0x09,0x09,0x09,
	0x09,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x09,0x09,0x09,0x09,
	0x09,0x09,0x00,0x00,0x00,0x00,0x00,0x00
};
// Eyes_1 (28 bytes)
static const uint8_t ninja_part1_data[] = {
	0x01,0x01,0x05,0x00,0x00,0x04,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x05,
	0x05,0x00,0x00,0x05,0x05,0x00,0x07,0x03,0x00,0x00,0x03,0x00
};
// Legs_1 (36 bytes)
static const uint8_t ninja_part2_data[] = {
	0x00,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x09,0x09,0x00,0x00,0x00,
	0x09,0x09,0x00,0x09,0x00,0x00,0x00,0x00,0x00,0x09,0x00,0x01,0x01,0x00,0x00,0x00,
	0x00,0x00,0x01,0x01
};
// Arm_1 (36 bytes)
static const uint8_t ninja_part3_data[] = {
	0x00,0x06,0x06,0x06,0x00,0x06,0x06,0x06,0x00,0x06,0x06,0x06,0x05,0x05,0x06,0x06,
	0x06,0x06,0x06,0x00,0x05,0x05,0x06,0x00,0x06,0x06,0x06,0x00,0x06,0x06,0x06,0x06,
	0x00,0x06,0x06,0x00
};
// Arm 2_2 (9 bytes)
static const uint8_t ninja_part4_data[] = {
	0x00,0x06,0x00,0x06,0x06,0x06,0x06,0x06,0x06
};
// Legs_4 (12 bytes)
static const uint8_t ninja_part5_data[] = {
	0x09,0x09,0x09,0x00,0x00,0x01,0x09,0x00,0x00,0x01,0x01,0x01
};
// Legs_5 (4 bytes)
static const uint8_t ninja_part6_data[] = {
	0x09,0x01,0x01,0x01
};
// Arm_5 (36 bytes)
static const uint8_t ninja_part7_data[] = {
	0x06,0x06,0x06,0x00,0x06,0x06,0x06,0x00,0x06,0x06,0x06,0x00,0x05,0x05,0x06,0x00,
	0x06,0x06,0x06,0x00,0x05,0x05,0x06,0x00,0x06,0x06,0x06,0x00,0x06,0x06,0x06,0x06,
	0x00,0x06,0x06,0x00
};
// Legs_6 (18 bytes)
static const uint8_t ninja_part8_data[] = {
	0x09,0x09,0x00,0x01,0x01,0x01,0x09,0x00,0x00,0x01,0x00,0x00,0x01,0x01,0x00,0x00,
	0x00,0x00
};
// Arm_6 (36 bytes)
static const uint8_t ninja_part9_data[] = {
	0x06,0x06,0x06,0x00,0x06,0x06,0x06,0x00,0x06,0x06,0x06,0x00,0x05,0x05,0x06,0x00,
	0x06,0x06,0x06,0x00,0x05,0x05,0x06,0x00,0x06,0x06,0x06,0x00,0x00,0x06,0x06,0x06,
	0x00,0x06,0x06,0x00
};
// Legs_7 (32 bytes)
static const uint8_t ninja_part10_data[] = {
	0x00,0x09,0x09,0x00,0x00,0x00,0x00,0x01,0x00,0x09,0x00,0x00,0x00,0x00,0x01,0x01,
	0x09,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00
};
// Arm_7 (40 bytes)
static const uint8_t ninja_part11_data[] = {
	0x06,0x06,0x06,0x00,0x00,0x06,0x06,0x06,0x00,0x00,0x06,0x06,0x06,0x00,0x00,0x05,
	0x05,0x06,0x00,0x00,0x06,0x06,0x06,0x00,0x00,0x00,0x05,0x05,0x06,0x00,0x00,0x06,
	0x06,0x06,0x06,0x00,0x00,0x06,0x06,0x00
};
// Legs_8 (44 bytes)
static const uint8_t ninja_part12_data[] = {
	0x00,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x09,0x00,0x00,
	0x00,0x00,0x00,0x01,0x01,0x00,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
	0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01
};
// Arm_8 (48 bytes)
static const uint8_t ninja_part13_data[] = {
	0x06,0x06,0x06,0x00,0x00,0x00,0x06,0x06,0x06,0x00,0x00,0x00,0x06,0x06,0x06,0x00,
	0x00,0x00,0x00,0x05,0x05,0x06,0x00,0x00,0x00,0x06,0x06,0x06,0x00,0x00,0x00,0x00,
	0x05,0x05,0x06,0x00,0x00,0x00,0x06,0x06,0x06,0x06,0x00,0x00,0x00,0x06,0x06,0x00
};
// Eyes_9 (21 bytes)
static const uint8_t ninja_part14_data[] = {
	0x01,0x01,0x05,0x00,0x00,0x04,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x05,
	0x05,0x00,0x00,0x05,0x05
};
// Legs_9 (30 bytes)
static const uint8_t ninja_part15_data[] = {
	0x00,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x09,0x09,0x00,0x00,0x00,
	0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01
};
// Legs_10 (24 bytes)
static const uint8_t ninja_part16_data[] = {
	0x01,0x09,0x09,0x09,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01
};
// Legs_11 (20 bytes)
static const uint8_t ninja_part17_data[] = {
	0x00,0x09,0x09,0x01,0x00,0x01,0x09,0x09,0x01,0x00,0x01,0x00,0x00,0x01,0x00,0x00,
	0x00,0x00,0x01,0x01
};

// Parts array (18 parts)
static const PlySpritePart ninja_parts[] = {
	{
		.width = 17,
		.height = 24,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part0_data
	},
	{
		.width = 7,
		.height = 4,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part1_data
	},
	{
		.width = 9,
		.height = 4,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part2_data
	},
	{
		.width = 4,
		.height = 9,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part3_data
	},
	{
		.width = 3,
		.height = 3,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part4_data
	},
	{
		.width = 4,
		.height = 3,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part5_data
	},
	{
		.width = 2,
		.height = 2,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part6_data
	},
	{
		.width = 4,
		.height = 9,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part7_data
	},
	{
		.width = 6,
		.height = 3,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part8_data
	},
	{
		.width = 4,
		.height = 9,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part9_data
	},
	{
		.width = 8,
		.height = 4,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part10_data
	},
	{
		.width = 5,
		.height = 8,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part11_data
	},
	{
		.width = 11,
		.height = 4,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part12_data
	},
	{
		.width = 6,
		.height = 8,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part13_data
	},
	{
		.width = 7,
		.height = 3,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part14_data
	},
	{
		.width = 10,
		.height = 3,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part15_data
	},
	{
		.width = 8,
		.height = 3,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part16_data
	},
	{
		.width = 5,
		.height = 4,
		.anchorX = 0,
		.anchorY = 0,
		.partData = ninja_part17_data
	},
};


// Animation 'Stand' frame 0 layers (4 layers)
static const PlySpriteLayer ninja_anim0_layer0_data[] = {
	{
		.partIndex = 0,
		.orientation = Transform::None,
		.x = 3,
		.y = 5,
		.start = 0,
		.strideX = 1,
		.strideY = 17
	},
	{
		.partIndex = 1,
		.orientation = Transform::None,
		.x = 12,
		.y = 7,
		.start = 0,
		.strideX = 1,
		.strideY = 7
	},
	{
		.partIndex = 2,
		.orientation = Transform::None,
		.x = 5,
		.y = 28,
		.start = 0,
		.strideX = 1,
		.strideY = 9
	},
	{
		.partIndex = 3,
		.orientation = Transform::None,
		.x = 3,
		.y = 16,
		.start = 0,
		.strideX = 1,
		.strideY = 4
	}
};


// Animation 'Stand' frames array (1 frames)
static const PlySpriteFrame ninja_anim0_frames[] = {
	{
		.duration = 0.1000,
		.layerCount = 4,
		.layerData = ninja_anim0_layer0_data
	}
};


// Animation 'Scratch' frame 0 layers (5 layers)
static const PlySpriteLayer ninja_anim1_layer0_data[] = {
	{
		.partIndex = 0,
		.orientation = Transform::None,
		.x = 3,
		.y = 5,
		.start = 0,
		.strideX = 1,
		.strideY = 17
	},
	{
		.partIndex = 1,
		.orientation = Transform::None,
		.x = 12,
		.y = 7,
		.start = 0,
		.strideX = 1,
		.strideY = 7
	},
	{
		.partIndex = 2,
		.orientation = Transform::None,
		.x = 5,
		.y = 28,
		.start = 0,
		.strideX = 1,
		.strideY = 9
	},
	{
		.partIndex = 3,
		.orientation = Transform::None,
		.x = 3,
		.y = 16,
		.start = 0,
		.strideX = 1,
		.strideY = 4
	},
	{
		.partIndex = 4,
		.orientation = Transform::None,
		.x = 15,
		.y = 21,
		.start = 0,
		.strideX = 1,
		.strideY = 3
	}
};


// Animation 'Scratch' frame 1 layers (5 layers)
static const PlySpriteLayer ninja_anim1_layer1_data[] = {
	{
		.partIndex = 0,
		.orientation = Transform::None,
		.x = 3,
		.y = 5,
		.start = 0,
		.strideX = 1,
		.strideY = 17
	},
	{
		.partIndex = 1,
		.orientation = Transform::None,
		.x = 12,
		.y = 7,
		.start = 0,
		.strideX = 1,
		.strideY = 7
	},
	{
		.partIndex = 2,
		.orientation = Transform::None,
		.x = 5,
		.y = 28,
		.start = 0,
		.strideX = 1,
		.strideY = 9
	},
	{
		.partIndex = 3,
		.orientation = Transform::None,
		.x = 3,
		.y = 16,
		.start = 0,
		.strideX = 1,
		.strideY = 4
	},
	{
		.partIndex = 4,
		.orientation = Transform::None,
		.x = 15,
		.y = 22,
		.start = 0,
		.strideX = 1,
		.strideY = 3
	}
};


// Animation 'Scratch' frames array (2 frames)
static const PlySpriteFrame ninja_anim1_frames[] = {
	{
		.duration = 0.1000,
		.layerCount = 5,
		.layerData = ninja_anim1_layer0_data
	},
	{
		.duration = 0.1000,
		.layerCount = 5,
		.layerData = ninja_anim1_layer1_data
	}
};


// Animation 'Walk' frame 0 layers (4 layers)
static const PlySpriteLayer ninja_anim2_layer0_data[] = {
	{
		.partIndex = 0,
		.orientation = Transform::None,
		.x = 3,
		.y = 5,
		.start = 0,
		.strideX = 1,
		.strideY = 17
	},
	{
		.partIndex = 1,
		.orientation = Transform::None,
		.x = 12,
		.y = 7,
		.start = 0,
		.strideX = 1,
		.strideY = 7
	},
	{
		.partIndex = 5,
		.orientation = Transform::None,
		.x = 9,
		.y = 29,
		.start = 0,
		.strideX = 1,
		.strideY = 4
	},
	{
		.partIndex = 3,
		.orientation = Transform::None,
		.x = 3,
		.y = 16,
		.start = 0,
		.strideX = 1,
		.strideY = 4
	}
};


// Animation 'Walk' frame 1 layers (4 layers)
static const PlySpriteLayer ninja_anim2_layer1_data[] = {
	{
		.partIndex = 0,
		.orientation = Transform::None,
		.x = 3,
		.y = 6,
		.start = 0,
		.strideX = 1,
		.strideY = 17
	},
	{
		.partIndex = 1,
		.orientation = Transform::None,
		.x = 12,
		.y = 8,
		.start = 0,
		.strideX = 1,
		.strideY = 7
	},
	{
		.partIndex = 6,
		.orientation = Transform::None,
		.x = 9,
		.y = 30,
		.start = 0,
		.strideX = 1,
		.strideY = 2
	},
	{
		.partIndex = 7,
		.orientation = Transform::None,
		.x = 4,
		.y = 17,
		.start = 0,
		.strideX = 1,
		.strideY = 4
	}
};


// Animation 'Walk' frame 2 layers (4 layers)
static const PlySpriteLayer ninja_anim2_layer2_data[] = {
	{
		.partIndex = 0,
		.orientation = Transform::None,
		.x = 3,
		.y = 5,
		.start = 0,
		.strideX = 1,
		.strideY = 17
	},
	{
		.partIndex = 1,
		.orientation = Transform::None,
		.x = 12,
		.y = 7,
		.start = 0,
		.strideX = 1,
		.strideY = 7
	},
	{
		.partIndex = 8,
		.orientation = Transform::None,
		.x = 7,
		.y = 29,
		.start = 0,
		.strideX = 1,
		.strideY = 6
	},
	{
		.partIndex = 9,
		.orientation = Transform::None,
		.x = 5,
		.y = 17,
		.start = 0,
		.strideX = 1,
		.strideY = 4
	}
};


// Animation 'Walk' frame 3 layers (4 layers)
static const PlySpriteLayer ninja_anim2_layer3_data[] = {
	{
		.partIndex = 0,
		.orientation = Transform::None,
		.x = 3,
		.y = 4,
		.start = 0,
		.strideX = 1,
		.strideY = 17
	},
	{
		.partIndex = 1,
		.orientation = Transform::None,
		.x = 12,
		.y = 6,
		.start = 0,
		.strideX = 1,
		.strideY = 7
	},
	{
		.partIndex = 10,
		.orientation = Transform::None,
		.x = 6,
		.y = 28,
		.start = 0,
		.strideX = 1,
		.strideY = 8
	},
	{
		.partIndex = 11,
		.orientation = Transform::None,
		.x = 5,
		.y = 16,
		.start = 0,
		.strideX = 1,
		.strideY = 5
	}
};


// Animation 'Walk' frame 4 layers (4 layers)
static const PlySpriteLayer ninja_anim2_layer4_data[] = {
	{
		.partIndex = 0,
		.orientation = Transform::None,
		.x = 3,
		.y = 5,
		.start = 0,
		.strideX = 1,
		.strideY = 17
	},
	{
		.partIndex = 1,
		.orientation = Transform::None,
		.x = 12,
		.y = 7,
		.start = 0,
		.strideX = 1,
		.strideY = 7
	},
	{
		.partIndex = 12,
		.orientation = Transform::None,
		.x = 5,
		.y = 28,
		.start = 0,
		.strideX = 1,
		.strideY = 11
	},
	{
		.partIndex = 13,
		.orientation = Transform::None,
		.x = 5,
		.y = 17,
		.start = 0,
		.strideX = 1,
		.strideY = 6
	}
};


// Animation 'Walk' frame 5 layers (4 layers)
static const PlySpriteLayer ninja_anim2_layer5_data[] = {
	{
		.partIndex = 0,
		.orientation = Transform::None,
		.x = 3,
		.y = 6,
		.start = 0,
		.strideX = 1,
		.strideY = 17
	},
	{
		.partIndex = 14,
		.orientation = Transform::None,
		.x = 12,
		.y = 9,
		.start = 0,
		.strideX = 1,
		.strideY = 7
	},
	{
		.partIndex = 15,
		.orientation = Transform::None,
		.x = 5,
		.y = 29,
		.start = 0,
		.strideX = 1,
		.strideY = 10
	},
	{
		.partIndex = 13,
		.orientation = Transform::None,
		.x = 4,
		.y = 17,
		.start = 0,
		.strideX = 1,
		.strideY = 6
	}
};


// Animation 'Walk' frame 6 layers (4 layers)
static const PlySpriteLayer ninja_anim2_layer6_data[] = {
	{
		.partIndex = 0,
		.orientation = Transform::None,
		.x = 3,
		.y = 5,
		.start = 0,
		.strideX = 1,
		.strideY = 17
	},
	{
		.partIndex = 1,
		.orientation = Transform::None,
		.x = 12,
		.y = 7,
		.start = 0,
		.strideX = 1,
		.strideY = 7
	},
	{
		.partIndex = 16,
		.orientation = Transform::None,
		.x = 6,
		.y = 29,
		.start = 0,
		.strideX = 1,
		.strideY = 8
	},
	{
		.partIndex = 11,
		.orientation = Transform::None,
		.x = 4,
		.y = 16,
		.start = 0,
		.strideX = 1,
		.strideY = 5
	}
};


// Animation 'Walk' frame 7 layers (4 layers)
static const PlySpriteLayer ninja_anim2_layer7_data[] = {
	{
		.partIndex = 0,
		.orientation = Transform::None,
		.x = 3,
		.y = 4,
		.start = 0,
		.strideX = 1,
		.strideY = 17
	},
	{
		.partIndex = 1,
		.orientation = Transform::None,
		.x = 12,
		.y = 6,
		.start = 0,
		.strideX = 1,
		.strideY = 7
	},
	{
		.partIndex = 17,
		.orientation = Transform::None,
		.x = 8,
		.y = 28,
		.start = 0,
		.strideX = 1,
		.strideY = 5
	},
	{
		.partIndex = 7,
		.orientation = Transform::None,
		.x = 4,
		.y = 15,
		.start = 0,
		.strideX = 1,
		.strideY = 4
	}
};


// Animation 'Walk' frames array (8 frames)
static const PlySpriteFrame ninja_anim2_frames[] = {
	{
		.duration = 0.1000,
		.layerCount = 4,
		.layerData = ninja_anim2_layer0_data
	},
	{
		.duration = 0.1000,
		.layerCount = 4,
		.layerData = ninja_anim2_layer1_data
	},
	{
		.duration = 0.1000,
		.layerCount = 4,
		.layerData = ninja_anim2_layer2_data
	},
	{
		.duration = 0.1000,
		.layerCount = 4,
		.layerData = ninja_anim2_layer3_data
	},
	{
		.duration = 0.1000,
		.layerCount = 4,
		.layerData = ninja_anim2_layer4_data
	},
	{
		.duration = 0.1000,
		.layerCount = 4,
		.layerData = ninja_anim2_layer5_data
	},
	{
		.duration = 0.1000,
		.layerCount = 4,
		.layerData = ninja_anim2_layer6_data
	},
	{
		.duration = 0.1000,
		.layerCount = 4,
		.layerData = ninja_anim2_layer7_data
	}
};

// Animations array
static const PlySpriteAnim ninja_anims[] = {
	// Animation 'Stand'
	{
		.direction = AnimationDirection::Forward,
		.repeats = 0,
		.anchorX = 13,
		.anchorY = 32,
		.frameCount = 1,
		.frameData = ninja_anim0_frames
	},
	// Animation 'Scratch'
	{
		.direction = AnimationDirection::Forward,
		.repeats = 3,
		.anchorX = 13,
		.anchorY = 32,
		.frameCount = 2,
		.frameData = ninja_anim1_frames
	},
	// Animation 'Walk'
	{
		.direction = AnimationDirection::Forward,
		.repeats = 0,
		.anchorX = 13,
		.anchorY = 32,
		.frameCount = 8,
		.frameData = ninja_anim2_frames
	},
};

// Animation names
static const int8_t ninja_names[] = {
	0x05,0x53,0x74,0x61,0x6e,0x64,0x07,0x53,0x63,0x72,0x61,0x74,0x63,0x68,0x04,0x57,
	0x61,0x6c,0x6b
};

// Ply sprite
static const PlySpriteData ninja = {
	.paletteCount = 12,
	.paletteData = ninja_palette,
	.partCount = 18,
	.partData = ninja_parts,
	.animCount = 3,
	.animData = ninja_anims,
	.animNames = ninja_names,
	.width = 24,
	.height = 32
};
