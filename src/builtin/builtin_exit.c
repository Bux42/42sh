/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 12:11:37 by drecours          #+#    #+#             */
/*   Updated: 2018/03/03 14:38:42 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	quit(char **input, int ret)
{
	ft_putstr_fd("Bye!", STDOUT_FILENO);
	custom_return();
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_old_term);
	if (!input[1])
		exit(ret);
	exit(ft_atoi(input[1]));
}

int		quit_error(int i, int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd("exit: Too many arguments.", STDERR_FILENO);
		custom_return();
		return (1);
	}
	if (i == 0)
	{
		ft_putstr_fd("exit: Expression syntax.", STDERR_FILENO);
		custom_return();
		return (2);
	}
	ft_putstr_fd("exit: Badly formed number.", STDERR_FILENO);
	custom_return();
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
