/**
 * @file CraftMicro.h
 * @author Peter "Projectitis" Vullings <peter@projectitis.com>
 * @brief App development library for microprocessors
 * @version 0.3
 * @copyright Copyright (c) 2024
 * @license MIT
 *
 * Craft Micro maintains an open-source software library and set of plans
 * to craft your own microprocessor-based handheld gaming console.
 *
 * Version 0.3+ supports any platform using the Arduino framework (Teensy, ESP32, etc)
 */

#pragma once

#define CRAFTMICRO_VERSION 0.3

 /**
  * Include all Craft Micro headers
  */
#include "Common.h"
#include "display/GuiApp.h"
#include "graphics/Color8888.h"
#include "physics/Tween.h"
