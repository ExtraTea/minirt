#include "../include/minirt.h"
#include "../include/vector.h"

double vec3_dot(t_vec3 a, t_vec3 b){
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b){
	t_vec3 ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_vec3 vec3_normalize(t_vec3 a){
	double l;
	t_vec3 ret;

	l = vec3_dot(a, a);
	ret.x = a.x / l;
	ret.y = a.y / l;
	ret.z = a.z / l;
	return (ret);	
}

t_vec3 vec3_cross(t_vec3 a, t_vec3 b){
	t_vec3 ret;

	ret.x = a.y * a.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}