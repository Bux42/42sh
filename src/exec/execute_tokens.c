/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:59:13 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/21 19:44:35 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		execute_tokens(t_listc **tok, t_sh *sh)
{
	t_listc	*cp;
	int		(*func)(char **, t_sh*);

	if ((cp = (*tok)))
	{
		while (cp)
		{
			if (cp->func)
			{
				func = cp->func;
				sh->retval = func(cp->cont, sh);
			}
			else if (cp->sep_type == AND || cp->sep_type == OR || cp->sep_type & SEMICOLON || !cp->sep_type)
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
