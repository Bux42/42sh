/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 16:21:51 by dquartin          #+#    #+#             */
/*   Updated: 2018/03/12 17:40:15 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/header.h"
#include "../builtin.h"

/*
** Cas du cd - qui ramene a l'ancien path, situe dans OLD_DIR
** et affiche le PWD
*/

int		cd_less(t_env **env, char *buff)
{
	char	*ret;
	char	*tmp;

	buff = getcwd(buff, 200);
	if ((tmp = get_specific_env("OLDPWD=", env)))
	{
		ft_strdel(&tmp);
		ret = get_specific_env("OLDPWD=", env);
		set_env(env, "OLDPWD=", buff);
		chdir(ret);
		set_env(env, "PWD=", ret);
		ft_strdel(&ret);
		getcwd(buff, 200);
		ft_putendl(buff);
	}
	return (0);
}

/*
** Cas du cd -P qui affiche le path complet, liens compris
*/

int		cd_p(t_env **env, char *option, char *buff)
{
	char	*tmp;
	char	*path_tmp;

	tmp = NULL;
	path_tmp = NULL;
	set_env(env, "OLDPWD=", getcwd(buff, 2048));
	if (option)
	{
		path_tmp = ft_strdup(option);
		if (chdir(path_tmp) == -1)
			error_case1(path_tmp);
		set_env(env, "PWD=", getcwd(buff, 2048));
	}
	else
	{
		if ((tmp = get_specific_env("HOME=", env)) == 0)
			tmp = ft_strdup("/");
		path_tmp = ft_strdup(tmp);
		if (chdir(path_tmp) == -1)
			error_case1(path_tmp);
		set_env(env, "PWD=", getcwd(buff, 2048));
	}
	ft_strdel(&tmp);
	ft_strdel(&path_tmp);
	return (0);
}

/*
** Cas du retour en arriere, voir avec la fonction cd_back_bis
*/

int		cd_back(t_env **env)
{
	char	*tmp;
	char	*tmp1;

	if ((tmp = get_specific_env("PWD=", env)) == 0)
		tmp = getcwd(tmp, 2048);
	set_env(env, "OLDPWD=", tmp);
	if (ft_strrchr(tmp + 1, '/') == NULL)
	{
		chdir("/");
		set_env(env, "PWD=", "/");
	}
	else
	{
		ft_strdel(&tmp);
		tmp1 = get_specific_env("PWD=", env);
		tmp = ft_strsub(tmp1, 0, ft_strlen(tmp1)
		- ft_strlen(ft_strrchr(tmp1, '/')));
		chdir(tmp);
		set_env(env, "PWD=", tmp);
		ft_strdel(&tmp1);
	}
	if (tmp)
		ft_strdel(&tmp);
	return (0);
}

/*
** Option -l du cd
*/

int		cd_l(t_env **env, char *option)
{
	char	*tmp;
	char	*path_tmp;
	char	buff[200];

	tmp = NULL;
	path_tmp = NULL;
	set_env(env, "OLDPWD=", getcwd(buff, 200));
	if (option)
		path_tmp = ft_strdup(option);
	else
	{
		if ((tmp = get_specific_env("HOME=", env)) == 0)
			tmp = ft_strdup("/");
		path_tmp = ft_strdup(tmp);
	}
	cd_l_bis(env, &path_tmp, buff);
	ft_strdel(&path_tmp);
	if (tmp)
		ft_strdel(&tmp);
	return (0);
}

/*
** Cd basique
*/

void	cd(t_env **env, char **path, char *buff)
{
	char	*tmp;
	char	*tmp2;
	int		free;

	free = 0;
	tmp = NULL;
	buff = NULL;
	if ((*path)[0] != '/')
	{
		if ((tmp = get_specific_env("PWD=", env)) == 0)
			tmp = getcwd(buff, 200);
		tmp = ft_strjoin(tmp, "/");
		tmp2 = ft_strdup(*path);
		*path = ft_strjoin(tmp, tmp2);
		ft_strdel(&tmp);
		free = 1;
		ft_strdel(&tmp2);
	}
	tmp2 = getcwd(buff, 200);
	if ((chdir(*path)) == -1)
		ft_putstr("Error: not a directory.");
	else
		set_old_dir(tmp2, path, env);
	ft_strdel(&tmp2);
	free ? ft_strdel(path) : 0;
}
