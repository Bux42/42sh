/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_close_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:39:51 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/12 21:05:32 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			print_expected_prompt(t_sh *sh, t_close **close)
{
	t_close		*cp;

	if ((cp = *close))
	{
		while (cp->next)
			cp = cp->next;
		while (cp)
		{
			if (cp->flag & QUOTE)
				print_str("quote", sh);
			if (cp->flag & DQUOTE)
				print_str("dquote", sh);
			if (cp->flag & BQUOTE)
				print_str("bquote", sh);
			if (cp->previous)
			{
				print_str(" ", sh);
				cp = cp->previous;
			}
			else
				break ;
		}
	}
	print_str("> ", sh);
	return (0);
}

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
