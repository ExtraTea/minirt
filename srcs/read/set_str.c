/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazokada <kazokada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:10:14 by kazuhiro          #+#    #+#             */
/*   Updated: 2024/06/11 18:17:32 by kazokada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/read.h"

t_environment	*set_ambient(t_environment *env, char **arr)
{
	int			i;
	t_ambient	*amb;

	i = 0;
	while (arr[i])
		i ++;
	if (i != 3 || env->ambient)
	{
		free_env(env);
		return (NULL);
	}
	amb = malloc (sizeof (t_ambient));
	amb->ratio = ft_atod(arr[1]);
	amb->color = ato_rgb(arr[2]);
	env->ambient = amb;
	if (check_01(amb->ratio) == false || check_coler(amb->color) == false)
	{
		free_env(env);
		return (NULL);
	}
	return (env);
}

t_environment	*set_camera(t_environment *env, char **arr)
{
	int			i;
	t_camera	*camera;

	i = 0;
	while (arr[i])
		i ++;
	if (i != 4 || env->cam)
	{
		free_env(env);
		return (NULL);
	}
	camera = malloc(sizeof (t_camera));
	camera->pos = ato_vec3(arr[1]);
	camera->ori = ato_vec3(arr[2]);
	camera->fov = ato_fov(arr[3]);
	env->cam = camera;
	if (check_norm(camera->ori) == false || check_fov(camera->fov) == false)
	{
		free_env(env);
		return (NULL);
	}
	return (env);
}

t_environment	*set_light(t_environment *env, char **arr)
{
	int		i;
	t_light	*light;
	t_light	*tmp;

	i = 0;
	while (arr[i])
		i ++;
	if (i != 4)
	{
		free_env(env);
		return (NULL);
	}
	light = malloc (sizeof(t_light));
	light->pos = ato_vec3(arr[1]);
	light->ratio = ft_atod(arr[2]);
	light->color = ato_rgb(arr[3]);
	light->next = NULL;
	if (!env->light)
		env->light = light;
	else
	{
		tmp = env->light;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = light;
	}
	if (check_01(light->ratio) == false || check_coler(light->color) == false)
	{
		free_env(env);
		return (NULL);
	}
	return (env);
}

t_environment	*set_sphere(t_environment *env, char **arr)
{
	int			i;
	t_obj		*obj;
	t_obj		*tmp;
	t_sphere	*sp;

	i = 0;
	while (arr[i])
		i ++;
	if (i != 4)
	{
		free_env(env);
		return (NULL);
	}
	obj = malloc (sizeof(t_obj));
	sp = malloc (sizeof(t_sphere));
	sp->center = ato_vec3(arr[1]);
	sp->r = ft_atod(arr[2]);
	sp->color = ato_rgb(arr[3]);
	obj->obj = sp;
	obj->next = NULL;
	obj->type = 's';
	if (!env->obj)
		env->obj = obj;
	else
	{
		tmp = env->obj;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = obj;
	}
	if (check_coler(sp->color) == false)
	{
		free_env(env);
		return (NULL);
	}
	return (env);
}

t_environment	*set_plane(t_environment *env, char **arr)
{
	int		i;
	t_obj	*obj;
	t_obj	*tmp;
	t_plane	*pl;

	i = 0;
	while (arr[i])
		i ++;
	if (i != 4)
	{
		free_env(env);
		return (NULL);
	}
	obj = malloc(sizeof(t_obj));
	pl = malloc(sizeof(t_plane));
	pl->point = ato_vec3(arr[1]);
	pl->norm = ato_vec3(arr[2]);
	pl->color = ato_rgb(arr[3]);
	obj->obj = pl;
	obj->type = 'p';
	obj->next = NULL;
	if (!env->obj)
		env->obj = obj;
	else
	{
		tmp = env->obj;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = obj;
	}
	if (check_norm(pl->norm) == false || check_coler(pl->color) == false)
	{
		free_env(env);
		return (NULL);
	}
	return (env);
}

t_environment	*set_cylinder(t_environment *env, char **arr)
{
	int			i;
	t_cylinder	*cy;
	t_obj		*obj;
	t_obj		*tmp;

	i = 0;
	while (arr[i])
		i ++;
	if (i != 6)
	{
		free_env(env);
		return (NULL);
	}
	cy = malloc(sizeof(t_cylinder));
	obj = malloc(sizeof(t_obj));
	cy->center = ato_vec3(arr[1]);
	cy->axis = ato_vec3(arr[2]);
	cy->diameter = ft_atod(arr[3]);
	cy->height = ft_atod(arr[4]);
	cy->color = ato_rgb(arr[5]);
	obj->type = 'c';
	obj->obj = cy;
	obj->next = NULL;
	if (!env->obj)
		env->obj = obj;
	else
	{
		tmp = env->obj;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = obj;
	}
	if (check_coler(cy->color) == false || check_norm(cy->axis) == false)
	{
		free_env(env);
		return (NULL);
	}
	return (env);
}
