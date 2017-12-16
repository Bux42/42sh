/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 06:48:58 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/16 14:18:31 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			check_flag(int flag, char letter)
{
	if (letter == 'P')
		return (flag | 1);
	if (letter == 'L')
		return (flag | 2);
	ft_putstr("cd: no such file or directory: -");
	ft_putchar(letter);
	custom_return();
	return (-1);
}

int			parse_flags(char **exec, int *index)
{
	int		i;
	int		j;
	int		k;
	int		tir;
	int		file;

	i = 0;
	j = 0;
	file = 0;
	while (exec[++j])
	{
		k = -1;
		tir = 0;
		if (exec[j][0] != '-')
		{
			if (file + 1 > 1)
				return (err_msg("cd: string not in pwd: ", exec[1], -1));
			else
				file++;
		}
		while (exec[j][++k])
		{
			if (exec[j][k] == '-')
			{
				if (file)
					return (err_msg("cd: string not in pwd: ", exec[1], -1));
				if (tir)
					return (-1);
				else
					tir++;
				(*index)++;
			}
			else
				if (tir && (i = check_flag(i, exec[j][k])) == -1)
					return (-1);
		}
	}
	return (i);
}

int			custom_chdir(char *path, int flag)
{
	struct stat		st;
	int				rights;

	rights = 0;
	if ((lstat(path, &st)) == -1)
		return (err_msg("cd: no such file or directory: ", path, -1));
	else
	{
		if (!(S_ISDIR(st.st_mode)) && !(S_ISLNK(st.st_mode)))
			return (err_msg("cd: not a directory: ", path, -1));
		else
		{
			rights += (st.st_mode & S_IRUSR) ? 1 : 0;
			rights += (st.st_mode & S_IWUSR) ? 1 : 0;
			rights += (st.st_mode & S_IXUSR) ? 1 : 0;
			if (!rights)
				return (err_msg("cd: permission denied: ", path, -1));
			else
			{
				if (flag & 2)
					;
				if (chdir(path) == -1)
					return (err_msg("wtf have you done :", path, -1));
			}
		}
	}
	return (1);
}

int			change_dir(char **exec, t_env **env)
{
	int		flag;
	int		index;
	char	*home;

	index = 1;
	if ((flag = parse_flags(exec, &index)) == -1)
		return (-1);
	if (!exec[index])
	{
		if ((home = get_specific_env("HOME=", env)))
		{
			custom_chdir(home, flag);
			free(home);
		}
		else
			ft_putstr("HOME variable does not exist.");
	}
	else
		custom_chdir(exec[index], flag);
	return (0);
}
