/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:59:26 by dquartin          #+#    #+#             */
/*   Updated: 2018/03/12 18:20:33 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/header.h"
#include "../builtin.h"

/*
** Parsing qui appelle les fonctions correspondantes aux options
*/

int		ft_cd_bis(char *path, char *option, t_env **env, char *buff)
{
	ft_putstr("||");
	ft_putstr(path);
	ft_putstr("||");
	if (ft_strcmp(path, "..") == 0)
	{
		ft_putstr("a");
		return (cd_back(env));
	}
	if (ft_strcmp(path, "-") == 0)
	{
		ft_putstr("b");
		return (cd_less(env, buff));
	}
	if (ft_strcmp(path, "-L") == 0)
	{
		ft_putstr("c");
		return (cd_l(env, option));
	}
	if (ft_strcmp(path, "-P") == 0)
	{
		ft_putstr("d");
		return (cd_p(env, option, buff));
	}
	return (-5);
}

/*
** Cas ou le path est introuvable dans l'environnement, le path est set
** sur /
*/

static void	ft_set_path(char **tmp, char **path, char **option, t_env **env)
{
	if ((*tmp = get_specific_env("HOME=", env)) == 0)
	{
		ft_putendl("Variable HOME not set, HOME defined to /");
		*tmp = ft_strdup("/");
	}
	*path = ft_strdup(*tmp);
	*option = ft_strdup("1");
}

/*
** Fonction qui verifie la validite de la ligne de commande et appelle
** les fonctions correspondantes au cd. Verifie egalement la presence
** d'un path et la presence ou non d'arguments ou d'options suivant
** la commande cd.
*/

int		ft_cd(char **stock, t_sh *sh)
{
	char	*tmp;
	char	buff[200];
	char	*path;
	char	*option;

	tmp = NULL;
	path = NULL;
	option = NULL;
	if (stock[0] && stock[1])
		path = ft_strdup(stock[1]);
	if (stock[0] && stock[1] && stock[2])
		option = ft_strdup(stock[2]);
	if (return_dot(path, option) || error_environ(&sh->env, path, option))
		return (-1);
	if (!path)
		ft_set_path(&tmp, &path, &option, &sh->env);
	if (return_usage(path, option))
		return (-1);
	if (return_cd_bis(path, option, &sh->env, buff))
		return (-1);
	check_cd(path, &sh->env, buff);
	ft_strdel(&path);
	ft_strdel(&option);
	ft_strdel(&tmp);
	return (0);
}
