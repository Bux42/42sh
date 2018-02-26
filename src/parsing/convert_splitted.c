/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_splitted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 15:59:20 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/26 23:02:27 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		convert_regular(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->c == '\'')
				convert_quote(&cp);
			else if (cp->c == '\"')
				convert_dquote(&cp, sh);
			else if (cp->c == '`')
				convert_bquote(&cp, sh);
			else if (cp->c == '$')
				try_insert_variable(&cp, sh);
			if (!cp)
				break ;
			(*inp) = cp;
			cp = cp->next;
		}
		while ((*inp)->previous)
			(*inp) = (*inp)->previous;
	}
}

int			inp_cmp(t_inp **inp, char *str)
{
	t_inp	*cp;
	int		i;

	i = 0;
	if ((cp = (*inp)))
	{
		while (str[i])
		{
			if (cp && cp->c == str[i])
			{
				cp = cp->next;
				i++;
			}
			else
				break;
			if (!cp && !str[i])
				return (1);
		}
	}
	return (0);
}

int			idenfity_regular(t_inp **inp)
{
	int		type;
	t_inp	*cp;

	type = 0;
	if (inp_cmp(inp, "env") || inp_cmp(inp, "unsetenv") || inp_cmp(inp, "echo"))
		return (type | BUILTIN);
	if (inp_cmp(inp, "cd") || inp_cmp(inp, "setenv") || inp_cmp(inp, "export"))
		return (type | BUILTIN);
	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->c == '=' && cp->previous && cp->next)
				return (type | BUILTIN);
			cp = cp->next;
		}
	}
	return (type | COMMAND);
}

int			check_special(t_inp **inp)
{
	int		type;
	t_inp	*cp;

	type = 0;
	if ((cp = (*inp)))
	{
		if (cp->c == '>')
			type = check_right_arrow(&cp);
		if (cp->c == '<')
			type = check_left_arrow(&cp);
		if (cp->c == '|')
			type = check_pipe_or(&cp);
		if (cp->c == '&')
			type = check_and(&cp);
	}
	return (type);
}

void		print_xx(t_inp **inp, int type)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			ft_putchar(cp->c);
			cp = cp->next;
		}
		if (type & PIPE)
			ft_putstr(" <= PIPE");
		if (type & AND)
			ft_putstr(" <= AND");
		if (type & OR)
			ft_putstr(" <= OR");
		if (type & TOFILE)
			ft_putstr(" <= TOFILE");
		if (type & ATOFILE)
			ft_putstr(" <= ATOFILE");
		if (type & TOEXE)
			ft_putstr(" <= TOEXE");
		if (type & ARGUMENT)
			ft_putstr(" <= ARGUMENT");
		if (type & COMMAND)
			ft_putstr(" <= COMMAND");
		if (type & BUILTIN)
			ft_putstr(" <= BUILTIN");
		if (type & _FILE)
			ft_putstr(" <= FILE");
		custom_return();
	}
}

void		convert_splitted(t_inpl **inpl, t_sh *sh)
{
	t_inpl	*cp;

	if ((cp = (*inpl)))
	{
		while (cp)
		{
			if (cp->type == 0)
			{
				convert_regular(&cp->inp, sh);
				cp->type = idenfity_regular(&cp->inp);
				if (cp->previous && cp->previous->type > 64)
					cp->type = ARGUMENT;
				if (cp->previous && (cp->previous->type & ATOFILE))
					cp->type = _FILE;
				if (cp->previous && (cp->previous->type & TOFILE))
					cp->type = _FILE;
			}
			else if (cp->type == 1)
			{
				if ((cp->type = check_special(&cp->inp)) == -1)
					return ((void)special_error(&cp->inp));
			}
			print_xx(&cp->inp, cp->type);
			cp = cp->next;
		}
	}
}
