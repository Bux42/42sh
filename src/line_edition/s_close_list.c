/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_close_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:39:51 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/21 12:38:12 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

t_close		*new_close(int flag)
{
	t_close		*ret;

	if (!(ret = (t_close*)malloc(sizeof(t_close))))
		return (NULL);
	ret->next = NULL;
	ret->previous = NULL;
	ret->flag = flag;
	return (ret);
}

void		delete_last_close(t_close **close)
{
	t_close		*cp;

	if (!(*close)->next)
	{
		free(*close);
		*close = NULL;
	}
	else
	{
		cp = *close;
		*close = (*close)->next;
		(*close)->previous = NULL;
		free(cp);
		cp = NULL;
	}
}

void		s_close_add(int flag, t_close **close)
{
	t_close		*cp;

	if (!(*close))
		*close = new_close(flag);
	else
	{
		cp = new_close(flag);
		cp->next = *close;
		(*close)->previous = cp;
		*close = cp;
	}
}
