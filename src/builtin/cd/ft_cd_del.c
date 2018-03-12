/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:14:46 by hlely             #+#    #+#             */
/*   Updated: 2018/03/12 17:35:04 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"
#include "../../../inc/header.h"

void	del_opt_path(char **option, char **path)
{
	if (*option && ft_strcmp(*option, "1") == 0)
	{
		ft_strdel(option);
		ft_strdel(path);
	}
}
