/*
 * project02.c
 *
 *  Created on: September 10, 2024
 *      Author: Thumrongsak Kosiyatrakul
 */


#ifdef __APPLE__  // include Mac OS X verions of headers

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#else // non-Mac OS X operating systems

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

#endif  // __APPLE__

#include "initShader.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <float.h>

#include "myLib.h" // replace this with your library

int num_vertices = 36;
GLuint ctm_location;
mat4 curr_trans_matrix = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
GLuint model_view_location;
mat4 model_view = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
GLuint projection_location;
mat4 projection = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

void init(void)
{
    GLuint program = initShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    vec4 *positions = (vec4 *) malloc(sizeof(vec4) * num_vertices);

    // creating one cube
    positions[0] = (vec4) { 0.15,  0.15, 0.15, 1.0};
    positions[1] = (vec4) {-0.15,  0.15, 0.15, 1.0};
    positions[2] = (vec4) { 0.15, -0.15, 0.15, 1.0};
    positions[3] = (vec4) { 0.15, -0.15, 0.15, 1.0};
    positions[4] = (vec4) {-0.15,  0.15, 0.15, 1.0};
    positions[5] = (vec4) {-0.15, -0.15, 0.15, 1.0};

    positions[6] = (vec4) { 0.15, -0.15, -0.15, 1.0};
    positions[7] = (vec4) {-0.15, -0.15, -0.15, 1.0};
    positions[8] = (vec4) { 0.15,  0.15, -0.15, 1.0};
    positions[9] = (vec4) { 0.15,  0.15, -0.15, 1.0};
    positions[10] = (vec4){-0.15, -0.15, -0.15, 1.0};
    positions[11] = (vec4){-0.15,  0.15, -0.15, 1.0};

    positions[12] = (vec4) {-0.15, -0.15,  0.15, 1.0};
    positions[13] = (vec4) {-0.15, -0.15, -0.15, 1.0};
    positions[14] = (vec4) { 0.15, -0.15,  0.15, 1.0};
    positions[15] = (vec4) { 0.15, -0.15,  0.15, 1.0};
    positions[16] = (vec4) {-0.15, -0.15, -0.15, 1.0};
    positions[17] = (vec4) { 0.15, -0.15, -0.15, 1.0};

    positions[18] = (vec4) {-0.15,  0.15,  0.15, 1.0};
    positions[19] = (vec4) {-0.15,  0.15, -0.15, 1.0};
    positions[20] = (vec4) {-0.15, -0.15,  0.15, 1.0};
    positions[21] = (vec4) {-0.15, -0.15,  0.15, 1.0};
    positions[22] = (vec4) {-0.15,  0.15, -0.15, 1.0};
    positions[23] = (vec4) {-0.15, -0.15, -0.15, 1.0};

    positions[24] = (vec4) { 0.15, 0.15,  0.15, 1.0};
    positions[25] = (vec4) { 0.15, 0.15, -0.15, 1.0};
    positions[26] = (vec4) {-0.15, 0.15,  0.15, 1.0};
    positions[27] = (vec4) {-0.15, 0.15,  0.15, 1.0};
    positions[28] = (vec4) { 0.15, 0.15, -0.15, 1.0};
    positions[29] = (vec4) {-0.15, 0.15, -0.15, 1.0};

    positions[30] = (vec4) { 0.15, -0.15,  0.15, 1.0};
    positions[31] = (vec4) { 0.15, -0.15, -0.15, 1.0};
    positions[32] = (vec4) { 0.15,  0.15,  0.15, 1.0};
    positions[33] = (vec4) { 0.15,  0.15,  0.15, 1.0};
    positions[34] = (vec4) { 0.15, -0.15, -0.15, 1.0};
    positions[35] = (vec4) { 0.15,  0.15, -0.15, 1.0};

    // TO-DOs: (Daisy)
    // create upside-down pyramid w/ textures
    // need to randomly remove/add cubes later

    

    // define texture coords for square
    vec2 *tex_coords = (vec2 *) malloc(sizeof(vec2) * num_vertices);
    
    // first row of blocks has grass (top), grass (side), and dirt
    // rest will be just dirt
    // top: grass
    tex_coords[0] = (vec2) {0.0, 0.25};
    tex_coords[1] = (vec2) {0.0, 0.0};
    tex_coords[2] = (vec2) {0.25, 0.25};
    tex_coords[3] = (vec2) {0.25, 0.25};
    tex_coords[4] = (vec2) {0.0, 0.0};
    tex_coords[5] = (vec2) {0.0, 0.25};

    // bottom: dirt
    tex_coords[6] = (vec2) {0.75, 1.00};
    tex_coords[7] = (vec2) {0.75, 0.75};
    tex_coords[8] = (vec2) {1.00, 1.00};
    tex_coords[9] = (vec2) {1.00, 1.00};
    tex_coords[10] = (vec2){0.75, 0.75};
    tex_coords[11] = (vec2){0.75, 1.00};

    // sides: dirt + grass
    for (int i = 0; i < 24; i += 6){
        tex_coords[i + 12] = (vec2) {0.50, 0.75};
        tex_coords[i + 13] = (vec2) {0.50, 1.00};
        tex_coords[i + 14] = (vec2) {0.75, 0.75};
        tex_coords[i + 15] = (vec2) {0.75, 0.75};
        tex_coords[i + 16] = (vec2) {0.50, 1.00};
        tex_coords[i + 17] = (vec2) {0.75, 1.00};
    }


    // create array of texels, open texture file, and fill array with data
    int tex_width = 64;
    int tex_height = 64;
    GLubyte my_texels[tex_width][tex_height][3];

    FILE *fp = fopen("textures02.raw", "r");
    fread(my_texels, tex_width * tex_height * 3, 1, fp);
    fclose(fp);

    // parameters for texture mapping
    GLuint mytex[1];
    glGenTextures(1, mytex);
    glBindTexture(GL_TEXTURE_2D, mytex[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, my_texels);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    
    int param;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &param);

    GLuint vao;
    glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArrayAPPLE(vao);

    // allocating and transfering data to graphic card
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * num_vertices + sizeof(vec2) * num_vertices, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec4) * num_vertices, positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4) * num_vertices, sizeof(vec2) * num_vertices, tex_coords);

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (0));

    GLuint vTexCoord = glGetAttribLocation(program, "vTexCoord");
    glEnableVertexAttribArray(vTexCoord);
    glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (sizeof(vec4) * num_vertices));
    
    ctm_location = glGetUniformLocation(program, "ctm");
    model_view_location = glGetUniformLocation(program, "model_view");
    projection_location = glGetUniformLocation(program, "projection");

    GLuint texture_location = glGetUniformLocation(program, "texture");
    glUniform1i(texture_location, 0);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1,0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glPolygonMode(GL_FRONT, GL_FILL);
    // glPolygonMode(GL_BACK, GL_LINE);

    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &curr_trans_matrix);
    glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *) &model_view);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *) &projection);
    
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int mousex, int mousey)
{
    //printf("%c %i %i ", key, mousex, mousey);
    if(key == 'q')
    	exit(0);
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        
    }

    glutPostRedisplay();
}

void motion(int x, int y)
{
    
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Project 2/3");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();

    return 0;
}
