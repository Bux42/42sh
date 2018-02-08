/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_backquotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 07:30:31 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/05 16:06:50 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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
				inp_insert_posat(ret, cp->c);
			if (!cp->next)
				if (inpl->next)
					if (cp->c != '\\')
						inp_insert_posat(ret, '\n');
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

void		check_escape(t_inp **inp)
{
	if ((*inp)->next && (*inp)->next->c == '\\')
		free_and_relink(inp, '\\');
	else if ((*inp)->next && (*inp)->next->c == 'n')
		free_and_relink(inp, '\n');
	else if ((*inp)->next && (*inp)->next->c == 't')
		free_and_relink(inp, '\t');
	else if ((*inp)->next && (*inp)->next->c == 'v')
		free_and_relink(inp, '\v');
	else if ((*inp)->next && (*inp)->next->c == 'a')
		free_and_relink(inp, '\a');
	else if ((*inp)->next && (*inp)->next->c == 'b')
		free_and_relink(inp, '\b');
	else if ((*inp)->next && (*inp)->next->c == 'f')
		free_and_relink(inp, '\f');
	else if ((*inp)->next)
		free_and_relink(inp, (*inp)->next->c);
}

void		convert_backslashes(t_inp **inp, t_sh *sh)
{
	while (*inp)
	{
		if ((*inp)->c == '\'')
			if (working_context(sh->context, (*inp)->c))
				sh->context = update_context(sh->context, (*inp)->c);
		if ((*inp)->c == '\"')
			if (working_context(sh->context, (*inp)->c))
				sh->context = update_context(sh->context, (*inp)->c);
		if ((*inp)->c == '\\')
		{
			if (sh->context == 0)
				free_and_relink(inp, (*inp)->next->c);
			else
				check_escape(inp);
		}
		if (!(*inp) || !(*inp)->next)
			break ;
		else
			(*inp) = (*inp)->next;
	}
	while (*inp)
	{
		if (!(*inp)->previous)
			break ;
		else
			(*inp) = (*inp)->previous;
	}
}

int			empty_inp(t_inp **inp)
{
	t_inp	*cp;
	int		i;

	i = 0;
	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (!is_space(cp->c))
				i++;
			cp = cp->next;
		}
	}
	return (i);
}

void		parse(t_sh *sh)
{
	t_inp	*clean;

	clean = concat_inpl(&sh->inpl, sh);
	history_push_front(&sh->history, clean, sh);
	if (empty_inp(&clean))
	{
		convert_backslashes(&clean, sh);
		sh->context = 0;
		lexer_parser(&clean, sh);
		custom_return();
		valid_command(&clean, sh);
	}
	free_list_from_beginning(&clean);
}
