/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:08:52 by drecours          #+#    #+#             */
/*   Updated: 2018/04/07 04:34:30 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

int			resolve_relative_path(t_env **env, char *bin_path)
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

int			check_flag(int flag, char letter)
{
	if (letter == 'P')
		return (flag | 1);
	if (letter == 'L')
		return (flag | 2);
	ft_putstr_fd("cd: no such file or directory: -", 2);
	ft_putchar_fd(letter, 2);
	ft_putstr("\n");
	return (-1);
}

int			parse_flags(char **exec, int *index)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	while (exec[i] && exec[++i] && exec[i][0] == '-')
	{
		if (ft_strcmp(exec[i], "-") == 0 || ft_strcmp(exec[i], "--") == 0)
			break ;
		while (exec[i][++j])
			if ((flag = check_flag(flag, exec[i][j])) == -1)
				return (-1);
		j = 0;
	}
	if (!exec[i])
		return (flag);
	*index = (ft_strcmp(exec[i], "--") == 0) ? i + 1 : i;
	if (ft_strcmp(exec[i], "--") == 0 && exec[i + 1] && exec[i + 2])
		return (err_msg("cd: string not in pwd: ", exec[i + 1], -1));
	if (exec[i] && exec[i + 1])
		return (err_msg("cd: string not in pwd: ", exec[i], -1));
	return (flag);
}

int			fix_root(char *path)
{
	if (ft_strlen(path) == 0)
		path_subcpy("/", path, 0, 1);
	return (0);
}
