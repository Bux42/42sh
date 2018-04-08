/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:59:13 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 14:33:35 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	sve_fd(int save_fd[3])
{
	save_fd[0] = dup(0);
	save_fd[1] = dup(1);
	save_fd[2] = dup(2);
}

void	reset_fd(int save_fd[3])
{
	dup2(save_fd[0], 0);
	close(save_fd[0]);
	dup2(save_fd[1], 1);
	close(save_fd[1]);
	dup2(save_fd[2], 2);
	close(save_fd[2]);
}

void	builtin_redir(t_listc *cp, int (*func)(char **, t_sh*), t_sh *sh)
{
	int		save_fd[3];
	t_pipe	*p;

	sve_fd(save_fd);
	if (!(p = (t_pipe *)malloc(sizeof(t_pipe) * ((2)))))
		return ;
	redirect(cp, p, 0, &cp->redirs);
	func = cp->func;
	sh->retval = func(cp->cont, sh);
	reset_fd(save_fd);
	close_tabtube(2, p);
}

void	execute_tokens(t_listc **tok, t_sh *sh)
{
	t_listc	*cp;
	int		(*func)(char **, t_sh*);

	if ((cp = (*tok)))
	{
		while (cp)
		{
			if (cp->func && cp->sep_type != PIPE)
			{
				func = cp->func;
				(cp->redirs) ? builtin_redir(cp, func, sh) :
					(sh->retval = func(cp->cont, sh));
			}
			else if (cp->sep_type == AND || cp->sep_type == OR
				|| cp->sep_type & SEMICOLON || !cp->sep_type)
				exec_cli(cp->cont[0], cp, sh);
			else if (cp->sep_type & PIPE)
			{
				prepare_pipe(cp);
				exec_cli(cp->cont[0], cp, sh);
				while (cp->next && cp->sep_type & PIPE)
					cp = cp->next;
			}
			cp = cp->next;
		}
	}
}
