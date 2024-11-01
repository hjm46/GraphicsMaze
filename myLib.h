#ifndef _MYLIB_H_

#define _MYLIB_H_

typedef struct {
    float x;
    float y;
    float z;
    float w;
} vec4;

typedef struct {
    vec4 x;
    vec4 y;
    vec4 z;
    vec4 w;
} mat4;

typedef struct {
    float x;
    float y;
} vec2;

// Insert function signatures after this line

void print_v4(vec4);
vec4 scalar_vec_mult(float, vec4);
vec4 vec_add(vec4, vec4);
vec4 vec_sub(vec4, vec4);
float magnitude(vec4);
vec4 normalize(float, vec4);
float dot_prod(vec4, vec4);
vec4 cross_prod(vec4, vec4);

void print_m4(mat4);
mat4 scalar_mat_mult(float, mat4);
mat4 mat_add(mat4, mat4);
mat4 mat_sub(mat4, mat4);
mat4 mat_mult(mat4, mat4);
mat4 inverse(mat4);
mat4 transpose(mat4);
vec4 mat_vec_mult(mat4, vec4);

mat4 scale(float, float, float);
mat4 translate(float, float, float);
mat4 x_rotate(float);
mat4 y_rotate(float);
mat4 z_rotate(float);

mat4 m4_identity();

// Do not put anything after this line

#endif
