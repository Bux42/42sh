/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_return.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:47:35 by drecours          #+#    #+#             */
/*   Updated: 2018/03/12 17:47:37 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../inc/header.h"
#include "../builtin.h"

/*
** Effectue un retour sur '.'
*/

int		return_dot(char *path, char *option)
{
	if (path && !ft_strcmp(path, "."))
	{
		ft_strdel(&path);
		ft_strdel(&option);
		return (1);
	}
	return (0);
}

int		return_cd_bis(char *path, char *option, t_env **env, char buff[])
{
	if (ft_cd_bis(path, option, env, buff) != -5)
	{
		ft_strdel(&path);
		ft_strdel(&option);
		return (1);
	}
	return (0);
}

/*
** Fonction qui set dans l'environnement l'ancien pwd dans la
** variable OLD_DIR
*/

void	set_old_dir(char *tmp2, char **path, t_env **env)
{
	set_env(env, "OLDPWD=", tmp2);
	set_env(env, "PWD=", *path);
}

/*
** Boucle qui effectue le cd back correspondant au path
** ../ donne. Tant que le path contient '../' et que le retour en
** arriere est possible, il sera fait
*/

void	cd_back_loop(char **tmp, char **path, t_env **env)
{
	char	*tmp1;

	ft_strdel(tmp);
	*tmp = NULL;
	tmp1 = get_specific_env("PWD=", env);
	*tmp = ft_strsub(tmp1, 0, ft_strlen(tmp1)
			- ft_strlen(ft_strrchr(tmp1, '/')));
	chdir(*tmp);
	set_env(env, "PWD=", *tmp);
	ft_strdel(&tmp1);
	ft_strdel(tmp);
	*tmp = NULL;
	*path = ft_strstr(*path, "../") ?
		ft_strdup(ft_strstr(*path, "../") + 3) :
		ft_strdup(ft_strstr(*path, "..") + 2);
}

void	cd_back_bis(char *tmp, char **path, t_env **env)
{
	tmp = ft_strdup(*path);
	ft_strdel(path);
	*path = ft_strjoin("/Users/", tmp);
	set_env(env, "PWD=", *path);
	ft_strdel(&tmp);
}
