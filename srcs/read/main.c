/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazokada <kazokada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:19:24 by kazuhiro          #+#    #+#             */
/*   Updated: 2024/06/12 17:11:06 by kazokada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../../include/read.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i ++;
	}
	free(arr);
}

void	free_light(t_light *light)
{
	t_light	*del;
	t_light	*tmp;

	del = light;
	while (del)
	{
		tmp = del->next;
		free(del);
		del = tmp;
	}
}

void	free_obj(t_obj	*obj)
{
	t_obj	*del;
	t_obj	*tmp;

	del = obj;
	while (del)
	{
		tmp = del->next;
		free(del->obj);
		free(del);
		del = tmp;
	}
}

void	free_env(t_environment *env)
{
	if (env->light)
		free_light(env->light);
	if (env->obj)
		free_obj(env->obj);
	if (env->cam)
		free(env->cam);
	if (env->ambient)
		free(env->ambient);
	free(env);
}

t_environment	*init_env(void)
{
	t_environment	*env;

	env = malloc (sizeof(t_environment));
	if (!env)
	{
		printf("malloc error\n");
		exit(1);
	}
	env->light = NULL;
	env->obj = NULL;
	env->ambient = NULL;
	env->cam = NULL;
	return (env);
}

t_environment	*str_env_str(t_environment *env, char *str)
{
	char	**arr;

	arr = ft_split(str, ' ');
	// printf("%s\n",arr[0]);
	if (strcmp("A", arr[0]) == 0)
		env = set_ambient(env, arr);
	else if (strcmp("C", arr[0]) == 0)
		env = set_camera(env, arr);
	else if (strcmp("L", arr[0]) == 0)
		env = set_light(env, arr);
	else if (strcmp("sp", arr[0]) == 0)
		env = set_sphere(env, arr);
	else if (strcmp("pl", arr[0]) == 0)
		env = set_plane(env, arr);
	else if (strcmp("cy", arr[0]) == 0)
		env = set_cylinder(env, arr);
	else
	{
		free_env(env);
		return (NULL);
	}
	free_arr(arr);
	return (env);
}

bool	file_name(char *str)
{
	size_t	size;

	size = ft_strlen(str);
	if (size <= 3)
		return (false);
	if (str[size - 1] == 't' && str[size - 2] == 'r' && str[size - 3] == '.')
		return (true);
	else
		return (false);
}

t_environment	*make_env_sub(char *file)
{
	int				fd;
	char			*str;
	t_environment	*env;

	fd = open(file, O_RDONLY);
	env = init_env();
	if (fd < 0 || env == NULL)
		return (NULL);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (*str == '\n')
			continue ;
		env = str_env_str(env, str);
		printf("%s", str);
		free(str);
		if (!env)
		{
			return (NULL);
		}
	}
	return (env);
}

t_environment	*make_env(char *str)
{
	t_environment	*env;

	if (file_name(str) == false)
		return (NULL);
	env = make_env_sub(str);
	if (!env)
		return (NULL);
	if (env->ambient == NULL || env->cam == NULL
		|| env->light == NULL || env->obj == NULL)
	{
		free_env(env);
		return (NULL);
	}
	return (env);
}

int	main(int ac, char **av)
{
	t_environment	*env;

	if (ac != 2)
	{
		write(2, "input correct arg\n", 19);
		return (1);
	}
	env = make_env(av[1]);
	if (!env)
	{
		write(2, "input correct file\n", 20);
		return (1);
	}
	print_env(env);
	free_env(env);
	return (0);
}
