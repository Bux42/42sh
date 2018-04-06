/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 12:11:37 by drecours          #+#    #+#             */
/*   Updated: 2018/04/07 00:54:22 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	quit(char **input, int ret)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_old_term);
	ft_putendl_fd("Bye!", STDOUT_FILENO);
	if (!input[1])
		exit(ret);
	exit(ft_atoi(input[1]));
}

int		quit_error(int i, int flag)
{
	if (flag == 1)
	{
		ft_putendl_fd("exit: Too many arguments.", STDERR_FILENO);
		return (1);
	}
	if (i == 0)
	{
		ft_putendl_fd("exit: Expression syntax.", STDERR_FILENO);
		return (2);
	}
	ft_putendl_fd("exit: Badly formed number.", STDERR_FILENO);
	return (3);
}

int		builtin_exit(char **input, t_sh *sh)
{
	int		i;
	int		flag;

	i = -1;
	flag = ((input[1] && !input[2]) || !input[1]) ? 0 : 1;
	if (input[1])
	{
		if (input[1][0] == '-')
			++i;
		while (input[1][++i])
			if (!(input[1][i] >= '0' && input[1][i] <= '9'))
			{
				flag = 1;
				break ;
			}
	}
	if (flag == 0)
		quit(input, sh->retval);
	flag = (input[1] && input[2]) ? 1 : 0;
	return (quit_error(i, flag));
}
