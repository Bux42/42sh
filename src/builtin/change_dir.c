/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 06:48:58 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/14 13:02:55 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int			change_pwd(int flag, t_env **env, char *path, int err)
{
	char	*oldpwd;
	int		ret;
	char	getpwd[2048];

	oldpwd = get_specific_env("PWD=", env);
	if (err == 1)
	{
		free(oldpwd);
		return (err_msg("cd: no such file or directory: ", getpwd, -1));
	}
	if (flag & 1)
		set_env(env, "OLDPWD=", getcwd(getpwd, 2048));
	else
		set_env(env, "OLDPWD=", oldpwd);
	ret = chdir(path);
	if (flag & 1)
		set_env(env, "PWD=", getcwd(getpwd, 2048));
	else
		set_env(env, "PWD=", path);
	free(oldpwd);
	return (ret);
}

int			check_link(char *path, int flag, struct stat st, t_env **env)
{
	char	buff[2048];
	char	*tmp;
	char	getpwd[2048];

	if (S_ISLNK(st.st_mode))
	{
		if (path[0] == '/')
			path_subcpy(path, buff, 0, ft_strlen(path));
		else
		{
			getwd(getpwd);
			tmp = path_join(getpwd, path);
			path_subcpy(tmp, buff, 0, ft_strlen(tmp));
			free(tmp);
		}
		path_eval(buff);
		resolve_relative_path(env, buff);
		if (fix_root(buff) == 0 && dir_exists(buff) != 0)
			return (change_pwd(flag, env, path, 1));
	}
	return (change_pwd(flag, env, path, 2));
}

int			custom_chdir(char *path, int flag, t_env **env)
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
			else if (check_link(path, flag, st, env) == -1)
				return (err_msg("cd: permission denied :", path, -1));
		}
	}
	return (1);
}

int			chdir_old_pwd(t_env **env, int flag)
{
	char	*old_pwd;

	if ((old_pwd = get_specific_env("OLDPWD=", env)))
	{
		custom_chdir(old_pwd, flag, env);
		free(old_pwd);
		return (0);
	}
	else
		return (err_msg("cd: OLDPWD not set", "", 3));
}

int			builtin_cd(char **exec, t_sh *sh)
{
	int		flag;
	int		index;
	char	*home;

	index = 1;
	if ((flag = parse_flags(exec, &index)) == -1)
		return (1);
	if (!exec[index])
	{
		if ((home = get_specific_env("HOME=", &sh->env)))
		{
			custom_chdir(home, flag, &sh->env);
			free(home);
		}
		else
			return (err_msg("cd: HOME not set", "", 2));
	}
	else if (ft_strcmp(exec[index], "-") == 0 &&
			chdir_old_pwd(&sh->env, flag) == 3)
		return (3);
	else if (!(ft_strcmp(exec[index], "-") == 0))
		custom_chdir(exec[index], flag, &sh->env);
	return (0);
}
