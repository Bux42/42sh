/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:09:24 by drecours          #+#    #+#             */
/*   Updated: 2018/04/05 13:07:48 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			builtin_echo(char **input, t_sh *sh)
{
	int	i;
	int	flag;

	(void)sh;
	i = 1;
	flag = 0;
	if (input[i] && !ft_strcmp(input[i], "-n"))
		++i;
	while (input[i])
	{
		if (flag == 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(input[i], STDOUT_FILENO);
		++i;
		flag = 1;
	}
	if (!input[1] || ft_strcmp(input[1], "-n"))
		ft_putstr("\n");
	return (0);
}
