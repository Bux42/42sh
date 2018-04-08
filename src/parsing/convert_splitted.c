/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_splitted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 15:59:20 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 12:17:54 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		remove_backslash(t_inp **inp)
{
	t_inp	*previous;

	previous = (*inp)->previous;
	if (!(*inp)->next)
	{
		if (previous)
		{
			free(previous->next);
			previous->next = NULL;
			*inp = previous;
		}
	}
	else
	{
		(*inp) = (*inp)->next;
		if (previous)
			previous->next = (*inp);
		free((*inp)->previous);
		(*inp)->previous = previous;
	}
}

void		convert_regular(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->c == '\\')
				remove_backslash(&cp);
			else if (cp && cp->c == '\'')
				convert_quote(&cp);
			else if (cp && cp->c == '\"')
				convert_dquote(&cp, sh);
			else if (cp && cp->c == '$')
				try_insert_variable(&cp, sh);
			else if (cp && cp->c == '~')
				try_insert_home(&cp, sh);
			if (!cp)
				break ;
			(*inp) = cp;
			cp = cp->next;
		}
		while ((*inp)->previous)
			(*inp) = (*inp)->previous;
	}
}

int			idenfity_regular(t_inp **inp)
{
	int		type;

	type = 0;
	if (inp_cmp(inp, "env") || inp_cmp(inp, "unsetenv") || inp_cmp(inp, "echo"))
		return (type | BUILTIN);
	if (inp_cmp(inp, "cd") || inp_cmp(inp, "setenv") || inp_cmp(inp, "export"))
		return (type | BUILTIN);
	if (inp_cmp(inp, "exit") || inp_cmp(inp, "set") || inp_cmp(inp, "unset"))
		return (type | BUILTIN);
	if (inp_cmp(inp, "local") || inp_cmp(inp, "myman")
			|| inp_cmp(inp, "history"))
		return (type | BUILTIN);
	return (type | COMMAND);
}

int			check_special(t_inp **inp)
{
	int		type;
	t_inp	*cp;

	type = 0;
	if ((cp = (*inp)))
	{
		if (cp->c > 47 && cp->c < 58)
			type = check_mult_aggr(&cp);
		if (cp->c == '>')
			type = check_right_arrow(&cp);
		if (cp->c == '<')
			type = check_left_arrow(&cp);
		if (cp->c == '|')
			type = check_pipe_or(&cp);
		if (cp->c == '&')
			type = check_and(&cp);
		if (cp->c == ';')
			type = check_semicolon(&cp);
	}
	return (type);
}

void		*convert_splitted(t_inpl **inpl, t_sh *sh)
{
	t_inpl	*cp;

	if ((cp = (*inpl)))
	{
		while (cp)
		{
			if (cp->type == 0)
			{
				convert_regular(&cp->inp, sh);
				if (cp)
				{
					cp->type = idenfity_regular(&cp->inp);
					if (cp->previous && cp->previous->type > 64 &&
							cp->previous->type != 2048)
						cp->type = ARGUMENT;
					if (cp->previous && cp->previous->type > 8 &&
							cp->previous->type < 128)
						cp->type = _FILE;
					if (cp->previous && (cp->previous->type & HERE))
						cp->type = ARGUMENT;
				}
			}
			else if (cp->type == 1)
				if ((cp->type = check_special(&cp->inp)) == -1)
					return (special_error(&cp->inp));
			cp = cp->next;
		}
	}
	return (inpl);
}
