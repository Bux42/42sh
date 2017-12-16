/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 06:48:58 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/16 11:42:31 by videsvau         ###   ########.fr       */
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
	return (-1);
}

int			parse_flags(char **exec)
{
	int		i;
	int		j;
	int		k;
	int		tir;

	i = 0;
	j = 0;
	while (exec[++j])
	{
		k = -1;
		tir = 0;
		while (exec[j][++k])
		{
			if (exec[j][k] == '-')
			{
				if (tir)
					return (-1);
				else
					tir++;
			}
			else if (tir && (i = check_flag(i, exec[j][k])) == -1)
				return (-1);
		}
	}
	return (i);
}

int			custom_chdir(char *path)
{
	struct stat		st;
	int				rights;

	rights = 0;
	if ((lstat(path, &st)) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(path);
		custom_return();
		return (-1);
	}
	else
	{
		if (!(S_ISDIR(st.st_mode)))
		{
			ft_putstr("cd: not a directory: ");
			ft_putstr(path);
			custom_return();
			return (-1);
		}
		else
		{
			rights += (st.st_mode & S_IRUSR) ? 1 : 0;
			rights += (st.st_mode & S_IWUSR) ? 1 : 0;
			rights += (st.st_mode & S_IXUSR) ? 1 : 0;
			if (!rights)
			{
				ft_putstr("cd: permission denied: ");
				ft_putstr(path);
				custom_return();
				return (-1);
			}
			else if (chdir(path) == -1)
			{
				perror("chdir: ");
				ft_putstr("WTF have you done, you fool, I don't have a message for that error!");
				custom_return();
				return (-1);
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

	if (env)
		;
	index = 1;
	flag = parse_flags(exec);
	if (!exec[index])
	{
		if ((home = get_specific_env("HOME=", env)))
		{
			custom_chdir(home);
			free(home);
		}
		else
			ft_putstr("HOME variable does not exist.");
	}
	else
		custom_chdir(exec[index]);
	return (0);
}
