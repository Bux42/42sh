/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_backquotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 07:30:31 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/21 14:00:46 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "../builtin/builtin.h"

void		inp_insert_posat_remake(t_inp **ret, char c)
{
	t_inp	*tmp;

	if (!*ret)
		*ret = new_inp(c);
	else
	{
		if ((tmp = new_inp(c)))
		{
			tmp->previous = *ret;
			(*ret)->next = tmp;
			(*ret) = (*ret)->next;
		}
	}
}

void		concat_inp(t_inp **inp, t_inp **ret, t_inpl *inpl)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->c == '\\' && !cp->next && inpl->next)
				;
			else
				inp_insert_posat_remake(ret, cp->c);
			if (!cp->next)
				if (inpl->next)
					if (cp->c != '\\')
						inp_insert_posat_remake(ret, '\n');
			cp = cp->next;
		}
	}
}

t_inp		*concat_inpl(t_inpl **inpl, t_sh *sh)
{
	t_inpl	*cp;
	t_inp	*ret;

	ret = NULL;
	sh->posy = sh->posy;
	if ((cp = (*inpl)))
	{
		while (cp)
		{
			concat_inp(&cp->inp, &ret, cp);
			cp = cp->next;
		}
	}
	while (ret && ret->previous)
		ret = ret->previous;
	return (ret);
}

void		free_and_relink(t_inp **inp, char c)
{
	t_inp	*tmp;

	tmp = (*inp)->next;
	(*inp)->next = tmp->next;
	if (tmp->next)
		tmp->next->previous = (*inp);
	free(tmp);
	if (c)
		(*inp)->c = c;
}

int			empty_inp(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;
	int		i;

	if (history_exclaim(inp, sh))
		return (0);
	i = 0;
	if ((cp = (*inp)))
	{
		while (cp && cp->c)
		{
			if (!is_space(cp->c))
				i++;
			cp = cp->next;
		}
	}
	return (i);
}

int			tokenize_splitted(t_inpl **inpl, t_sh *sh, t_listc **tok);

void		parse(t_sh *sh)
{
	t_inp	*clean;
	t_inpl	*splitted;
	t_listc	*tok;

	clean = concat_inpl(&sh->inpl, sh);
	tok = NULL;
	if (empty_inp(&clean, sh))
	{
		history_push_front(&sh->history, clean, sh);
		sh->history_len = history_len(&sh->history);
		splitted = NULL;
		sh->context = 0;
		split_line(&splitted, &clean, sh);
		if (convert_splitted(&splitted, sh) != NULL)
		{
			print_splitted(&splitted);
			ft_putstr("Creating Token List");
			tokenize_splitted(&splitted, sh, &tok);
			execute_tokens(&tok, sh);
		}
		custom_return();
		sh->context = 0;
	}
	free_list_from_beginning(&clean);
}
