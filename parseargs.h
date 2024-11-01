/*
 *  parseargs.h : groups ce qui concerne le traitement des paramètres passés en ligne de commande
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

#ifndef PARSEARGS_H
#define PARSEARGS_H 0

#ifdef unix
	#include <getopt.h>
#endif
#ifdef WIN32
	#include "getopt.h"
#endif
#include <string.h>

#define TITRE "OpenGLavity v0.9.6 Fr"

static Typ_interrupteur glui_onoff = OFF;
static Typ_interrupteur grafx_onoff = OFF;
static Typ_interrupteur fullscreen_onoff = OFF;

static int NB_ITER_NOGRAFX = 1;



static int go_parse(int argc, char* argv[]) {
		int option_index;
		char c = '?';
        double gg;
		char* optstring = "vhuxFn:i:o:t:";
		static struct option long_options[] =
		{
				{"version",			no_argument,		NULL, 'v'},
				{"help",			no_argument,		NULL, 'h'},
				{"glui-interface",	no_argument,		NULL, 'u'},
				{"glut-interface",	no_argument,		NULL, 'x'},
				{"fullscreen",		no_argument,		NULL, 'F'},
				{"iterations",		required_argument,	NULL, 'n'},
				{"input-file",		required_argument,	NULL, 'i'},
				{"output-file",		required_argument,	NULL, 'o'},
				{"duration",		required_argument,	NULL, 't'},
				{0, 0, 0, 0}
		};

		char* help_text = "OpenGLavity [options]\n\
\t-v --version :\n\t\t affiche le numéro de version\n\
\t-h --help :\n\t\t ce que vous etes en train de lire\n\
\t-i --input-file :\n\t\t fichier (.unv) ?ouvrir (indispensable)\n\
\t-o --output-file :\n\t\t fichier (.unv) ?(éventuellement) écrire\n\
\t-t --duration :\n\t\t fixer un temps d'éxécution limit?en secondes\n\
\t-n --iterations :\n\t\t fixer un nombre fini d'utérations ?calculer\n\
\t-x --glut-interface :\n\t\t lancer l'interface OpenGL\n\
\t-u --glui-interface :\n\t\t lancer l'interface GLUI (-u implicite)\n\
\t-F --fullscreen :\n\t\t lancer l'interface OpenGL en plein ecran (pas d'interface GLUI)\n\n";\

		if (argc == 1) {
				fprintf(stdout, "OpenGLavity : Les arguments sont manquants.\nPour en savoir davantage, faites: `OpenGLavity --help'.\n");
				exit(-1);
		}


		while(c != EOF) {
				c = getopt_long(argc, argv, optstring, long_options, &option_index);

				switch(c) {
						case 'v' :
								fprintf(stdout, "%s\n\n", TITRE);
								exit(0);
								break;
						case 'h' :
								fprintf(stdout, "%s", help_text);
								exit(0);
								break;
						case 'i' :
								fichier = (char*)malloc(strlen(optarg)*sizeof(char));
								fichier2 = (char*)malloc(strlen(optarg)*sizeof(char));
								strcpy(fichier, optarg);
								strcpy(fichier2, fichier);
								input_file(fichier);
								break;
						case 'o' :
								outfile = (char*)malloc(strlen(optarg)*sizeof(char));
								strcpy(outfile, optarg);
								break;
						case 't' :
								deadline_bench = atof(optarg);
								break;
						case 'n' :
							    gg=atof(optarg);
								if (gg < 0){LOOP=-gg;if(LOOP<1){LOOP=-1/gg;FACT=-1/gg;};}else {FACT=gg;}
								break;
						case 'x' :
								grafx_onoff = ON;
								break;
						case 'F' :
								fullscreen_onoff = ON;
								glui_onoff = OFF;
								break;
						case 'u' :
								grafx_onoff = ON;
								glui_onoff = ON;
								break;
						case '?' :
						case ':' :
								quitter(0);
								break;
						default : break;
				}
		}

		if (optind < argc) {
				printf ("Arguments ne constituant pas des options: ");
				while (optind < argc)
						printf ("%s ", argv[optind++]);
				printf ("\n");
		}

		return(optind);
}

#endif
