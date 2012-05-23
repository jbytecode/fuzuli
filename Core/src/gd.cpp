/*
 * fuzuli : A general purpose interpreter
 * Copyright (C) 2012 Mehmet Hakan Satman <mhsatman@yahoo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "FuzuliTypes.h"
#include <gd.h>
#include <gdfonts.h>

using namespace std;
using namespace fuzuli;


extern "C" {
	Token *gd_createImage(Token *p, Environment *env);
	Token *gd_allocateColor(Token *p, Environment *env);
	Token *gd_drawString (Token *p, Environment *env);
	Token *gd_imagePng (Token *p, Environment *env);
}

TwoParameters
Token *gd_createImage (Token *p, Environment *env){
	int x = p->tokens[0]->getIntValue();
	int y = p->tokens[1]->getIntValue();
	gdImage *image = gdImageCreate(x,y);
	Token *result = new Token("@GdImage",COBJECT);
	result->object = (void*) image;
	return(result);
}

MoreThanThreeParameters
Token *gd_allocateColor (Token *p, Environment *env){
	gdImage *image = (gdImage*)p->tokens[0]->object;
	int red = p->tokens[1]->getIntValue();
	int green = p->tokens[2]->getIntValue();
	int blue = p->tokens[3]->getIntValue();
	int allocColor = gdImageColorAllocate(image,red,green,blue);
	Token *result = new Token(allocColor, INTEGER);
	return(result);
}

MoreThanThreeParameters
Token *gd_drawString (Token *p, Environment *env){
	gdImage *image = (gdImage*)p->tokens[0]->object;
	gdFontPtr font = gdFontSmall;
	int x =  p->tokens[1]->getIntValue();
	int y =  p->tokens[2]->getIntValue();
	int color = p->tokens[4]->getIntValue();
	gdImageString(image, font, x, y, (unsigned char*)p->tokens[3]->getContent(), color);
	return(Token::NULL_TOKEN);
}

Token *gd_imagePng (Token *p, Environment *env){
	gdImage *image = (gdImage*) p->tokens[0]->object;
	FILE *file = (FILE*) p->tokens[1]->object;
	gdImagePng(image, file);
	return(Token::NULL_TOKEN);
}



