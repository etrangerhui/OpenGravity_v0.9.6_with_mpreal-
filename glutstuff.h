/*
 *  glutstuff.h : groupe ce qui g鑢e l'affichage d閜endant de la biblioth鑡ue GLUT
 *
 *  Copyright 2001, 2002 Gwenhael LE MOINE, Michel SALVADORI
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

#ifndef GLUTSTUFF_H
#define GLUTSTUFF_H

#define largeur 600  //宽度
#define hauteur 600  //高度

#define AXES_SIZE 1000
#define DISCRETISATION 10

//	variables
static Typ_interrupteur moving = OFF;
static Typ_interrupteur fullscreen = OFF;
static GLfloat view_rotx = 0.0 ;
static GLfloat view_roty = 0.0 ;
static GLfloat view_rotz = 0.0 ;
static double my=1.e-10;

//gestion mouvements souris
static int startx;
static int starty;
//fin gestion mouvements souris

static float distance = 0.0f;
static float transl[2] = {0.0f, 0.0f};
static float rotarray[16] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 , 0.0, 0.0, 0.0, 1.0 };

static char* fichier;	//	nom du ficher
static char* fichier2;	//	nom du ficher
static char* outfile = "saved.unv";   //      fichier dans lequel on vas 閏rire
static char cc[1024];
static int intervalle_fps = 500; // intervalle en ms entre les calculs de fps

static Typ_interrupteur pause = OFF;

static float total_f = 0; // gestion FPS

//couleurs (?mettre dans un fichier ?)
static float Couleurs[][4] = {
	{1.0f,		0.0f,	0.0f,	0.0f},		//0: rouge
	{0.0f,		1.0f,	0.0f,	0.0f},		//1: vert
	{0.0f,		0.0f,	1.0f,	0.0f},		//2: bleu
	{1.0f,		1.0f,	0.0f,	0.0f},		//3: jaune
	{0.225f,	0.725f,	1.0f,	0.0f},		//4: gris
	{0.725f,	1.0f,	0.725f,	0.0f},		//5: blanc
	{1.0f,		0.225f,	0.0f,	0.0f},		//6: noir
	{1.0f,		0.0f,	1.0f,	0.0f},		//7: rose
	{1.0f,		0.5f,	1.0f,	0.0f},		//8: rose
};

//	fonctions
#define rotations() {\
	glRotatef(view_rotx, 1.0, 0.0, 0.0);\
	glRotatef(view_roty, 0.0, 1.0, 0.0);\
	glRotatef(view_rotz, 0.0, 0.0, 1.0);\
\
	glMultMatrixf(rotarray);\
}\

#define centrer_vue() {\
	int i;\
	float x_tot=0;\
	float y_tot=0;\
\
	for (i=nbC-1 ;i>=0 ; i--) {\
		x_tot+=(tbCorps[i].X).toFloat();\
		y_tot+=(tbCorps[i].Y).toFloat();\
	}\
\
	transl[0] = x_tot/nbC;\
	transl[1] = y_tot/nbC;\
}\

static void mouvementsFixe(int whichOne) {
	//
	glTranslatef(((tbCorps[whichOne].X*my).toFloat()), ((tbCorps[whichOne].Y*my).toFloat()), -34.0f-distance);
	rotations();
/*	int i=(whichOne+nbC+1)%nbC;

GLfloat eyeX = (tbCorps[whichOne].X-tbCorps[i].X)*my ;
GLfloat eyeY = (tbCorps[whichOne].Y-tbCorps[i].Y)*my;
GLfloat eyeZ = (tbCorps[whichOne].Z-tbCorps[i].Z)*my;
GLfloat distance = sqrt(sq(eyeX)+sq(eyeY)+sq(eyeZ));
glTranslatef(eyeX/2+tbCorps[i].X*my+distance, eyeY/2+tbCorps[i].Y*my, eyeZ+tbCorps[i].Z*my);
*/
//glTranslatef(transl[0]*my, transl[1]*my, -34.0f-distance);
	
}

static void mouvementsEmbarque(int whichOne) {


int i=(whichOne+nbC-1)%nbC;
// 设置眼睛位置（观察者位置），即在中心点前方一定距离的位置
GLfloat eyeX = ((tbCorps[whichOne].X-tbCorps[i].X)).toFloat()*my ;
GLfloat eyeY = ((tbCorps[whichOne].Y-tbCorps[i].Y)).toFloat()*my;
GLfloat eyeZ = ((tbCorps[whichOne].Z-tbCorps[i].Z)).toFloat()*my;
GLfloat dist = sqrt(sq(eyeX)+sq(eyeY)+sq(eyeZ));
// 使用 gluLookAt 设置视点
gluLookAt(eyeX/2+(tbCorps[i].X).toFloat()*my, eyeY/2+(tbCorps[i].Y).toFloat()*my, eyeZ+(tbCorps[i].Z).toFloat()*my-distance, 
		  eyeX, eyeY, eyeZ, 
		  -eyeX/dist,-eyeY/dist,-eyeZ/dist); // 假设上方向为 Y 轴方向
          
 //   glTranslatef(tbCorps[whichOne].X*my, tbCorps[whichOne].Y*my, tbCorps[whichOne].Z*my);      
	rotations();
	
}

static void _2DTranslate(const float x, const float y, const float z) {
	glTranslatef(x*my, y*my, 0.0);
}

static void _3DTranslate(const float x, const float y, const float z) {
	glTranslatef(x*my, y*my, z*my);
}

static void dessinSphere(const double r) {
	double d=sqrt(sqrt(r*my));
	glutSolidSphere(d, DISCRETISATION, DISCRETISATION);
}

static void dessinPoint(const double r) {
	 double d=sqrt(r*my);
	/*glBegin(GL_QUADS);
	   
		glVertex3f(0.0f, -d, -d);
		glVertex3f(0.0f, d, -d);
		glVertex3f(0.0f, d, d);
		glVertex3f(0.0f, -d, d);

		glVertex3f(-d, -d, 0.0f);
		glVertex3f(-d, d, 0.0f);
		glVertex3f(d, d, 0.0f);
		glVertex3f(d, -d, 0.0f);
	glEnd();*/
    glutSolidSphere(d, DISCRETISATION, DISCRETISATION);
	
}
//		glRasterPos2f(tbCorps[i].X*my, tbCorps[i].Y*my);\		
//		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *itoa(i,cc,10));\
	    
#define scene() {\
	int i;\
	glCallList(LST_AXES);\
\
	for (i=nbC-1 ;i>=0 ; i--) {\
	    glColor4fv(Couleurs[tbCorps[i].Couleur]);\
	    glMaterialfv(GL_FRONT, GL_DIFFUSE, Couleurs[tbCorps[i].Couleur]);\
	    glMaterialfv(GL_FRONT, GL_SPECULAR, Couleurs[5]);\
	    glMaterialfv(GL_FRONT, GL_AMBIENT, Couleurs[5]);\
	    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);\
	    glPushMatrix();\
	        ptr_translate((tbCorps[i].X).toFloat(), (tbCorps[i].Y).toFloat(), (tbCorps[i].Z).toFloat());\
			ptr_dessin(tbCorps[i].D);\
			glPopMatrix();\
	}\
}\

#define quitter(code_out) {\
		delete[]tbCorps;\
    float uptime = (glutGet(GLUT_ELAPSED_TIME)/1000.0f);\
    float ftmp = total_f / uptime;\
\
	if (uptime > 0.0f)\
		fprintf(stdout, "dur閑 d'execution : %10.3f seconde(s)\nFPS moyen : %10.10f\n", uptime, ftmp/(1000.0f/intervalle_fps));\
    exit(code_out);\
}\

//	Menus
static void selectMenu(int selection) {
	switch (selection) {
		case -1 :
			break;
		case 1 :
				collisions = (collisions == ON) ? OFF : ON;
			break ;
		case 2 :
				pause = (pause == ON) ? OFF : ON;
			break ;
		case 3 :
				if (ptr_translate == _2DTranslate ) {
					ptr_translate = _3DTranslate;
					ptr_deplace = deplace_3D;
				}
				else {
					ptr_translate = _2DTranslate;
					ptr_deplace = deplace_2D;
				}
			break;
		case 4 :
				ptr_dessin = (ptr_dessin == dessinSphere) ? dessinPoint : dessinSphere;
			break;
		case 5 :
				input_file(fichier);
			break;
		case 6 :
				askAndLoadFile();
			break;
		case 7 :
				moving = OFF;
				view_rotx = view_roty = view_rotz =\
					distance =\
					transl[0] = transl[1] =\
					rotarray[1] = rotarray[2] = rotarray[3] = rotarray[4] =\
					rotarray[6] = rotarray[7] = rotarray[8] = rotarray[9] =\
					rotarray[11] = rotarray[12] = rotarray[13] = rotarray[14] = 0.0 ;
				rotarray[0] = rotarray[5] = rotarray[10] = rotarray[15] = 1.0;
			break;
		case 8 :
				ptr_mouvements = (ptr_mouvements == mouvementsFixe) ? mouvementsEmbarque : mouvementsFixe;
			break;
		case 9 :
				lost = (lost == ON) ? OFF : ON;
			break ;
		case 10 :
		          output_file(outfile, tbCorps);
		        break;
		case 11 :
				centrer_vue();
			break;
		case 0 :
				quitter(0);
			break;
		default : break;
	}
	glutPostRedisplay();
}

static void make_menu(void) {
	glutCreateMenu(selectMenu);
glutAddMenuEntry("<c>   激活/取消碰撞管理",1);
glutAddMenuEntry("<d>   激活/取消距离控制",9);
glutAddMenuEntry("<p>   暂停 开/关",2);
glutAddMenuEntry("<2,3> 激活/取消 3D 管理",3);
glutAddMenuEntry("<s>   点 / 球体",4);
glutAddMenuEntry("<r>   重新加载文件",5);
glutAddMenuEntry("<l>   加载另一个文件",6);
glutAddMenuEntry("<i>   初始位置",7);
glutAddMenuEntry("<v>   以系统为中心",11);
glutAddMenuEntry("<e>   相机位置",8);
glutAddMenuEntry("<o>   保存到 out.unv",10);
glutAddMenuEntry("---------------------",-1);
glutAddMenuEntry("<Esc> 退出",0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//	Souris
static void mouse(int button, int state, int x, int y)
{
	int ix_tb = 0;
	int iy_tb = 0;

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			moving = ON;
			startx = x;
			starty = y;
		}
		if (state == GLUT_UP)
			moving = OFF;
	}
	if (button == GLUT_MIDDLE_BUTTON) {
		if (state == GLUT_DOWN) {}
		if (state == GLUT_UP) {}
	}
}

static void motion(int x, int y)
{
	if (moving == ON) {
		view_roty = view_roty + (x - startx);
		view_rotx = view_rotx + (y - starty);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}
}

//	Clavier
//gestion des touches "normales"
static void key(unsigned char key,int x,int y) {
	switch ( key ) {
		case 'c' :
		case 'C' : selectMenu(1);
			break;
		case 'd' :
		case 'D' : selectMenu(9);
			break;
		case 'e' :
		case 'E' : selectMenu(8);
			break;
		case 'i' :
		case 'I' : selectMenu(7);
			break;
		case 'l' :
		case 'L' : selectMenu(6);
			break;
		case 'p' :
		case 'P' : selectMenu(2);
			break;
		case 'o' :
		case 'O' : selectMenu(10);
			break;
		case 'r' :
		case 'R' : selectMenu(5);
			break;
		case 's' :
		case 'S' : selectMenu(4);
			break;
		case 'v' :
		case 'V' : selectMenu(11);
			break;
		case 'z'    : view_rotz += 2.0;
					  break;
		case 'Z'    : view_rotz -= 2.0;
					  break;
		case '3' :
		case '2' : selectMenu(3);
			break;
		case '\033' : 
			nb=(nb+1)%nbC;
			break ;
	}
}

//gestion des touches "sp閏iales"
static void special(int k, int x, int y) {
	switch (k) {
		case GLUT_KEY_PAGE_UP    : distance += 1;
							  break;
		case GLUT_KEY_PAGE_DOWN  : distance -= 1;
							  break;
		case GLUT_KEY_UP    : view_rotx += 2.0;
							  break;
		case GLUT_KEY_DOWN  : view_rotx -= 2.0;
							  break;
		case GLUT_KEY_LEFT  : view_roty += 2.0;
							  break;
		case GLUT_KEY_RIGHT : view_roty -= 2.0;
							  break;
	}
	glutPostRedisplay();
}

#endif
