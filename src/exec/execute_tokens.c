/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:59:13 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/21 15:35:41 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		execute_tokens(t_listc **tok, t_sh *sh)
{
	t_listc	*cp;

	if ((cp = (*tok)))
	{
		while (cp)
		{
			if (cp->sep_type & SEMICOLON || !cp->sep_type)
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
