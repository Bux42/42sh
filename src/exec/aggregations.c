/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:45:51 by jamerlin          #+#    #+#             */
/*   Updated: 2018/04/10 15:45:56 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	do_aggre(t_listc *cmd, t_pipe *tabtube, int i)
{
	if (cmd->redirs->file == NULL)
		tabtube[i].cote[0] = cmd->redirs->redir[2];
	else
	{
		if (cmd->redirs->redir[1] == AGGR + AGGRFILE)
			tabtube[i].cote[0] = open(cmd->redirs->file, O_RDWR | O_APPEND
				| O_CREAT, S_IRWXU);
		else if (cmd->redirs->redir[1] == AGGR + AGGRFILE + AGGROUT)
			tabtube[i].cote[0] = open(cmd->redirs->file, O_RDWR | O_TRUNC
				| O_CREAT, S_IRWXU);
	}
	tabtube[i].cote[1] = cmd->redirs->redir[0];
	if (cmd->redirs->redir[1] == AGGR + AGGRFILE && tabtube[1].cote[0] == -1)
		close(tabtube[1].cote[1]);
	else if (cmd->redirs->redir[1] == LAGGRIN && tabtube[i].cote[0] == -1)
		close(tabtube[i].cote[1]);
	else if (cmd->redirs->redir[1] == AGGR + AGGRFILE + AGGROUT
		&& tabtube[i].cote[0] == -1)
		close(tabtube[i].cote[1]);
	else if (cmd->redirs->redir[1] == CLOSEAGGR)
		close(tabtube[i].cote[1]);
}
