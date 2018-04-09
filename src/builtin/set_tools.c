/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 11:32:28 by drecours          #+#    #+#             */
/*   Updated: 2018/04/09 11:57:06 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

int		valid_name(char *str, char *builtin)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] <= 32)
		{
			i = -1;
			break ;
		}
		i++;
	}
	if (i == -1)
	{
		ft_putstr_fd(builtin, STDERR_FILENO);
		ft_putstr_fd(": wrong caracter in variable: \"", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("\"", STDERR_FILENO);
		return (0);
	}
	return (1);
}
