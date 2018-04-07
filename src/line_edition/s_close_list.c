/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_close_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:39:51 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/07 10:53:04 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		check_close_length(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;
	int		len;

	len = 0;
	if ((cp = (*inp)))
	{
		while (cp && !cp->pos)
			cp = cp->next;
		while (cp && cp->next)
		{
			len++;
			cp = cp->next;
		}
		len /= sh->width;
		while (len--)
			custom_return();
	}
}

int			print_expected_prompt(t_sh *sh, t_close **close)
{
	t_close		*cp;

	sh->posy = 1;
	check_close_length(&sh->inpl->inp, sh);
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
	sh->prompt_len = sh->posy;
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
