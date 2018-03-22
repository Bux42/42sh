/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special_surrounding.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:16:03 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/22 15:00:04 by videsvau         ###   ########.fr       */
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
		if (inpl->previous->type > 64 && inpl->previous->type < 2048)
			if (inpl->next->type > 64 && inpl->next->type < 2048)
				return (0);
	return (1);
}

int			bad_surrounding_2(t_inpl *inpl)
{
	if (inpl->previous && inpl->next)
		if (inpl->next->type & _FILE)
			if (inpl->previous->type > 64 && inpl->previous->type < 1024)
				return (0);
	return (1);
}

int			bad_surrounding_3(t_inpl *inpl)
{
	if (inpl->previous)
		if (inpl->previous->type > 64 && inpl->previous->type < 1024)
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
				if (bad_surrounding_2(cp))
					return (special_error_surrounding(&cp->inp));
			if (cp->type & HERE)
			{
				if (bad_surrounding_3(cp))
					return (special_error_surrounding(&cp->inp));
			}
			cp = cp->next;
		}
	}
	return (1);
}
