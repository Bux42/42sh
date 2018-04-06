/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inpl_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 01:08:57 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/07 00:33:24 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		custom_return(void)
{
	ft_putstr(tgetstr("do", NULL));
	ft_putstr(tgetstr("cr", NULL));
}

int			inpl_add_new(t_inpl **inpl, int print)
{
	t_inpl	*new;
	t_inpl	*cp;

	if (!(new = (t_inpl*)malloc(sizeof(t_inpl))))
		return (print);
	new->inp = NULL;
	new->next = NULL;
	(*inpl)->next = new;
	cp = (*inpl);
	(*inpl) = (*inpl)->next;
	cp->next = (*inpl);
	(*inpl)->previous = cp;
	return (print);
}

void		process_line(t_sh *sh)
{
	while (sh->inpl && sh->inpl->previous)
		sh->inpl = sh->inpl->previous;
	parse(sh);
	while (sh->history && sh->history->previous)
		sh->history = sh->history->previous;
	print_prompt(sh);
}

void		enter_key(t_sh *sh)
{
	int		print;

	print = 1;
	custom_return();
	if (!sh->close)
	{
		if (!line_is_closed(sh, &sh->inpl->inp))
			print = inpl_add_new(&sh->inpl, 0);
	}
	else
	{
		if (line_is_closed(sh, &sh->inpl->inp))
			print = 1;
		else
			print = inpl_add_new(&sh->inpl, 0);
	}
	if (print)
		process_line(sh);
}
