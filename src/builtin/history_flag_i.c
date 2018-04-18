/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_flag_i.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 16:56:20 by drecours          #+#    #+#             */
/*   Updated: 2018/04/18 17:43:25 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

void	history_push(t_his **history, t_his *his)
{
	if (!(*history))
		(*history) = his;
	else
	{
		while ((*history)->previous)
			(*history) = (*history)->previous;
		(*history)->previous = his;
		his->next = (*history);
		(*history) = his;
	}
}

int		first_arg(char **exec)
{
	int		i;

	i = 1;
	while (exec[i])
	{
		if (ft_strcmp("--", exec[i]) == 0)
		{
			i++;
			break ;
		}
		if (exec[i][0] != '-')
			break ;
		i++;
	}
	return (i);
}

int		insert_err(void)
{
	ft_putendl_fd("Add problem too insert an arg in history", STDERR_FILENO);
	return (2);
}

int		insert_args(char *fg, t_sh *sh, char **exec)
{
	int		i;
	int		j;
	t_his	*ret;

	i = 0;
	i = first_arg(exec);
	j = i;
	while (exec[i])
	{
		if ((ret = new_his(exec[i])))
			history_push(&sh->history, ret);
		else
			return (insert_err());
		i++;
	}
	if (fg[2] == 'n')
	{
		ft_putnbr(i - j);
		ft_putendl(" new entries in history.");
	}
	return (0);
}
