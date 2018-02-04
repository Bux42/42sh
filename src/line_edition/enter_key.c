/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inpl_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 01:08:57 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/04 18:34:47 by videsvau         ###   ########.fr       */
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
	if (sh->inpl->inp)
		history_push_front(&sh->history, sh->inpl->inp, sh);
	sh->history_len = history_len(&sh->history);
	parse(sh);
	while (sh->inpl && sh->inpl->next)
		sh->inpl = sh->inpl->next;
	while (sh->inpl && sh->inpl->previous)
	{
		free_list_from_beginning(&sh->inpl->inp);
		sh->inpl = sh->inpl->previous;
		free(sh->inpl->next);
		sh->inpl->next = NULL;
	}
	if (sh->inpl)
	{
		free_list_from_beginning(&sh->inpl->inp);
		sh->inpl->next = NULL;
	}
	print_prompt(sh);
}

void		enter_key(t_sh *sh)
{
	int		print;

	print = 1;
	custom_return();
	if (sh->expected_quote == '\0')
	{
		if (cut_from_quote(sh, &sh->inpl->inp))
			print = inpl_add_new(&sh->inpl, 0);
	}
	else
	{
		if (get_closing_quote(sh, &sh->inpl->inp))
			print = 1;
		else
			print = inpl_add_new(&sh->inpl, 0);
	}
	if (print)
		process_line(sh);
}
