// COLUMN MAJOR!!!!!

#include "myLib.h"
#include <stdio.h>
#include <math.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

void print_v4(vec4 v) {
    printf("[ %7.4f %7.4f %7.4f %7.4f ]\n", v.x, v.y, v.z, v.w);
}

vec4 scalar_vec_mult(float s, vec4 v) {
    // scalar * vector
    vec4 s_v_multiplication;
    s_v_multiplication.x = s * v.x;
    s_v_multiplication.y = s * v.y;
    s_v_multiplication.z = s * v.z;
    s_v_multiplication.w = s * v.w;
    return s_v_multiplication;
}

vec4 vec_add(vec4 v1, vec4 v2) {
    // vector1 + vector2
    vec4 v_addition;
    v_addition.x = v1.x + v2.x;
    v_addition.y = v1.y + v2.y;
    v_addition.z = v1.z + v2.z;
    v_addition.w = v1.w + v2.w;
    return v_addition;
}

vec4 vec_sub(vec4 v1, vec4 v2) {
    // vector1 - vector2
    vec4 v_subtraction;
    v_subtraction.x = v1.x - v2.x;
    v_subtraction.y = v1.y - v2.y;
    v_subtraction.z = v1.z - v2.z;
    v_subtraction.w = v1.w - v2.w;
    return v_subtraction;
}

float magnitude(vec4 v) {
    // |v| = sqrt(x2 + y2 + z2 + w2)
    return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

vec4 normalize(float magnitude, vec4 v) {
    // 1/|v| * vector
    return scalar_vec_mult((1/magnitude), v);
}

float dot_prod(vec4 v1, vec4 v2) {
    // (x1 × x2) + (y1 × y2) + (z1 × z2) + (w1 × w2)
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

vec4 cross_prod(vec4 v1, vec4 v2) {
    // leave last elem as 0
    vec4 cross_prod_vec;
    cross_prod_vec.x = (v1.y * v2.z) - (v1.z * v2.y);
    cross_prod_vec.y = (v1.z * v2.x) - (v1.x * v2.z);
    cross_prod_vec.z = (v1.x * v2.y) - (v1.y * v2.x);
    cross_prod_vec.w = 0 * 0;
    return cross_prod_vec;
}

void print_m4(mat4 m) {
    printf("[ %7.4f %7.4f %7.4f %7.4f ]\n", m.x.x, m.y.x, m.z.x, m.w.x);
    printf("[ %7.4f %7.4f %7.4f %7.4f ]\n", m.x.y, m.y.y, m.z.y, m.w.y);
    printf("[ %7.4f %7.4f %7.4f %7.4f ]\n", m.x.z, m.y.z, m.z.z, m.w.z);
    printf("[ %7.4f %7.4f %7.4f %7.4f ]\n", m.x.w, m.y.w, m.z.w, m.w.w);
}

mat4 scalar_mat_mult(float s, mat4 m) {
    // scalar * matrix
    mat4 s_m_multiplication;
    s_m_multiplication.x = scalar_vec_mult(s, m.x);
    s_m_multiplication.y = scalar_vec_mult(s, m.y);
    s_m_multiplication.z = scalar_vec_mult(s, m.z);
    s_m_multiplication.w = scalar_vec_mult(s, m.w);
    return s_m_multiplication;
}

mat4 mat_add(mat4 m1, mat4 m2) {
    // matrix1 + matrix2
    mat4 m_addition;
    m_addition.x = vec_add(m1.x, m2.x);
    m_addition.y = vec_add(m1.y, m2.y);
    m_addition.z = vec_add(m1.z, m2.z);
    m_addition.w = vec_add(m1.w, m2.w);
    return m_addition;
}

mat4 mat_sub(mat4 m1, mat4 m2) {
    // matrix1 - matrix2
    mat4 m_subtraction;
    m_subtraction.x = vec_sub(m1.x, m2.x);
    m_subtraction.y = vec_sub(m1.y, m2.y);
    m_subtraction.z = vec_sub(m1.z, m2.z);
    m_subtraction.w = vec_sub(m1.w, m2.w);
    return m_subtraction;
}

mat4 mat_mult(mat4 m1, mat4 m2) {
    // matrix1 * matrix2
    mat4 m_multiplication;
    // col 1
    m_multiplication.x.x = (m1.x.x * m2.x.x) + (m1.y.x * m2.x.y) + (m1.z.x * m2.x.z) + (m1.w.x * m2.x.w);
    m_multiplication.x.y = (m1.x.y * m2.x.x) + (m1.y.y * m2.x.y) + (m1.z.y * m2.x.z) + (m1.w.y * m2.x.w);
    m_multiplication.x.z = (m1.x.z * m2.x.x) + (m1.y.z * m2.x.y) + (m1.z.z * m2.x.z) + (m1.w.z * m2.x.w);
    m_multiplication.x.w = (m1.x.w * m2.x.x) + (m1.y.w * m2.x.y) + (m1.z.w * m2.x.z) + (m1.w.w * m2.x.w);
    // col 2
    m_multiplication.y.x = (m1.x.x * m2.y.x) + (m1.y.x * m2.y.y) + (m1.z.x * m2.y.z) + (m1.w.x * m2.y.w);
    m_multiplication.y.y = (m1.x.y * m2.y.x) + (m1.y.y * m2.y.y) + (m1.z.y * m2.y.z) + (m1.w.y * m2.y.w);
    m_multiplication.y.z = (m1.x.z * m2.y.x) + (m1.y.z * m2.y.y) + (m1.z.z * m2.y.z) + (m1.w.z * m2.y.w);
    m_multiplication.y.w = (m1.x.w * m2.y.x) + (m1.y.w * m2.y.y) + (m1.z.w * m2.y.z) + (m1.w.w * m2.y.w);
    // col 3
    m_multiplication.z.x = (m1.x.x * m2.z.x) + (m1.y.x * m2.z.y) + (m1.z.x * m2.z.z) + (m1.w.x * m2.z.w);
    m_multiplication.z.y = (m1.x.y * m2.z.x) + (m1.y.y * m2.z.y) + (m1.z.y * m2.z.z) + (m1.w.y * m2.z.w);
    m_multiplication.z.z = (m1.x.z * m2.z.x) + (m1.y.z * m2.z.y) + (m1.z.z * m2.z.z) + (m1.w.z * m2.z.w);
    m_multiplication.z.w = (m1.x.w * m2.z.x) + (m1.y.w * m2.z.y) + (m1.z.w * m2.z.z) + (m1.w.w * m2.z.w);
    // col 4
    m_multiplication.w.x = (m1.x.x * m2.w.x) + (m1.y.x * m2.w.y) + (m1.z.x * m2.w.z) + (m1.w.x * m2.w.w);
    m_multiplication.w.y = (m1.x.y * m2.w.x) + (m1.y.y * m2.w.y) + (m1.z.y * m2.w.z) + (m1.w.y * m2.w.w);
    m_multiplication.w.z = (m1.x.z * m2.w.x) + (m1.y.z * m2.w.y) + (m1.z.z * m2.w.z) + (m1.w.z * m2.w.w);
    m_multiplication.w.w = (m1.x.w * m2.w.x) + (m1.y.w * m2.w.y) + (m1.z.w * m2.w.z) + (m1.w.w * m2.w.w);
    return m_multiplication;
}

mat4 transpose(mat4 m) {
    // row1 becomes col1, etc.
    mat4 transposed;
    // col 1
    transposed.x.x = m.x.x;
    transposed.x.y = m.y.x;
    transposed.x.z = m.z.x;
    transposed.x.w = m.w.x;
    // col 2
    transposed.y.x = m.x.y;
    transposed.y.y = m.y.y;
    transposed.y.z = m.z.y;
    transposed.y.w = m.w.y;
    // col 3
    transposed.z.x = m.x.z;
    transposed.z.y = m.y.z;
    transposed.z.z = m.z.z;
    transposed.z.w = m.w.z;
    // col 4
    transposed.w.x = m.x.w;
    transposed.w.y = m.y.w;
    transposed.w.z = m.z.w;
    transposed.w.w = m.w.w;
    return transposed;
}

vec4 mat_vec_mult(mat4 m, vec4 v) {
    // matrix * vector
    vec4 m_v_mult;
    m_v_mult.x = (m.x.x * v.x) + (m.y.x * v.y) + (m.z.x * v.z) + (m.w.x * v.w);
    m_v_mult.y = (m.x.y * v.x) + (m.y.y * v.y) + (m.z.y * v.z) + (m.w.y * v.w);
    m_v_mult.z = (m.x.z * v.x) + (m.y.z * v.y) + (m.z.z * v.z) + (m.w.z * v.w);
    m_v_mult.w = (m.x.w * v.x) + (m.y.w * v.y) + (m.z.w * v.z) + (m.w.w * v.w);
    return m_v_mult;
}

mat4 minor(mat4 m) {
    // matrix of minor is made up of determinants with row i and col j removed

    // how to find determinant of 3x3 matrix where row i and col j are removed: 
    // | a b c |
    // | d e f | = aei + bfg + cdh - gec - hfa - idb
    // | g h i | 

    mat4 m_minor;
    // col 1
    m_minor.x.x = (m.y.y * m.z.z * m.w.w) + (m.z.y * m.w.z * m.y.w) + (m.w.y * m.y.z * m.z.w) - (m.y.w * m.z.z * m.w.y) - (m.z.w * m.w.z * m.y.y) - (m.w.w * m.y.z * m.z.y);
    m_minor.x.y = (m.y.x * m.z.z * m.w.w) + (m.z.x * m.w.z * m.y.w) + (m.w.x * m.y.z * m.z.w) - (m.y.w * m.z.z * m.w.x) - (m.z.w * m.w.z * m.y.x) - (m.w.w * m.y.z * m.z.x);
    m_minor.x.z = (m.y.x * m.z.y * m.w.w) + (m.z.x * m.w.y * m.y.w) + (m.w.x * m.y.y * m.z.w) - (m.y.w * m.z.y * m.w.x) - (m.z.w * m.w.y * m.y.x) - (m.w.w * m.y.y * m.z.x);
    m_minor.x.w = (m.y.x * m.z.y * m.w.z) + (m.z.x * m.w.y * m.y.z) + (m.w.x * m.y.y * m.z.z) - (m.y.z * m.z.y * m.w.x) - (m.z.z * m.w.y * m.y.x) - (m.w.z * m.y.y * m.z.x);
    // col 2
    m_minor.y.x = (m.x.y * m.z.z * m.w.w) + (m.z.y * m.w.z * m.x.w) + (m.w.y * m.x.z * m.z.w) - (m.x.w * m.z.z * m.w.y) - (m.z.w * m.w.z * m.x.y) - (m.w.w * m.x.z * m.z.y);
    m_minor.y.y = (m.x.x * m.z.z * m.w.w) + (m.z.x * m.w.z * m.x.w) + (m.w.x * m.x.z * m.z.w) - (m.x.w * m.z.z * m.w.x) - (m.z.w * m.w.z * m.x.x) - (m.w.w * m.x.z * m.z.x);
    m_minor.y.z = (m.x.x * m.z.y * m.w.w) + (m.z.x * m.w.y * m.x.w) + (m.w.x * m.x.y * m.z.w) - (m.x.w * m.z.y * m.w.x) - (m.z.w * m.w.y * m.x.x) - (m.w.w * m.x.y * m.z.x);
    m_minor.y.w = (m.x.x * m.z.y * m.w.z) + (m.z.x * m.w.y * m.x.z) + (m.w.x * m.x.y * m.z.z) - (m.x.z * m.z.y * m.w.x) - (m.z.z * m.w.y * m.x.x) - (m.w.z * m.x.y * m.z.x);
    // col 3
    m_minor.z.x = (m.x.y * m.y.z * m.w.w) + (m.y.y * m.w.z * m.x.w) + (m.w.y * m.x.z * m.y.w) - (m.x.w * m.y.z * m.w.y) - (m.y.w * m.w.z * m.x.y) - (m.w.w * m.x.z * m.y.y);
    m_minor.z.y = (m.x.x * m.y.z * m.w.w) + (m.y.x * m.w.z * m.x.w) + (m.w.x * m.x.z * m.y.w) - (m.x.w * m.y.z * m.w.x) - (m.y.w * m.w.z * m.x.x) - (m.w.w * m.x.z * m.y.x);
    m_minor.z.z = (m.x.x * m.y.y * m.w.w) + (m.y.x * m.w.y * m.x.w) + (m.w.x * m.x.y * m.y.w) - (m.x.w * m.y.y * m.w.x) - (m.y.w * m.w.y * m.x.x) - (m.w.w * m.x.y * m.y.x);
    m_minor.z.w = (m.x.x * m.y.y * m.w.z) + (m.y.x * m.w.y * m.x.z) + (m.w.x * m.x.y * m.y.z) - (m.x.z * m.y.y * m.w.x) - (m.y.z * m.w.y * m.x.x) - (m.w.z * m.x.y * m.y.x);
    // col 4
    m_minor.w.x = (m.x.y * m.y.z * m.z.w) + (m.y.y * m.z.z * m.x.w) + (m.z.y * m.x.z * m.y.w) - (m.x.w * m.y.z * m.z.y) - (m.y.w * m.z.z * m.x.y) - (m.z.w * m.x.z * m.y.y);
    m_minor.w.y = (m.x.x * m.y.z * m.z.w) + (m.y.x * m.z.z * m.x.w) + (m.z.x * m.x.z * m.y.w) - (m.x.w * m.y.z * m.z.x) - (m.y.w * m.z.z * m.x.x) - (m.z.w * m.x.z * m.y.x);
    m_minor.w.z = (m.x.x * m.y.y * m.z.w) + (m.y.x * m.z.y * m.x.w) + (m.z.x * m.x.y * m.y.w) - (m.x.w * m.y.y * m.z.x) - (m.y.w * m.z.y * m.x.x) - (m.z.w * m.x.y * m.y.x);
    m_minor.w.w = (m.x.x * m.y.y * m.z.z) + (m.y.x * m.z.y * m.x.z) + (m.z.x * m.x.y * m.y.z) - (m.x.z * m.y.y * m.z.x) - (m.y.z * m.z.y * m.x.x) - (m.z.z * m.x.y * m.y.x);
    return m_minor;
}

mat4 cofactor(mat4 m) {
    // apply 4x4 checkerboard of minuses
    mat4 m_cofactor = m;
    // row 1
    m_cofactor.y.x = -m.y.x;
    m_cofactor.w.x = -m.w.x;
    // row 2
    m_cofactor.x.y = -m.x.y;
    m_cofactor.z.y = -m.z.y;
    // row 3
    m_cofactor.y.z = -m.y.z;
    m_cofactor.w.z = -m.w.z;
    // row 4
    m_cofactor.x.w = -m.x.w;
    m_cofactor.z.w = -m.z.w;
    return m_cofactor;
}

mat4 inverse(mat4 m) {
    // steps:
    // calculate matrix of minor of m
    // turn matrix of minor to matrix of cofactor
    // transpose matrix of cofactor
    // multiply result of transposed matrix by 1/(determinant of m)
    mat4 mat_of_minor = minor(m);
    mat4 mat_of_cofactor = cofactor(mat_of_minor);
    mat4 transposed = transpose(mat_of_cofactor);
    float m_det = (m.x.x * mat_of_minor.x.x) - (m.x.y * mat_of_minor.x.y) + (m.x.z * mat_of_minor.x.z) - (m.x.w * mat_of_minor.x.w);
    return scalar_mat_mult((1/m_det), transposed);
}

mat4 scale(float f1, float f2, float f3) {
    mat4 m = {
        {f1, 0.0, 0.0, 0.0},
        {0.0, f2, 0.0, 0.0},
        {0.0, 0.0, f3, 0.0}, 
        {0.0, 0.0, 0.0, 1.0}
    };
    return m;
}

mat4 translate(float f1, float f2, float f3) {
    mat4 m = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0}, 
        {f1, f2, f3, 1.0}
    };
    return m;
}

mat4 x_rotate(float d) {
    float r = d * M_PI / 180.0;
    mat4 m = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, (float)cos(r), -(float)sin(r), 0.0},
        {0.0, (float)sin(r), (float)cos(r), 0.0}, 
        {0.0, 0.0, 0.0, 1.0}
    };
    return m;
}

mat4 y_rotate(float d) {
    float r = d * M_PI / 180.0;
    mat4 m = {
        {(float)cos(r), 0.0, (float)sin(r), 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {-(float)sin(r), 0.0, (float)cos(r), 0.0}, 
        {0.0, 0.0, 0.0, 1.0}
    };
    return m;
}

mat4 z_rotate(float d) {
    float r = d * M_PI / 180.0;
    mat4 m = {
        {(float)cos(r), (float)sin(r), 0.0, 0.0},
        {(float)sin(r), (float)cos(r), 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0}, 
        {0.0, 0.0, 0.0, 1.0}
    };
    return m;
}

mat4 m4_identity() {
    mat4 m = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0}, 
        {0.0, 0.0, 0.0, 1.0}
    };
    return m;
}

