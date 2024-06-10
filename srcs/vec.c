#include "../include/minirt.h"
#include "../include/vector.h"

// t_vec3 vec3_sub(t_vec3 a, t_vec3 b){
// 	t_vec3 ret;

// 	ret.x = a.x - b.x;
// 	ret.y = a.y - b.y;
// 	ret.z = a.z - b.z;
// 	return (ret);
// }

// t_vec3 vec3_normalize(t_vec3 a){
// 	double l;
// 	t_vec3 ret;

// 	l = sqrt(vec3_dot(a, a));
// 	ret.x = a.x / l;
// 	ret.y = a.y / l;
// 	ret.z = a.z / l;
// 	return (ret);	
// }

// double vec3_dot(t_vec3 a, t_vec3 b){
// 	return (a.x * b.x + a.y * b.y + a.z * b.z);
// }

// t_vec3 vec3_cross(t_vec3 a, t_vec3 b){
// 	t_vec3 ret;

// 	ret.x = a.y * b.z - a.z * b.y;
// 	ret.y = a.z * b.x - a.x * b.z;
// 	ret.z = a.x * a.y - a.y * b.x;
// 	return (ret);
// }

// t_sqmatrix3 vec3_get_rotation_matrix(t_vec3 x, t_vec3 y, t_vec3 z){
// 	t_sqmatrix3 ret;

// 	ret.m_00 = x.x;
// 	ret.m_01 = y.x;
// 	ret.m_02 = z.x;
// 	ret.m_10 = x.y;
// 	ret.m_11 = y.y;
// 	ret.m_12 = z.y;
// 	ret.m_20 = x.z;
// 	ret.m_21 = y.z;
// 	ret.m_22 = z.z;

// 	return (ret);
// }

// t_vec3 rotate_matrix(t_sqmatrix3 rotation_matrix, t_vec3 vec){
// 	t_vec3 ret;

// 	ret.x = rotation_matrix.m_00 * vec.x + rotation_matrix.m_01 * vec.y + rotation_matrix.m_02 * vec.z;
// 	ret.y = rotation_matrix.m_10 * vec.x + rotation_matrix.m_11 * vec.y + rotation_matrix.m_12 * vec.z;
// 	ret.z = rotation_matrix.m_20 * vec.x + rotation_matrix.m_21 * vec.y + rotation_matrix.m_22 * vec.z;

// 	return (ret);
// }