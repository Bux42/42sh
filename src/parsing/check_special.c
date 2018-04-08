/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 22:03:14 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 12:29:50 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			redir(t_inp *cp)
{
	if (cp->c > 47 && cp->c < 58)
	{
		if (cp->next && cp->next->c == '>')
			return (1);
		if (cp->next && cp->next->c == '<')
			return (1);
	}
	return (0);
}

void		*special_error(t_inp **inp)
{
	t_inp	*cp;

	write(2, "21sh: parse error near ", 23);
	if ((cp = (*inp)))
	{
		while (cp)
		{
			write(2, &cp->c, 1);
			cp = cp->next;
		}
		custom_return();
	}
	return (NULL);
}

int			check_semicolon(t_inp **inp)
{
	int		type;

	type = 0;
	if (!(*inp)->next)
		return (type | SEMICOLON);
	return (-1);
}

int			check_and(t_inp **inp)
{
	t_inp	*cp;
	int		type;

	type = 0;
	if ((cp = (*inp)))
	{
		if (cp->next && cp->next->c == '&' && !cp->next->next)
			return (type | AND);
	}
	return (-1);
}

int			check_pipe_or(t_inp **inp)
{
	t_inp	*cp;
	int		type;

	type = 0;
	if ((cp = (*inp)))
	{
		if (!cp->next)
			return (type | PIPE);
		if (cp->next->c == '|' && !cp->next->next)
			return (type | OR);
	}
	return (-1);
}
