/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 06:48:58 by videsvau          #+#    #+#             */
/*   Updated: 2018/01/11 15:57:52 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

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
				if (exec[j][1])
					(*index)++;
			}
			else
				if (tir && (i = check_flag(i, exec[j][k])) == -1)
					return (-1);
		}
	}
	return (i);
}

int			check_link(char *path, int flag, struct stat st)
{
	char	buff[1024];
	char	getpwd[1024];
	int		ret;

	if (S_ISLNK(st.st_mode))
	{
		if (!(flag & 1))
		{
			ft_bzero(buff, 1024);
			getwd(getpwd);
			ft_strcat(buff, getpwd);
			ft_strcat(buff, "/");
			ft_strcat(buff, path);
		}
	}
	ret = chdir(path);
	return (ret);
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
			else if (check_link(path, flag, st) == -1)
				return (err_msg("wtf have you done :", path, -1));
		}
	}
	return (1);
}

void		update_env_chdir(char *cur_pwd, char *old_pwd, t_env **env)
{
	set_env(env, "PWD=", cur_pwd);
	set_env(env, "OLDPWD=", old_pwd);
}

int			chdir_old_pwd(t_env **env, int flag)
{
	char	*old_pwd;

	if ((old_pwd = get_specific_env("OLDPWD=", env)))
	{
		custom_chdir(old_pwd, flag);
		free(old_pwd);
		return (1);
	}
	else
		return (err_msg("cd: OLDPWD not set", "", -1));
}

int			change_dir(char **exec, t_env **env)
{
	int		flag;
	int		index;
	char	*home;
	char	old_pwd[2048];
	char	cur_pwd[2048];

	index = 1;
	if ((flag = parse_flags(exec, &index)) == -1)
		return (-1);
	getwd(old_pwd);
	if (!exec[index])
	{
		if ((home = get_specific_env("HOME=", env)))
		{
			custom_chdir(home, flag);
			free(home);
		}
		else
			return (err_msg("cd: HOME not set", "", -1));
	}
	else if (exec[index][0] == '-' && !exec[index][1])
		return (chdir_old_pwd(env, flag));
	else
		custom_chdir(exec[index], flag);
	getwd(cur_pwd);
	if (ft_strcmp(cur_pwd, old_pwd) != 0)
		update_env_chdir(cur_pwd, old_pwd, env);
	return (0);
}
