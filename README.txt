                         -= OpenGLavity =-

http://cycojesus.free.fr/progs/openglavity/index.htm

/***************************************************************************************/

Sommaire :
1. Copyright

2. Buts et principes
  2.1. But
  2.2. N-corps complet
  2.3. format du fichier d'entree

3. Utilisation
  3.1. Compilation
  3.2. Options de lancement
    3.2.1. Exemple
  3.3. GUI

4. Epilogue

/***************************************************************************************/

  1. Copyright
	Copyright (C) 2001, 2002 Gwenhael LE MOINE (cycojesus@yahoo.fr)
        	                 Michel SALVADORI

	OpenGLavity est fourni avec ABSOLUMENT AUCUNE GARANTIE; pour les
	details voir COPYING. Ceci est un logiciel libre, et vous �tes libre de le
	redistribuer sous certaines conditions, voir COPYING pour les details.

  2. Buts et principes
    2.1. But
			(plus tard)

    2.2. N-corps complet
			(plus tard)

    2.3. format du fichier d'entree
		Le contenu du fichier d'entree est on ne peu plus simple ;) :
		nombre de corps
			=>	| 10
				| 0.000000 0.000000 0.000000 6600000000.000000 1.000000 0.000000 0.000000 0.000000 0
				| -15.000000 0.000000 0.000000 6000000.000000 0.640000 0.000000 0.180000 0.180000 1
				| 9.521000 0.000000 0.000000 1.000000 0.340000 0.000000 -0.211653 0.000000 2
				| 12.446900 2.650000 0.633400 0.100000 0.340000 0.018467 -0.201553 0.000041 3
				| 12.986400 2.696200 2.935800 0.100000 0.340000 0.011478 -0.201453 0.015724 3
				| 11.546100 1.682700 2.328100 0.100000 0.340000 0.028145 -0.201353 0.005705 2
				| 11.103600 0.482700 1.194200 0.100000 0.340000 0.002995 -0.201253 0.000491 1
				| 10.599200 0.015300 0.390200 0.100000 0.340000 0.014604 -0.201153 0.032391 0
				| 12.569500 1.971800 1.871600 0.100000 0.340000 0.017421 -0.201053 0.012382 0
				| 10.776900 1.153800 1.477100 0.100000 0.340000 0.021726 -0.200953 0.005447 1
				    X		  Y			Z		M		D		  VX		VY		VZ		C
		X  : coordonnee du corps en X
		Y  : coordonnee du corps en Y
		Z  : coordonnee du corps en Z
		M  : masse du corps
		D  : diam�tre du corps
		VX : celerite du corps en X
		VY : celerite du corps en Y
		VZ : celerite du corps en Z
		C  : couleur du corps

  3. Utilisation
	il vous faudras glut ( http://www.opengl.org/developers/documentation/glut/index.html ) et �ventuellement glui ( http://www.cs.unc.edu/~rademach/glui/ )

	3.1. Compilation
		(sous windows, vous utilisez le projet MSVC++ 6 et puis vous vous d�brouillez avec :p)
		- editez le fichier config.h afin de fixer certaines options (GLUT & GLUI)
		- make
		- make run-gui pour voir si ca marche

	3.2. Options de lancement
		OpenGLavity [options]
			-v --version :
				 affiche le num�ro de version
			-h --help :
				 ce que vous etes en train de lire
			-i --input-file :
				 fichier (.unv) � ouvrir (indispensable)
			-o --output-file :
				 fichier (.unv) � (�ventuellement) �crire
			-t --duration :
				 fixer un temps d'�x�cution limit� en secondes
			-n --iterations :
				 fixer un nombre fini d'ut�rations � calculer
			-x --glut-interface :
				 lancer l'interface OpenGL
			-u --glui-interface :
				 lancer l'interface GLUI (-u implicite)
			-F --fullscreen :
				 lancer l'interface OpenGL en plein ecran (pas d'interface GLUI)
				 
		3.2.1. Exemple
			./OpenGLavity -i universes/good.unv -u

	3.3. GUI
		J'ai besoin d'expliquer �a ?! ;-)

  4. Epilogue
		(plus tard)
