/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuhiro <kazuhiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:50:48 by kazuhiro          #+#    #+#             */
/*   Updated: 2024/06/10 14:11:57 by kazuhiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *str)
{
	int		byte;
	char	*buf;

	byte = 1;
	buf = malloc (BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (byte > 0)
	{
		byte = read(fd, buf, BUFFER_SIZE);
		if (byte < 0)
			return (free_str2(str, buf));
		buf[byte] = '\0';
		str = gnl_strcat(str, buf);
		if (!str)
			return (free_str2(str, buf));
		if (check_newline(buf))
			break ;
	}
	free(buf);
	return (str);
}

char	*get_file(int fd, char *next)
{
	static int	first = 1;
	char		*result;

	result = malloc(1);
	if (!result)
		return (NULL);
	*result = '\0';
	result = gnl_strcat(result, next);
	if (!first && check_newline(next))
		return (result);
	first = 0;
	result = read_file(fd, result);
	return (result);
}

char	*get_result(char *str)
{
	int		i;
	char	*result;

	i = 0;
	if (str[i] == '\0')
		return (free_str(str));
	while (str[i] != '\n' && str[i])
		i ++;
	result = malloc (i + 2);
	if (result == NULL)
		return (free_str(str));
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		result[i] = str[i];
		i ++;
	}
	if (str[i] == '\n')
	{
		result[i] = str[i];
		i ++;
	}
	result [i] = '\0';
	return (result);
}

void	get_next(char *next, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i ++;
	if (str[i] == '\n')
		i ++;
	while (str[i])
		next[j++] = str[i++];
	next[j] = '\0';
}

char	*get_next_line(int fd)
{
	char		*result;
	char		*str;
	static char	next[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = get_file(fd, next);
	if (!str)
		return (NULL);
	result = get_result(str);
	if (!result)
		return (NULL);
	get_next(next, str);
	free(str);
	return (result);
}

// int main ()
// {
// 	int	fd;
// 	char *s;
// 	system("clear");
// 	fd = open("test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		s = get_next_line(fd);
// 		if (!s)
// 			break;
// 		printf("%s", s);
// 		free(s);
// 	}
// 	close(fd);
// }