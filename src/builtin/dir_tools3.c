/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:08:52 by drecours          #+#    #+#             */
/*   Updated: 2018/03/12 15:13:53 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

int				resolve_relative_path(t_env **env, char *bin_path)
{
	char correct_path[2048];
	char *home;

	path_subcpy(bin_path, correct_path, 0, ft_strlen(bin_path));
	if (ft_strlen(bin_path) > 1 &&
			bin_path[0] == '.' && bin_path[1] == '/')
		path_subcpy(bin_path + 2, correct_path,
				0, ft_strlen(bin_path) - 2);
	if (!(home = get_specific_env("HOME=", env)))
		return (-1);
	if (bin_path[0] == '~')
	{
		path_subcpy(home, correct_path, 0, ft_strlen(home));
		path_subcpy(bin_path + 1, correct_path + ft_strlen(home),
				0, ft_strlen(bin_path) - 1);
	}
	path_subcpy(correct_path, bin_path, 0, ft_strlen(correct_path));
	free(home);
	return (0);
}

char		*path_join(const char *path, const char *bin)
{
	char	*path_part;
	char	*path_full;
	size_t	path_size;

	path_size = ft_strlen(path);
	if (path[path_size] != '/')
		path_part = ft_strjoin(path, "/");
	else
		path_part = ft_strdup(path);
	path_full = ft_strjoin(path_part, bin);
	free(path_part);
	return (path_full);
}
