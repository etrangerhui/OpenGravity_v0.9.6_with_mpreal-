/*
 *  gluistuff.h : groupe ce qui gère l'affichage dépendant de la bibliothèque GLUI
 *                                                  (http://www.cs.unc.edu/~rademach/glui)
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


#ifndef GLUISTUFF_H
#define GLUISTUFF_H

static float fps = 0.0f; // gestion FPS

static int idF;	//	window ID

#ifdef HAVE_GLUI
#ifdef WIN32
	#include "GL/glui.h"
#endif
#ifdef unix
	#include "glui.h"
#endif

	static GLUI* glui_controlWindow;
	static GLUI_EditText* get;
	static GLUI_EditText* get_outfile;
	static GLUI_Panel* p_boutons;
	static GLUI_Panel* sp_infos;
	static GLUI_Panel* sp_rb_reglages;
	static GLUI_Panel* rb_2d3d;
	static GLUI_Panel* rb_spherepoint;
	static GLUI_Panel* rb_camera;
	static GLUI_Rollout* ro_parametres;
	static GLUI_Rollout* ro_mouvements;
	static GLUI_Rollout* ro_fichiers;
	static GLUI_RadioGroup* rg_2d3d;
	static GLUI_RadioGroup* rg_spherepoint;
	static GLUI_RadioGroup* rg_camera;

	static int dummy_var1 = 0;
	static int dummy_var2 = 0;
	static int dummy_var3 = 0;
	static int dummy_var4 = 0;
	static int dummy_var5 = 0;

	static void glui_react(int RAF) {
		switch(RAF) {
			case 99 :	input_file(get->get_text());
				break;
			case 98 :	selectMenu(1);	//	collisions ON/OFF
				break;
			case 97 :	selectMenu(3);	//	2D <=> 3D
				break;
			case 96 :	selectMenu(4);	//	sphere <=> point
				break;
			case 95 :	G = 6.67430e-11;	//	reinit G
				break;
			case 94 :	selectMenu(8);	//	sphere <=> point
				break;
			case 93 :	selectMenu(9);	//	contrôle des distances ON/OFF
				break;
			case 92 :	output_file(get_outfile->get_text(), tbCorps);
				break;
			default : break;
		}
	}

	static void make_controlWindow(void) {
		glui_controlWindow = GLUI_Master.create_glui("Control", 0, largeur+15, 10);

		ro_mouvements = glui_controlWindow->add_rollout("Movement", true);
			glui_controlWindow->add_rotation_to_panel(ro_mouvements, "rotation", rotarray);
			glui_controlWindow->add_button_to_panel(ro_mouvements, "Inital position", 7, selectMenu);
			glui_controlWindow->add_column_to_panel(ro_mouvements);
			glui_controlWindow->add_translation_to_panel(ro_mouvements, "distance", GLUI_TRANSLATION_Z, &distance);
			glui_controlWindow->add_column_to_panel(ro_mouvements);
			glui_controlWindow->add_translation_to_panel(ro_mouvements, "Framework", GLUI_TRANSLATION_XY, transl);
			glui_controlWindow->add_button_to_panel(ro_mouvements, "view center", 11, selectMenu);
		ro_parametres = glui_controlWindow->add_rollout("param", true);
			sp_infos = glui_controlWindow->add_panel_to_panel(ro_parametres, "", GLUI_PANEL_NONE);
				(glui_controlWindow->add_edittext_to_panel(sp_infos, "FPS",	GLUI_EDITTEXT_FLOAT, &fps))->disable();
				(glui_controlWindow->add_edittext_to_panel(sp_infos, "Planet number", GLUI_EDITTEXT_INT, &nbC ))->disable();
				glui_controlWindow->add_checkbox_to_panel(sp_infos, "Collsion", &dummy_var1, 98, glui_react);
				glui_controlWindow->add_column_to_panel(sp_infos);
				(glui_controlWindow->add_edittext_to_panel(sp_infos, "Collision number", GLUI_EDITTEXT_INT, &nb_collide ))->disable();
				(glui_controlWindow->add_edittext_to_panel(sp_infos, "Disappear number", GLUI_EDITTEXT_INT, &nb_lost ))->disable();
				glui_controlWindow->add_checkbox_to_panel(sp_infos, "Disappear Control", &dummy_var5, 93, glui_react);
			sp_rb_reglages = glui_controlWindow->add_panel_to_panel(ro_parametres, "", GLUI_PANEL_NONE);
				rb_2d3d = glui_controlWindow->add_panel_to_panel(sp_rb_reglages, "diffusion");
					rg_2d3d = glui_controlWindow->add_radiogroup_to_panel(rb_2d3d, &dummy_var3, 97, glui_react);
						glui_controlWindow->add_radiobutton_to_group(rg_2d3d, "3D");
						glui_controlWindow->add_radiobutton_to_group(rg_2d3d, "2D");
				glui_controlWindow->add_column_to_panel(sp_rb_reglages);
				rb_spherepoint = glui_controlWindow->add_panel_to_panel(sp_rb_reglages, "draw");
					rg_spherepoint = glui_controlWindow->add_radiogroup_to_panel(rb_spherepoint, &dummy_var2, 96, glui_react);
						glui_controlWindow->add_radiobutton_to_group(rg_spherepoint, "sphere");
						glui_controlWindow->add_radiobutton_to_group(rg_spherepoint, "rectangle");
				glui_controlWindow->add_column_to_panel(sp_rb_reglages);
				rb_camera = glui_controlWindow->add_panel_to_panel(sp_rb_reglages, "camera");
					rg_camera = glui_controlWindow->add_radiogroup_to_panel(rb_camera, &dummy_var4, 94, glui_react);
						glui_controlWindow->add_radiobutton_to_group(rg_camera, "Fix");
						glui_controlWindow->add_radiobutton_to_group(rg_camera, "Rotate");
		ro_fichiers = glui_controlWindow->add_rollout("File", true);
			get = glui_controlWindow->add_edittext_to_panel(ro_fichiers, "File", GLUI_EDITTEXT_TEXT, fichier2);
			get->set_w(280);
			glui_controlWindow->add_button_to_panel(ro_fichiers, "Begin", 99, glui_react);
			get_outfile = glui_controlWindow->add_edittext_to_panel(ro_fichiers, "File", GLUI_EDITTEXT_TEXT, outfile);
			get_outfile->set_w(280);
			glui_controlWindow->add_button_to_panel(ro_fichiers, "Save", 92, glui_react);
		p_boutons = glui_controlWindow->add_panel("", GLUI_PANEL_NONE);
			glui_controlWindow->add_button_to_panel(p_boutons, "Pause", 2, selectMenu);
			glui_controlWindow->add_column_to_panel(p_boutons);
			glui_controlWindow->add_button_to_panel(p_boutons, "Exit", 0, selectMenu);

		glui_controlWindow->set_main_gfx_window(idF);
	}

	#endif
#endif
