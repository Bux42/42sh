/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:31:55 by drecours          #+#    #+#             */
/*   Updated: 2018/01/29 14:02:35 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

static char		**dir_create(const char *path)
{
	char	**dirs;
	char	new_path[2048];
	size_t	i;
	size_t	len;

	i = 0;
	if (path[0] == '/')
		new_path[i++] = ' ';
	len = ft_strlen(path);
	path_subcpy(path, new_path + i, 0, len);
	dirs = ft_strsplit(new_path, '/');
	return (dirs);
}

static int		dir_del(char **dir_list, size_t i)
{
	if (dir_list[i] != NULL)
		dir_list[i][0] = '\0';
	return (0);
}

static void		dir_eval(char **dir_list)
{
	int		i;
	int		j;

	i = -1;
	while (dir_list[++i] != NULL)
	{
		if (ft_strcmp(dir_list[i], ".") == 0)
			dir_del(dir_list, i);
		if (ft_strcmp(dir_list[i], "..") == 0 && ((j = i) != -1))
		{
			while (j != 0 && --j > 0)
				if (ft_strlen(dir_list[j]) != 0 && dir_del(dir_list, j) == 0)
					break ;
			dir_del(dir_list, i);
		}
		j = 0;
		if (ft_strcmp(dir_list[i], "~") == 0)
			while (j != i)
			{
				dir_del(dir_list, j);
				++j;
			}
		if (ft_strcmp(dir_list[i], " ") == 0)
			dir_list[i][0] = '/';
	}
}

static int		dir_join(char **dir, char *path_str)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	path_str[0] = '\0';
	while (dir[i] != NULL)
	{
		len = ft_strlen(dir[i]);
		if (dir[i][0] != '\0')
		{
			j += path_subcpy(dir[i], path_str + j, 0, len);
			if (dir[i + 1] != NULL)
				j += path_subcpy("/", path_str + j, 0, 1);
		}
		free(dir[i]);
		++i;
	}
	free(dir);
	len = ft_strlen(path_str);
	path_trim(path_str, len);
	return (ft_strlen(path_str));
}

int				path_eval(char *path)
{
	char	**dirs;

	dirs = dir_create(path);
	dir_eval(dirs);
	dir_join(dirs, path);
	if (ft_strncmp(path, "//", 2) == 0)
		path_subcpy(path + 1, path, 0, ft_strlen(path) - 1);
	return (ft_strlen(path));
}
