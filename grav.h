/*
 *  grav.h : groupe les fonctions en rapport avec les calculs gravitationnels
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

#ifndef GRAV_H
#define GRAV_H

//#include <process.h>

/*
“计算分为两个阶段进行：

计算加速度并修改 VX, VY, VZ（速度分量）
 修改位置”
*/

//	variables
static mpreal G = 6.67430e-11;
static double FACT=1;
static int LOOP=1;
static double distanceMax = 1.e30;
static struct tt {mpreal dx,dy,dz,a,d,d2,c;} t;
static Typ_interrupteur collisions = OFF;
static Typ_interrupteur lost = OFF;
static double deadline_bench = 1;
// 宏比函数运行得更快 :D愉快
#define sq(n) ((n)*(n))
#define C 299792458
void  calcAccCorps_2D(TypCorps*C1, TypCorps*C2) {
	mpreal dx;
	mpreal dy;
	mpreal a;
	mpreal d;
	mpreal d2;
	mpreal c;
	dx = C2->X - C1->X;
	dy = C2->Y - C1->Y;
	d2 = sq(dx) + sq(dy);
	d = sqrt(d2);
	a = G*(C2->M/d2);
	c = a/d;
	if(deadline_bench<0)c=1;
	else c= 1/sqrt(1-(C1->VX*C1->VX+C1->VY*C1->VY)/C/C);
	C1->VX += dx/FACT * a/d/c;
	C1->VY += dy/FACT * a/d/c;
}

#define calcPositions_2D(n, tb) {\
	int i;\
	for (i=n-1 ; i>=0 ;i--) {\
		tb[i].X += tb[i].VX/FACT;\
		tb[i].Y += tb[i].VY/FACT;\
	}\
}\

void calcAccCorps_3D(TypCorps*C1, TypCorps* C2) {
	
	if(deadline_bench<0)t.c=1;
	else t.c= 1/sqrt(1-(C1->VX*C1->VX+C1->VY*C1->VY+C1->VZ*C1->VZ)/C/C);
	t.dx = C2->X - C1->X;
	t.dy = C2->Y - C1->Y;
	t.dz = C2->Z - C1->Z;
	t.d2 = sq(t.dx) + sq(t.dy) + sq(t.dz);
	t.d = sqrt(t.d2);
	t.a = G/t.d2/FACT/t.c;
	C1->VX += t.dx* t.a/t.d*C2->M;
	C1->VY += t.dy* t.a/t.d*C2->M;
	C1->VZ += t.dz* t.a/t.d*C2->M;
}

#define calcPositions_3D(n, tb) {\
	int i;\
	for (i=n-1 ; i>=0 ;i--) {\
		tb[i].X += tb[i].VX/FACT;\
		tb[i].Y += tb[i].VY/FACT;\
		tb[i].Z += tb[i].VZ/FACT;\
	}\
}\

#define makeNewCorps_2D(C) {\
	float a, b, l;\
	float Dist =30.0f;\
	float k = 1;\
	float x = 0.0f, y = 0.0f, z = 0.0f;\
	float vx = 0.0f, vy = 0.0f, vz = 0.0f;\
\
	a = rand()*2-RAND_MAX;\
	b = rand()*2-RAND_MAX;\
	l = sqrt((sq(a) + sq(b)));\
\
	x = Dist * (a/l);\
	y = Dist * (b/l);\
\
	vx = -y*k;\
	vy = x*k;\
\
}

void twoWorldsCollide_2D( TypCorps* tb) {
	int i;
	int j,k;
	double d;
	int dd;

	srand(glutGet(GLUT_ELAPSED_TIME));

	for (i=0 ; i<nbC;i++)
		for (j=i+1 ;j<nbC;j++)
			if (i != j) {

				//dd = (int)(tb[i].D + tb[j].D);
				if (tb[i].D + tb[j].D >  sqrt(sq(tb[j].X - tb[i].X) + sq(tb[j].Y - tb[i].Y))) {
					nb_collide++;
					//if (tb[i].M >= tb[j].M) 
					{
						tb[i].X = (tb[j].M * tb[j].X + tb[i].M * tb[i].X) / (tb[j].M + tb[i].M);
						tb[i].Y = (tb[j].M * tb[j].Y + tb[i].M * tb[i].Y) / (tb[j].M + tb[i].M);
						tb[i].M += tb[j].M;
						tb[i].D = 2*pow(pow(tb[i].D/2.0,3) + pow(tb[j].D/2.0,3),1/3.);
						tb[i].VX = (tb[j].VX * tb[j].M + tb[i].VX * tb[i].M) / (tb[j].M + tb[i].M);
						tb[i].VY = (tb[j].VY * tb[j].M + tb[i].VY * tb[i].M) / (tb[j].M + tb[i].M);
						nbC--;for(k=j;k<nbC;k++)tb[k]=tb[k+1];
						//tb[j].M=1.e-30;tb[j].D=1.e-30;
						//makeNewCorps_2D((&(tb[j])));

					}/* else {
						tb[j].X = (tb[j].M * tb[j].X + tb[i].M * tb[i].X) / (tb[j].M + tb[i].M);
						tb[j].Y = (tb[j].M * tb[j].Y + tb[i].M * tb[i].Y) / (tb[j].M + tb[i].M);
						tb[j].M += tb[i].M;
						tb[j].D = 2*pow(pow(tb[i].D/2.0,3) + pow(tb[j].D/2.0,3),1/3.);
						tb[j].VX = (tb[j].VX * tb[j].M + tb[i].VX * tb[i].M) / (tb[j].M + tb[i].M);
						tb[j].VY = (tb[j].VY * tb[j].M + tb[i].VY * tb[i].M) / (tb[j].M + tb[i].M);
						//tb[i].M=1.e-30;tb[i].D=1.e-30;
						makeNewCorps_2D(&(tb[j]));
					}*/
				}
			}
}

#define makeNewCorps_3D(C) {\
	float a, b, c, l;\
	float Dist = 30.0f;\
	float k = 1;\
	float x = 0.0f, y = 0.0f, z = 0.0f;\
	float vx = 0.0f, vy = 0.0f, vz = 0.0f;\
\
	a = rand()*2-RAND_MAX;\
	b = rand()*2-RAND_MAX;\
	c = rand()*2-RAND_MAX;\
	l = sqrt((sq(a) + sq(b) +sq(c)));\
\
	x = Dist * (a/l);\
	y = Dist * (b/l);\
	z = Dist * (c/l);\
\
	vx = -y*k;\
	vy = x*k;\
	vz = 0;\
}

void  twoWorldsCollide_3D(TypCorps* tb)
{
	double d;
	int dd;
	int i;
	int j,k;
	srand(glutGet(GLUT_ELAPSED_TIME));
	for (i=0 ; i<nbC;i++)
		for (j=i+1 ;j<nbC;j++)
			if (i != j) {
				if (tb[i].D + tb[j].D >  sqrt((tb[j].X - tb[i].X)*(tb[j].X - tb[i].X) + (tb[j].Y - tb[i].Y)*(tb[j].Y - tb[i].Y) + (tb[j].Z - tb[i].Z)*(tb[j].Z - tb[i].Z))) 
				{
					nb_collide++;
					//if (tb[i].M >= tb[j].M) 
					{
						tb[i].X = (tb[j].M * tb[j].X + tb[i].M * tb[i].X) / (tb[j].M + tb[i].M);
						tb[i].Y = (tb[j].M * tb[j].Y + tb[i].M * tb[i].Y) / (tb[j].M + tb[i].M);
						tb[i].Z = (tb[j].M * tb[j].Z + tb[i].M * tb[i].Z) / (tb[j].M + tb[i].M);
						tb[i].M += tb[j].M;
						tb[i].D = 2*pow(pow(tb[i].D/2.0,3) + pow(tb[j].D/2.0,3),1/3.);
						tb[i].VX = (tb[j].VX * tb[j].M + tb[i].VX * tb[i].M) / (tb[j].M + tb[i].M);
						tb[i].VY = (tb[j].VY * tb[j].M + tb[i].VY * tb[i].M) / (tb[j].M + tb[i].M);
						tb[i].VZ = (tb[j].VZ * tb[j].M + tb[i].VZ * tb[i].M) / (tb[j].M + tb[i].M);
						nbC--;for(k=j;k<nbC;k++)tb[k]=tb[k+1];
						//tb[j].M=1.e-30;tb[j].D=1.e-30;
						//makeNewCorps_3D(&(tb[j]));
					} 
					/*else {
						tb[j].X = (tb[j].M * tb[j].X + tb[i].M * tb[i].X) / (tb[j].M + tb[i].M);
						tb[j].Y = (tb[j].M * tb[j].Y + tb[i].M * tb[i].Y) / (tb[j].M + tb[i].M);
						tb[j].Z = (tb[j].M * tb[j].Z + tb[i].M * tb[i].Z) / (tb[j].M + tb[i].M);
						tb[j].M += tb[i].M;
						tb[j].D = 2*pow(pow(tb[i].D/2.0,3) + pow(tb[j].D/2.0,3),1/3.);
						tb[j].VX = (tb[j].VX * tb[j].M + tb[i].VX * tb[i].M) / (tb[j].M + tb[i].M);
						tb[j].VY = (tb[j].VY * tb[j].M + tb[i].VY * tb[i].M) / (tb[j].M + tb[i].M);
						tb[j].VZ = (tb[j].VZ * tb[j].M + tb[i].VZ * tb[i].M) / (tb[j].M + tb[i].M);
						//tb[i].M=1.e-30;tb[i].D=1.e-30;
						makeNewCorps_3D(&(tb[i]));
					}*/
				}
			}
}

#define lost_2D(n, tb) {\
	int i;\
	for (i=n-1 ;i>=0  ;i--)\
		if ((abs(tb[i].X) > distanceMax) || (abs(tb[i].Y) > distanceMax)) {\
			nb_lost++;\
			makeNewCorps_2D(&(tb[i]));\
		}\
}\

#define lost_3D(n, tb) {\
	int i;\
	for (i=n-1 ; i>=0 ;i--)\
		if ((abs(tb[i].X) > distanceMax) || (abs(tb[i].Y) > distanceMax) || (abs(tb[i].Z) > distanceMax)) {\
			nb_lost++;\
			makeNewCorps_3D(&(tb[i]));\
		}\
}\

//	fonctions point閑s
	int i;
	int j;
static void deplace_3D(const int nbC, TypCorps* tb) {

	int k,m;
for(m=0;m<LOOP;m++)
for(k=0;k<(FACT<=1?1:FACT);k++)
 {
	for (i=nbC-1 ; i>=0 ;i--)
	{
		for (j=i-1 ; j>=0 ;j--)
			calcAccCorps_3D((&tb[i]), (&tb[j]));
		for (j=i+1 ; j<nbC ;j++)
			calcAccCorps_3D((&tb[i]), (&tb[j]));
	}

	calcPositions_3D(nbC, tb);
	if (collisions)
		twoWorldsCollide_3D(tb);
	if (lost)
		lost_3D(nbC, tb);
  }
if(FACT<=1)COUNT+=LOOP/FACT;else COUNT+=LOOP;
   

}

static void deplace_2D(const int nbC, TypCorps* tb) {
	int i;
	int j;
	int k,m;
for(m=0;m<LOOP;m++)
for(k=0;k<(FACT<1?1:FACT);k++)
 {

	for (i=nbC-1 ; i>=0 ;i--)
	{
		for (j=i-1 ; j>=0 ;j--)calcAccCorps_2D((&tb[i]), (&tb[j]));
		for (j=i+1 ; j<nbC ;j++)calcAccCorps_2D((&tb[i]), (&tb[j]));
	}

	calcPositions_2D(nbC,tb);
	if (collisions)
		twoWorldsCollide_2D(tb);
	if (lost)
		lost_2D(nbC, tb);
  }

  if(FACT<1)COUNT+=LOOP/FACT;else COUNT+=LOOP;
}

#endif
