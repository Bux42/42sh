/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inpl_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:21:14 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 07:30:06 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		free_inpl(t_inpl **inpl)
{
	t_inpl	*cp;
	t_inpl	*tmp;

	cp = (*inpl);
	{
		while (cp)
		{
			tmp = cp;
			cp = cp->next;
			free_list_from_beginning(&tmp->inp);
			free(tmp);
		}
	}
}

t_inpl		*new_inpl(t_inp **inp, int type)
{
	t_inpl	*ret;

	if (!(ret = (t_inpl*)malloc(sizeof(t_inpl))))
		return (NULL);
	ret->inp = *inp;
	ret->type = type;
	ret->previous = NULL;
	ret->next = NULL;
	return (ret);
}

void		inpl_push_back(t_inpl **inpl, t_inp **inp, int type)
{
	t_inpl	*cp;
	t_inpl	*tmp;

	while (*inp && (*inp)->previous)
		(*inp) = (*inp)->previous;
	if (!(*inpl))
		*inpl = new_inpl(inp, type);
	else
	{
		cp = *inpl;
		while (cp->next)
			cp = cp->next;
		cp->next = new_inpl(inp, type);
		tmp = cp;
		cp = cp->next;
		cp->previous = tmp;
	}
}
