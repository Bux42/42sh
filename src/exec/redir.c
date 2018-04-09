/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:55:11 by jamerlin          #+#    #+#             */
/*   Updated: 2018/04/05 00:57:59 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	left_redirect(t_listc *cmd, t_pipe *tabtube, int i)
{
	int ret;

	if (!(ret = open(cmd->redirs->file, O_RDONLY)))
	{
		close(ret);
		errexit(cmd->redirs->file);
	}
	tabtube[i].cote[0] = (cmd->redirs->file) ? ret : cmd->redirs->redir[2];
	tabtube[i].cote[1] = cmd->redirs->redir[0];
}

void	right_redirect(t_listc *cmd, t_pipe *tabtube, int i)
{
	tabtube[i].cote[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR
			| O_TRUNC | O_CREAT, S_IRWXU) : cmd->redirs->redir[2];
	tabtube[i].cote[1] = cmd->redirs->redir[0];
}

void	heredock_redirect(t_listc *cmd, t_pipe *tabtube, int i)
{
	int j;

	j = 0;
	if (pipe(tabtube[i].cote) == -1)
		errexit("pipe");
	while (cmd->redirs->heredoc[j])
	{
		write(tabtube[i].cote[1], cmd->redirs->heredoc[j]
			, ft_strlen(cmd->redirs->heredoc[j]));
		j++;
	}
	close(tabtube[i].cote[1]);
}

void	double_right_redirect(t_listc *cmd, t_pipe *tabtube, int i)
{
	tabtube[i].cote[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR
			| O_APPEND | O_CREAT, S_IRWXU) : cmd->redirs->redir[2];
	tabtube[i].cote[1] = cmd->redirs->redir[0];
}

void	do_aggre(t_listc *cmd, t_pipe *tabtube, int i)
{
	if (cmd->redirs->redir[1] == AGGR)
	{
		if (cmd->redirs->redir[0] != -1 && (cmd->redirs->redir[1] != -1
					&& cmd->redirs->file == NULL))
		{
			tabtube[i].cote[0] = cmd->redirs->redir[2];
			tabtube[i].cote[1] = cmd->redirs->redir[0];
		}
	}
	else if (cmd->redirs->redir[1] == AGGR + AGGRFILE)
	{
		if (cmd->redirs->file != NULL)
		{
			tabtube[i].cote[0] = open(cmd->redirs->file, O_RDWR | O_APPEND
					| O_CREAT, S_IRWXU);
			tabtube[i].cote[1] = cmd->redirs->redir[0];
		}
		else
		{
			tabtube[i].cote[0] = cmd->redirs->redir[2];
			tabtube[i].cote[1] = cmd->redirs->redir[0];
			if (tabtube[i].cote[0] == -1)
				close(tabtube[i].cote[1]);
		}
	}
	else if (cmd->redirs->redir[1] == AGGR + AGGRFILE + AGGROUT)
	{
		tabtube[i].cote[0] = (cmd->redirs->file) ? open(cmd->redirs->file,
				O_RDWR | O_TRUNC | O_CREAT, S_IRWXU) : cmd->redirs->redir[2];
		tabtube[i].cote[1] = cmd->redirs->redir[0];
		if (tabtube[i].cote[0] == -1)
			close(tabtube[i].cote[1]);
	}
	else if (cmd->redirs->redir[1] == LAGGR || cmd->redirs->redir[1] == LAGGRIN)
	{
		tabtube[i].cote[0] = cmd->redirs->redir[2];
		tabtube[i].cote[1] = cmd->redirs->redir[0];
		if (cmd->redirs->redir[1] == LAGGRIN && cmd->redirs->redir[2] == -1)
			close(tabtube[i].cote[1]);
	}
	else if (cmd->redirs->redir[1] == CLOSEAGGR)
	{
		tabtube[i].cote[0] = cmd->redirs->redir[2];
		tabtube[i].cote[1] = cmd->redirs->redir[0];
		close(tabtube[i].cote[1]);
	}
}

void	redirect(t_listc *cmd, t_pipe *tabtube, int i, t_redir **redir)
{
	t_redir	*cp;

	cp = *redir;
	while (cmd->redirs != NULL)
	{
		if (cmd->redirs && cmd->redirs->redir[1] == 0)
			left_redirect(cmd, tabtube, i);
		else if (cmd->redirs && cmd->redirs->redir[1] & (1 | 16))
			right_redirect(cmd, tabtube, i);
		else if (cmd->redirs && cmd->redirs->redir[1] == 3)
			double_right_redirect(cmd, tabtube, i);
		else if (cmd->redirs && (cmd->redirs->redir[1] & (AGGR | LAGGR
			| LAGGRIN | CLOSEAGGR)))
			do_aggre(cmd, tabtube, i);
		if (tabtube[i].cote[0] != -1)
		{
			if (cmd->redirs->redir[1] != 0 && cmd->redirs->redir[1] != 4
				&& cmd->redirs->redir[0] != 2)
				dup2(tabtube[i].cote[0], STDOUT_FILENO);
			else if (cmd->redirs->redir[0] != 2)
				dup2(tabtube[i].cote[0], STDIN_FILENO);
			else
				dup2(tabtube[i].cote[0], STDERR_FILENO);
		}
		if (cmd->redirs && !(cmd->redirs->redir[1] & AGGR))
			close(tabtube[i].cote[0]);
		if (cmd->redirs->next)
			cmd->redirs = cmd->redirs->next;
		else
			break ;
	}
	cmd->redirs = cp;
	i++;
}
