#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

/*
00 01 02
10 11 12
20 21 22
*/
typedef struct s_sqmatrix3
{
	double	m_00;
	double 	m_01;
	double	m_02;
	double	m_10;
	double	m_11;
	double	m_12;
	double	m_20;
	double	m_21;
	double	m_22;
}t_sqmatrix3;

double vec3_dot(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
t_vec3 rotate_matrix(t_sqmatrix3 rotation_matrix, t_vec3 vec);
t_vec3 vec3_sum(t_vec3 a, t_vec3 b);
t_vec3 vec3_mul(t_vec3 a, double n);
t_vec3 vec3_normalize(t_vec3 a);


#endif