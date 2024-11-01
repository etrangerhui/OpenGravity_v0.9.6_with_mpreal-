CC=gcc-2.96
#CC=gcc #3.0.2
CCLIBS= -lstdc++-3-libc6.2-2-2.10.0 -lpthread -L/usr/X11R6/lib -lGL -lGLU -lglut -lglui
CCINC= -I/usr/X11R6/include/GL/
CCOPTIMISATION=-O3 -march=athlon -fexpensive-optimizations

all:
	$(MAKE) OpenGLavity

OpenGLavity: main.cpp grav.h es.h glutstuff.h parseargs.h globalvars.h gluistuff.h config.h
	@$(CC) -o $@ $< $(CCLIBS) $(CCINC) $(CCOPTIMISATION)
	@echo ./OpenGLavity pour lancer le programme
	@echo il serais judicieux de lire le README

clean:
	@rm -f *~

real-clean:
	$(MAKE) clean
	@rm -f OpenGLavity

run-gui:
	./OpenGLavity -i universes/good.unv -x -u

run-bench-time:
	./OpenGLavity -i universes/good.unv -x -t 100

run-bench-iter:
	./OpenGLavity -i universes/good.unv -n 100

archive:
		echo $(join $(subst $(space),"_",$(shell pwd)),".tar.bz2")
		$(MAKE) clean
		tar jcvf $(join $(shell pwd),".tar.bz2") ./