/*
 * Authors (alphabetical order)
 * - Andre Bernet <bernet.andre@gmail.com>
 * - Andreas Weitl
 * - Bertrand Songis <bsongis@gmail.com>
 * - Bryan J. Rentoul (Gruvin) <gruvin@gmail.com>
 * - Cameron Weeks <th9xer@gmail.com>
 * - Erez Raviv
 * - Gabriel Birkus
 * - Jean-Pierre Parisy
 * - Karl Szmutny
 * - Michael Blandford
 * - Michal Hlavinka
 * - Pat Mackenzie
 * - Philip Moss
 * - Rob Thomson
 * - Romolo Manfredini <romolo.manfredini@gmail.com>
 * - Thomas Husterer
 *
 * opentx is based on code named
 * gruvin9x by Bryan J. Rentoul: http://code.google.com/p/gruvin9x/,
 * er9x by Erez Raviv: http://code.google.com/p/er9x/,
 * and the original (and ongoing) project by
 * Thomas Husterer, th9x: http://code.google.com/p/th9x/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "lcd.h"
#include "menus.h"

#define DEFAULT_SCROLLBAR_X            (LCD_W-1)
#define NUM_BODY_LINES                 (LCD_LINES-1)
#define MENU_HEADER_HEIGHT             FH
#define MENU_INIT_VPOS                 0

#define BITMAP_BUFFER_SIZE(width, height)   (2 + (width) * (((height)+7)/8)*4)
#define MODEL_BITMAP_WIDTH             64
#define MODEL_BITMAP_HEIGHT            32
#define MODEL_BITMAP_SIZE              BITMAP_BUFFER_SIZE(MODEL_BITMAP_WIDTH, MODEL_BITMAP_HEIGHT)
extern uint8_t modelBitmap[MODEL_BITMAP_SIZE];
bool loadModelBitmap(char * name, uint8_t * bitmap);
#define LOAD_MODEL_BITMAP()            loadModelBitmap(g_model.header.bitmap, modelBitmap)

struct MenuItem {
  const char *name;
  const MenuHandlerFunc action;
};

int circularIncDec(int current, int inc, int min, int max, IsValueAvailable isValueAvailable=NULL);
void displaySplash();
void displayScreenIndex(uint8_t index, uint8_t count, uint8_t attr);
void drawVerticalScrollbar(coord_t x, coord_t y, coord_t h, uint16_t offset, uint16_t count, uint8_t visible);
void displayMenuBar(const MenuItem *menu, int index);
void drawProgressBar(const char *label);
void updateProgressBar(int num, int den);
void drawGauge(coord_t x, coord_t y, coord_t w, coord_t h, int32_t val, int32_t max);

extern coord_t scrollbar_X;
#define SET_SCROLLBAR_X(x) scrollbar_X = (x);

