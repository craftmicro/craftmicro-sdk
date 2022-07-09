/**
 * @file CraftMicro.h
 * @author Peter "Projectitis" Vullings <peter@projectitis.com>
 * @brief App development library for microprocessors
 * @version 0.2
 * @date 2022-05-25
 * @copyright Copyright (c) 2022
 * @license https://choosealicense.com/licenses/mit/
 *
 * Craft Micro maintains an open-source software library and set of plans
 * to craft your own microprocessor-based handheld gaming console.
 *
 * Version 0.2 supports
 *      Teensy
 *
 * Planned support for
 *      ESP32 (via Arduino)
 */

#pragma once

#define CRAFTMICRO_VERSION 0.2

 /**
  * Include all Craft Micro headers
  */
#include "Common.h"
#include "display/GuiApp.h"
#include "display/hardware/DisplayILI9341.h"
#include "display/hardware/DisplayILI9488.h"
#include "display/hardware/DisplayST7789.h"
#include "graphics/Color8888.h"
#include "physics/Tween.h"
