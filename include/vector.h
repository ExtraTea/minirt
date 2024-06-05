#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec3{
	double x;
	double y;
	double z;
}t_vec3;

typedef struct s_rgb{
	int r;
	int g;
	int b;
}t_rgb;

double vec3_dot(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);

#endif