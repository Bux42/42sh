/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclaim_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 17:46:57 by drecours          #+#    #+#             */
/*   Updated: 2018/03/15 19:59:44 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

void	suppr_letter(t_inp **c)
{
	t_inp	*tmp;

	tmp = *c;
	ft_putchar(tmp->c);
	if (tmp->previous)
	{
		ft_putstr("probleme");
		tmp->previous->next = tmp->next;
		if (tmp->next)
			tmp->next->previous  = tmp->previous;
		free(tmp);
	}
	else
	{
		ft_putstr("normal");
		tmp = (*c)->next;
		ft_putstr("	ON DOIT DRESSER LE CHAPITEAU");
		free(*c);
		ft_putstr("j ai free");
		if (tmp)
			(tmp)->previous = NULL;
	}
}

t_inp	*insert_inp(t_inp **inp, char c)
{
	t_inp	*tmp;

	tmp = (*inp)->next;
	(*inp)->next = new_inp(c);
	(*inp)->next->previous = (*inp);
	(*inp)->next->next = tmp;
	if (tmp)
		tmp->previous = (*inp)->next;
	//	else
	//		(*inp)->next->next = NULL;
	return ((*inp)->next);
}

void	suppr_exclaim(t_inp **inp, int i, t_sh *sh)
{
	t_inp	*tmp;

	(void)sh;
	tmp = *inp;
	ft_putchar((*inp)->c);
	ft_putchar(tmp->c);
	ft_putstr("hop");
	while (--i >= 0 && (*inp)->next)
	{
		ft_putchar((*inp)->next->c);
		//delete_letter(sh, &(*inp)->next);
		suppr_letter(&(*inp)->next);
	}
	ft_putstr("hop");
	/*	if ((*inp) && (*inp)->previous)
		inp = &(*inp)->previous;
		if (inp && *inp && (*inp)->c)
		{
		ft_putchar((*inp)->c);
	//	delete_letter(sh, &(*inp)->next);
	suppr_letter(&(*inp)->next);
	}
	else
	//	delete_letter(sh, inp);
	suppr_letter(inp);*/
	ft_putstr("flute");
	//	if ((*inp)->next)
	//		inp = &(*inp)->next;
	//	else
	//		inp = NULL;
	//	suppr_letter(&tmp);o
	//	free(tmp);
	ft_putstr("hop");
	ft_putstr("hop");
	//while (tmp && tmp->previous)
	//	tmp = tmp->previous;
	//	inp = &tmp;
}

int		nothing_front_back(t_inp **input, int i)
{
	t_inp	*inp;

	inp = (*input);
	if (inp->previous)
		return (0);
	while (inp && inp->c && i--)
		inp = inp->next;
	if (!inp)
		return (-1);
	return (0);
}

void	pt_next(t_inp **input, int i)
{
	(*input) = (*input)->next;
	while (i-- > 0)
		(*input) = (*input)->next;
}
