/*
 *  main.cpp : la fonction main, les fonctions d'initialisation et les fonctions OpenGL
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

#include "config.h"

// include C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <malloc.h>

// includes OpenGL & GLUT
#include "GL/glut.h"
#include "GL/glfw3.h"

// OpenGLavity's includes
#include "globalvars.h"
#include "es.h"
#include "grav.h"
#include "glutstuff.h"
#include "gluistuff.h"
#include "parseargs.h"

//positions
static float pos_light0[] = {0.0f, 0.0f, 5.0f, 0.0f};
static float pos_light1[] = {20.0f, 0.0f, 0.0f, 0.0f};

//gestion FPS
static int frame=0;
static int temps;
static int tempsbase=0;
//fin gestion FPS

static void redraw(void) {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		ptr_mouvements(nb);
		
		glLightfv(GL_LIGHT1, GL_POSITION, pos_light1);

		scene();
	glPopMatrix();
	glutSwapBuffers();
}

static void reshape(int w,int h) {
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.,(float)w/(float)h,1.0,500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void idle(void) {
//calcul FPS
	frame++;
	temps=glutGet(GLUT_ELAPSED_TIME);
	if (temps - tempsbase > intervalle_fps) {
	    fps = frame*1000.0/(temps-tempsbase);
	    tempsbase = temps;
	    frame = 0;
#ifdef HAVE_GLUI
	    GLUI_Master.sync_live_all();
#endif
	    total_f += fps;
	    //if ((temps/1000.0f >= deadline_bench) && (deadline_bench != -1))quitter(0);
	        
	}
//fin calcul FPS
	if (pause == OFF)
	    ptr_deplace(nbC, tbCorps);
#ifdef HAVE_GLUI
	glutSetWindow(idF);
#endif
	glutPostRedisplay();
}

static void init() {
	ptr_translate = _3DTranslate;
	ptr_dessin = dessinSphere;
	ptr_mouvements = mouvementsFixe;
	ptr_deplace = deplace_3D;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Couleurs[5]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Couleurs[5]);
	glLightfv(GL_LIGHT0, GL_SHININESS, Couleurs[5]);
	glLightfv(GL_LIGHT0, GL_POSITION, pos_light0);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, Couleurs[5]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Couleurs[5]);
	glLightfv(GL_LIGHT1, GL_SHININESS, Couleurs[5]);
	glEnable(GL_LIGHT1);

	glEnable(GL_RGBA | GL_DEPTH | GL_DOUBLE);

	glNewList(LST_AXES, GL_COMPILE);
	    glBegin(GL_LINES);
	        glColor4f(0.5,0.5,0.0,1.0);

		glVertex3f(AXES_SIZE, 0, 0);
		glVertex3f(-AXES_SIZE, 0, 0);
		glVertex3f(0, AXES_SIZE, 0);
		glVertex3f(0, -AXES_SIZE, 0);
		glVertex3f(0, 0, AXES_SIZE);
		glVertex3f(0, 0, -AXES_SIZE);

		glColor4f(0.25,0.25,0.0,1.0);

		glVertex3f(AXES_SIZE, 1, 0);
		glVertex3f(-AXES_SIZE, 1, 0);
		glVertex3f(AXES_SIZE, -1, 0);
		glVertex3f(-AXES_SIZE, -1, 0);

		glVertex3f(0, 1, AXES_SIZE);
		glVertex3f(0, 1, -AXES_SIZE);
		glVertex3f(0, -1, AXES_SIZE);
		glVertex3f(0, -1, -AXES_SIZE);

		glColor4f(0.0,0.5,0.0,1.0);

		glVertex3f(1.0f, 0.9f, 0.0f);
		glVertex3f(1.1f, 0.8f, 0.0f);
		glVertex3f(1.1f, 0.9f, 0.0f);
		glVertex3f(1.0f, 0.8f, 0.0f);

		glVertex3f(0.0f, 0.9f, 1.0f);
		glVertex3f(0.0f, 0.9f, 1.1f);
		glVertex3f(0.0f, 0.9f, 1.1f);
		glVertex3f(0.0f, 0.8f, 1.0f);
		glVertex3f(0.0f, 0.8f, 1.0f);
		glVertex3f(0.0f, 0.8f, 1.1f);

	    glEnd();
	glEndList();
}

static void init_glut(void) {
	glutInitWindowSize(largeur, hauteur);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	idF = glutCreateWindow( TITRE);
	glutSetWindow(idF);
	glutPositionWindow(4, 25);

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(key);
	glutSpecialFunc(special);

	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	make_menu();
	if (fullscreen_onoff == ON)
		glutFullScreen();
}

#ifdef HAVE_GLUI
	static void init_glui(void) {
		GLUI_Master.set_glutIdleFunc(idle);
		make_controlWindow();
	}
#endif

int main(int argc, char* argv[]) {
	fprintf(stdout, "%s\nCopyright (C) 2001, 2002 Gwenhael LE MOINE, Michel SALVADORI\n\n%s est fourni avec ABSOLUMENT AUCUNE GARANTIE; pour les\ndetails voir COPYING. Ceci est un logiciel libre, et vous êtes libre de le\nredistribuer sous certaines conditions, voir COPYING pour les details.\n\n", TITRE, TITRE);
	
	if (go_parse(argc, argv) < 1)
		exit(-1);
	//if (NB_ITER_NOGRAFX < 0){LOOP=-NB_ITER_NOGRAFX;FACT=1;}else {LOOP=1;FACT=NB_ITER_NOGRAFX;}
	if ( deadline_bench != 0)my=abs(deadline_bench);else my=1; 

	if (grafx_onoff == OFF) {
	    char* date;
	    time_t date_debut;
	    time_t date_fin;

	    time( &date_debut );
	    date = asctime(localtime( &date_debut ));

	    fprintf(stdout, "Et c'est parti pour %i iterations\ndate debut : %s\n", NB_ITER_NOGRAFX, date);

	    init();
		/*
		if (NB_ITER_NOGRAFX > 0) {
			int z;
			for(z=NB_ITER_NOGRAFX ; z-- ;)
			  ptr_deplace(nbC, tbCorps);
		} else {
			fprintf(stdout, "paramètre manquant : -n<nb_iterations>\n");
			quitter(-1);
		}
		*/

	    time( &date_fin );
	    date = asctime(localtime( &date_fin ));
	    fprintf(stdout, "date fin : %s\n", date);
	    fprintf(stdout, "duree en secondes : %18.0f\n", difftime(date_fin, date_debut)*LOOP);
	    fprintf(stdout, "\n\nEt voila, c'est fini...\nAppuyer sur Entree...");
	    getchar();
	}
	else {
	    init_glut();
#ifdef HAVE_GLUI
	    switch (glui_onoff) {
	      case OFF :
#endif
				glutIdleFunc(idle);
#ifdef HAVE_GLUI
			break;
	      case ON :
			  init_glui();
		break;
	      default : exit(-1);
		break;
	    }
#endif

	    init();
		output_file("saved.unv",tbCorps);
	    glutMainLoop();
	    getchar();
	}
	quitter(0);
	//return(0);
}
