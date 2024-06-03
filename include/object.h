#ifndef OBJECT_H
# define OBJECT_H

#include "vector.h"

/*
平面のベクトル方程式
a(x - p) + b(y - q) + c(z - r) = 0
x = p, y = q, z = r を通る、法線ベクトル(a, b, c)を持つ平面
*/
typedef struct s_plane{
	t_vec3	point;
	t_vec3	norm;
	t_rgb	color;
}t_plane;

/*
球のベクトル方程式
(x - a)^2 + (y - b)^2 + (z - c)^2 = r^2;
中心(a, b, c)、半径rの球
*/
typedef struct t_sphere{
	t_vec3	center;
	double r;
	t_rgb color;
}t_sphere;

#endif