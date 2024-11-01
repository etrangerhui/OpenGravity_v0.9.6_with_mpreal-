/*
 *  globalvars.h : regroupe certaines variables globales et déclarations de type
 *
 *  Copyright (C) 2001, 2002 Gwenhael LE MOINE, Michel SALVADORI
 *
 *   This file is part of OpenGLavity.
 *
 *   OpenGLavity is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   OpenGLavity is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with OpenGLavity; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef GLOBALVARS_H
#define GLOBALVARS_H
#include "mpreal.h"
using mpfr::mpreal;
//	définitions de type
typedef enum {OFF, ON} Typ_interrupteur;


typedef struct {
	mpreal X;
	mpreal Y;
	mpreal Z;
	mpreal M;
	double D;
	mpreal VX;
	mpreal VY;
	mpreal VZ;
	int Couleur;
} TypCorps;

//variables
  // Système
  static TypCorps* tbCorps;

  static int nbC = 2,nb=0;		//	nombre de corps
  static int nb_collide = 0;	//	nombre de collisions
  static int nb_lost = 0;
  // fin Système
  static int COUNT=0;
// Call listes
#define LST_AXES 1
// fin Call listes

//	pointeurs de fonctions
static void (*ptr_deplace)    (const int, TypCorps*);			//	2D / 3D
static void (*ptr_translate)  (const float, const float, const float);  //	pointeur sur la fonction de translation avant dessin (2D / 3D)
static void (*ptr_dessin)     (const double);			        //	pointeur sur la fonction de dessin (sphère / point)
static void (*ptr_mouvements) (int);					//	caméra fixe / embarqu?
//	fin pointeurs de fonctions

#endif
