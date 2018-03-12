/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:15:16 by hlely             #+#    #+#             */
/*   Updated: 2018/03/12 17:46:26 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"
#include "../../../inc/header.h"

/*
** Copie les options de la ligne de commande dans la variable option
** et le path dans la variable path. Si l'element commencd par '-'
** alors il s'agit d'une option et sera copie dans option, sinon dans
** path.
*/

void	cpy_path_opt(char **path, char **option, char **stock)
{
	if (stock[1][0] == '-')
		*option = ft_strdup(stock[1]);
	else
		*path = ft_strdup(stock[1]);
}

/*
** Le cas echeant, s'il existe a la foi une option et un path, le path
** initialement defini comme le premier element suivant 'cd' est supprime
** et remplacer par le vrai path, suivant l'option.
*/

void	change_path_opt(char **path, char **option, char **stock)
{
	ft_strdel(path);
	*path = ft_strdup(stock[2]);
	*option = ft_strdup(stock[1]);
}
