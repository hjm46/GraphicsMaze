# OPTIONS = -framework GLUT -framework OpenGL
# DEFINES = -D GL_SILENCE_DEPRECATION
LIBS = -lXi -lXmu -lglut -lGLEW -lGLU -lm -lGL

template: project02.c initShader.o myLib.o
	gcc -o project02 project02.c initShader.o myLib.o $(LIBS)

initShader.o: initShader.c initShader.h
	gcc -c initShader.c

tempLib.o: myLib.h myLib.c
	gcc -c myLib.c
