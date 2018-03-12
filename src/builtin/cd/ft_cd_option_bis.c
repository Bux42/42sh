/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_option_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:41:55 by dquartin          #+#    #+#             */
/*   Updated: 2018/03/12 17:35:53 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/header.h"
#include "../builtin.h"

/*
** Suite de l'option cd -L qui suit les liens
*/

void	cd_l_bis(t_env **env, char **path, char *buff)
{
	char	*tmp;
	char	*tmp2;
	int		free;

	free = 0;
	tmp = NULL;
	buff = NULL;
	if ((*path)[0] != '/')
	{
		tmp = getcwd(tmp, 200);
		ft_strjoin(tmp, "/");
		tmp2 = ft_strdup(*path);
		ft_strdel(path);
		*path = ft_strjoin(tmp, tmp2);
		free = 1;
		ft_strdel(&tmp2);
	}
	tmp2 = getcwd(buff, 200);
	set_env(env, "OLDPWD=", tmp2);
	chdir(*path);
	set_env(env, "PWD=", *path);
	ft_strdel(&tmp2);
}

/*
** Check si l'acces est possible sinon cas d'erreur
*/

void	check_cd(char *path, t_env **env, char *buff)
{
	if (path)
	{
		if (access(path, F_OK | X_OK) == 0)
			cd(env, &path, buff);
		else if (access(path, F_OK) == -1)
			error_case1(path);
		else if (access(path, X_OK) == -1)
			error_case2(path);
	}
}
