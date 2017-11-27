/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inpl_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 01:08:57 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/27 07:16:28 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

t_inpl		*inpl_create(void)
{
	t_inpl	*ret;

	if (!(ret = (t_inpl*)malloc(sizeof(t_inpl))))
		return (NULL);
	ret->inp = NULL;
	ret->next = NULL;
	return (ret);
}

void		custom_return(void)
{
	ft_putstr(tgetstr("do", NULL));
	ft_putstr(tgetstr("cr", NULL));
}

void		print_all_inp(t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			ft_putchar(cp->c);
			if (cp->next)
				cp = cp->next;
			else
				break;
		}
	}
}

void		print_all_inpl(t_inpl **inpl)
{
	t_inpl	*cp;

	if ((cp = (*inpl)))
	{
		while (cp)
		{
			if (cp->next)
				custom_return();
			print_all_inp(&cp->inp);
			if (cp->next)
				cp = cp->next;
			else
				break ;
		}
	}
}

void		enter_key(t_sh *sh)
{
	int		print;
	t_inpl	*cp;

	print = 1;
	custom_return();
	if (sh->inpl->inp && check_empty_line(&sh->inpl->inp))
	{
		if (sh->expected_quote == '\0')
		{
			if (cut_from_quote(sh, &sh->inpl->inp))
			{
				sh->inpl->next = inpl_create();
				if (sh->inpl->next)
				{
					cp = sh->inpl;
					sh->inpl = sh->inpl->next;
					cp->next = sh->inpl;
					sh->inpl->previous = cp;
				}
				print = 0;
			}
		}
		else
		{
			if (get_closing_quote(sh, &sh->inpl->inp))
				print = 1;
			else
			{
				sh->inpl->next = inpl_create();
				if (sh->inpl->next)
				{
					cp = sh->inpl;
					sh->inpl = sh->inpl->next;
					cp->next = sh->inpl;
					sh->inpl->previous = cp;
				}
				print = 0;
			}
		}
	}
	if (print)
	{
		while (sh->inpl && sh->inpl->previous)
			sh->inpl = sh->inpl->previous;
		print_all_inpl(&sh->inpl);
		if (sh->inpl->inp)
			history_push_front(&sh->history, sh->inpl->inp);
		sh->history_len = history_len(&sh->history);
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
		custom_return();
		print_prompt(sh);
	}
}
