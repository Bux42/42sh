/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special_surrounding.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:16:03 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 06:21:21 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			special_error_surrounding(t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		ft_putstr_fd("21sh: parse error near ", 2);
		while (cp)
		{
			ft_putchar_fd(cp->c, 2);
			cp = cp->next;
		}
		custom_return();
	}
	return (0);
}

int			bad_surrounding(t_inpl *inpl)
{
	if (inpl->previous && inpl->next)
		if ((inpl->previous->type > 64 && inpl->previous->type < 2048) ||
				inpl->previous->type > 2048)
			if (inpl->next->type > 64 && inpl->next->type < 2048)
				return (0);
	return (1);
}

int			bad_surrounding_3(t_inpl *inpl)
{
	if (inpl->previous && inpl->previous->previous)
		if (inpl->previous->previous->type & HERE)
			return (1);
	if (inpl->previous)
		if ((inpl->previous->type > 64 && inpl->previous->type < 1024) ||
				inpl->previous->type > 2048)
			if (inpl->next && inpl->next->type & ARGUMENT)
				return (0);
	return (1);
}

int			bad_surrounding_4(t_inpl *inpl, int flag)
{
	if (flag == 4 && inpl->previous)
	{
		if (inpl->previous->type > 64 && inpl->previous->type < 1024)
			return (0);
		else if (inpl->previous->type > 2048)
			return (0);
	}
	if (flag == 5 && inpl)
		if (inpl->inp && inpl->inp->c == '-' && !inpl->inp->next)
			return (0);
	if (flag == 2 && inpl->previous && inpl->next)
		if (inpl->next->type & _FILE)
			if (inpl->previous->type > 64 && inpl->previous->type < 2048)
				return (0);
	return (1);
}

int			check_special_surrounding(t_inpl **inpl)
{
	t_inpl	*cp;

	if ((cp = (*inpl)))
	{
		while (cp)
		{
			if (cp->type & PIPE || cp->type & AND || cp->type & OR)
				if (bad_surrounding(cp))
					return (special_error_surrounding(&cp->inp));
			if (cp->type & TOFILE || cp->type & ATOFILE || cp->type & TOEXE)
				if (bad_surrounding_4(cp, 2))
					return (special_error_surrounding(&cp->inp));
			if (cp->type & HERE)
				if (bad_surrounding_3(cp))
					return (special_error_surrounding(&cp->inp));
			if (cp->type & AGGR || cp->type & LAGGR || cp->type & LAGGRIN)
				if (bad_surrounding_4(cp, 4))
					return (special_error_surrounding(&cp->inp));
			if (cp->type & AGGROUT || cp->type & LAGGRIN)
				if (bad_surrounding_4(cp, 5))
					return (special_error_surrounding(&cp->inp));
			cp = cp->next;
		}
	}
	return (1);
}
