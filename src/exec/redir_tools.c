/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:55:29 by jamerlin          #+#    #+#             */
/*   Updated: 2018/03/28 21:34:59 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	errexit(char *str)
{
	ft_putstr("[");
	ft_putstr(str);
	ft_putstr("]\n");
	exit(1);
}

void	prepare_pipe(t_listc *cmd)
{
	t_listc	*cpy;
	int		nb_cmd;
	int		i;

	cpy = cmd;
	nb_cmd = 0;
	i = 0;
	while (cpy->sep_type == PIPE)
	{
		if (cpy->sep_type == PIPE)
			nb_cmd++;
		cpy = cpy->next;
	}
	cpy = cmd;
	nb_cmd++;
	while (cpy && i < nb_cmd)
	{
		cpy->nb_arg = nb_cmd;
		i++;
		cpy = cpy->next;
	}
}

void	closed_unused_fd(int fils, int nb_tube, t_pipe *tabtube)
{
	int i;

	i = 0;
	while (i < nb_tube)
	{
		if (i != (fils - 1))
			close(tabtube[i].cote[0]);
		if (i != fils)
			close(tabtube[i].cote[1]);
		i++;
	}
}
