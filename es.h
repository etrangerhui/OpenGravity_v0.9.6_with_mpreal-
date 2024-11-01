/*
 *  es.h : g鑢e les entr閑s/sorties
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

#ifndef ES_H
#define ES_H
#define sq(n) ((n)*(n))
//	fonctions
	//	fonction d'initialisation
	static void initCorps(char* X,
					  char* Y,
					  char* Z,
					  char* M,
					  char* D,
					  char* VX,
					  char* VY,
					  char* VZ,
					  int Color,
					  TypCorps* C)
{
	C->X =mpreal(X);
	C->Y = mpreal(Y);
	C->Z =mpreal( Z);
	C->M =mpreal( M);
	C->D = atof(D);
	C->VX = mpreal(VX);
	C->VY =mpreal( VY);
	C->VZ = mpreal(VZ);

	C->Couleur = Color;
}
#define NLINE 409600
#define LEN 40960
	static int input_file(char* nom_fichier) {
		int i;
		int err;
		int color = 0;
		long precise=200;
		char tbP[8][LEN];
		char name[LEN],line[NLINE];
		FILE *fp;
		
		fopen_s(&fp,nom_fichier, "r");
		if ( fp  == NULL)
		{
			fprintf(stderr, "Error opening file %s.\n", nom_fichier);
			exit(-1);
		}
		fgets(line,NLINE,fp);
		err = sscanf(line, "%d %ld\n", &nbC,&precise);

		if (err != 2)precise=200;
		if (err == EOF)fprintf(stderr, "错误，意外的文件结尾e");
			
		tbCorps = new TypCorps[nbC];
		mpreal::set_default_prec(mpfr::digits2bits(precise));
		for (i=0 ; i<nbC ; i++) {
			fgets(line,NLINE,fp);
			err = sscanf(line, "%s %s %s %s %s %s %s %s %li %s", (tbP[0]), (tbP[1]), (tbP[2]), (tbP[3]), (tbP[4]), (tbP[5]), (tbP[6]), (tbP[7]), &color,name);
			//if (err != 10)fprintf(stderr, "接收到的参数数量错误\n\tFound only %i\n", err);
				
			if (err == EOF)fprintf(stderr, "错误，意外的文件结尾");
				
			initCorps(tbP[0], tbP[1], tbP[2], tbP[3], tbP[4], tbP[5], tbP[6], tbP[7], color, &(tbCorps[i]));
		}
		fclose(fp);
		//tbCorps[2].Y=sqrt(mpreal(3.0))/2*1.e5;
		//tbCorps[1].VY=4/sqrt(0.25+mpreal(3.0)/36);
		//tbCorps[0].VY=-tbCorps[1].VY;


		return(0);
	}

	//閏rit le fichier de param鑤res
	static int output_file(char* fich, TypCorps* tb) {
		int i,j;
		FILE *fp;
		if ( (fp = fopen(fich, "w+")) == NULL)
		{
			fprintf(stderr, "Error opening file %s.\n", fich);
			return(-1);
		}
		 
		//donn閑s pr閞equises dans tous les modes
		fprintf(fp, "%d %d\n", nbC,COUNT);
		//fin pr閞equis
		for (i=0,j=(i+nbC+1)%nbC ; i<nbC ; i++,j=(i+nbC+1)%nbC )
		{
			mpreal v=sqrt(sq(tb[i].VX)+ sq(tb[i].VY)+ sq(tb[i].VZ));
			mpreal dx=tb[i].X-tb[j].X; 
			mpreal dy=tb[i].Y-tb[j].Y;
			mpreal dz=tb[i].Z-tb[j].Z;
			mpreal d=sqrt(sq(tb[i].X-tb[j].X)+ sq(tb[i].Y-tb[j].Y)+ sq(tb[i].Z-tb[j].Z));
			//mpreal d=sqrt(sq(tb[j].X));
			fprintf(fp, "%s %s %s %s %lf %s %s %s %i %s %s\n", (tb[i].X).toString().c_str(), (tb[i].Y).toString().c_str(), (tb[i].Z).toString().c_str(),
			(tb[i].M).toString().c_str(), tb[i].D,(tb[i].VX).toString().c_str(), (tb[i].VY).toString().c_str(), (tb[i].VZ).toString().c_str(),
			 tb[i].Couleur, (v).toString().c_str(),(d).toString().c_str()/*, tb[i].Texture*/);
		}
		fclose(fp);

		return(0);
	}

	static void reload_fichier(char* file) {
		int err;
		err = input_file(file);
		if (err < 0) {
			fprintf(stderr, "Erreur relecture fichier: %s", file);
		}
	}

	//	demande la saisie des corps "en manuel"
	static void input_byHand(TypCorps* tb) {
		int i;
		fprintf(stdout, "\n\nnombre de Corps : ");	scanf("%i", &nbC);
		tb = (TypCorps*) malloc(nbC * sizeof(TypCorps));

		for (i=0 ; i<nbC ; i++) {
			fprintf(stdout, "Corps %i\n", i+1);
			fprintf(stdout, "X : ");	scanf("%f", &(tb[i].X));
			fprintf(stdout, "Y : ");	scanf("%f", &(tb[i].Y));
			fprintf(stdout, "Z : ");	scanf("%f", &(tb[i].Z));
			fprintf(stdout, "M : ");	scanf("%f", &(tb[i].M));
			fprintf(stdout, "VX : ");	scanf("%f", &(tb[i].VX));
			fprintf(stdout, "VY : ");	scanf("%f", &(tb[i].VY));
			fprintf(stdout, "VZ : ");	scanf("%f", &(tb[i].VZ));
			fprintf(stdout, "\n");
		}
	}

	//	affiche les corps sur stdout
	static void output_stdout(int nbC, TypCorps* tb) {
		int i;
		for (i=0 ; i<nbC ; i++) {
			fprintf(stdout, "corps %i\n", i+1);
			fprintf(stdout, "X : %10.10f\n", tb[i].X);
			fprintf(stdout, "Y : %10.10f\n", tb[i].Y);
			fprintf(stdout, "Z : %10.10f\n", tb[i].Z);
			fprintf(stdout, "M : %10.10f\n", tb[i].M);
			fprintf(stdout, "D : %10.10f\n", tb[i].D);
			fprintf(stdout, "VX : %10.10f\n", tb[i].VX);
			fprintf(stdout, "VY : %10.10f\n", tb[i].VY);
			fprintf(stdout, "VZ : %10.10f\n", tb[i].VZ);
			fprintf(stdout, "\n");
		}
	}

	static int askAndLoadFile(void) {
		char filename[256];
		fprintf(stdout, "\nNom du ficher : ");
		scanf("%s", filename);
		fprintf(stdout, "\n%s\n", filename);
		return(input_file(filename));
	}

#endif
