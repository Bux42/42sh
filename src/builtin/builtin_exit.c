/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 12:11:37 by drecours          #+#    #+#             */
/*   Updated: 2018/01/11 10:49:42 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

//REMPLACER LOCALE->RET PAR DERNIERE VALEUR DE RETOUR OBTENUE

int			quit(char **input)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_old_term);
	ft_putendl_fd("Bye!", STDOUT_FILENO);
	if (!input[1])
		exit(0);
	exit(ft_atoi(input[1]));
	return (0);
}

int			builtin_exit(char **input, t_env **env)
{
	int		i;
	int		flag;

	(void)env;
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
		return (quit(input));
	ft_putendl_fd((i == 0) ? "exit: Expression Syntax." :
			"exit: Badly formed number.", STDOUT_FILENO);
	return (1);
}
