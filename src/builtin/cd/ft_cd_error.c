/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:13:52 by dquartin          #+#    #+#             */
/*   Updated: 2018/03/12 17:57:13 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/header.h"
#include "../builtin.h"

/*
** Cas d'erreur ou il n'existe aucun fichier ou dossier
** correspondant au nom donne
*/

void	error_case1(char *path)
{
	ft_putstr("Error: ");
	if (path)
		ft_putstr(path);
	ft_putstr(": no such file or directory.");
}

/*
** Cas d'erreur ou l'acces est refuse
*/

void	error_case2(char *path)
{
	ft_putstr("Error: ");
	if (path)
		ft_putstr(path);
	ft_putstr(": permission denied.");
}

/*
** Affiche l'usage du cd et ses options
*/

int		return_usage(char *path, char *option)
{
	if (ft_strcmp(path, "--help") == 0)
	{
		ft_putstr("usage: cd [-] [-L] [-P] [argument ...]\n");
		ft_strdel(&path);
		ft_strdel(&option);
		return (1);
	}
	return (0);
}

/*
** Cas d'erreur ou la variable HOME n'existe plus dans l'environnement
*/

int		error_environ(t_env **env, char *path, char *option)
{
	if (get_specific_env("HOME=", env) == 0)
	{
		ft_putstr("Error : cd: HOME not set");
		ft_strdel(&path);
		ft_strdel(&option);
		return (1);
	}
	return (0);
}
