/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 12:11:37 by drecours          #+#    #+#             */
/*   Updated: 2017/10/31 16:07:29 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			builtin_exit(t_cmd *cmd)
{
	int		i;
	int		flag;

	// envoyer directement maillon apres "exit"
	i = 0;
	flag = 1;
	if (cmd && cmd->arg && cmd->next == NULL)
	{
		flag = 0;
		if (cmd->arg[i] == '-')
			++i;
		--i;
		while (cmd->arg[++i])
			if (!(cmd->arg[i] >= '0' && cmd->arg[i] <= '9'))
			{
				flag = 1;
				break ;
			}
	}
	if (flag == 0 || cmd == NULL)
		ft_pustr("Bye!");
	if (flag == 0 || cmd == NULL)
		exit(ft_atoi(cmd->str));
	ft_putendl_fd((i == 0) ? "exit: Expression Syntax." :
			"exit: Badly formed number.", STDOUT_FILENO);
	return (1);
}
