/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 22:03:14 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/26 19:57:46 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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

int			check_left_arrow(t_inp **inp)
{
	t_inp	*cp;
	int		type;

	type = 0;
	if ((cp = (*inp)))
	{
		if (!cp->next)
			return (type | TOEXE);
		else if (cp->next->c == '<' && !cp->next->next)
			return (type | HERE);
	}
	return (-1);
}

int			check_out_aggr(t_inp *inp)
{
	int		type;

	type = 0;
	if (inp->c > 47 && inp->c < 51)
		return (type | AGGROUT | AGGR);
	return (-1);
}

int			check_mult_aggr(t_inp **inp)
{
	int		type;
	t_inp	*cp;

	type = 0;
	if ((cp = (*inp)))
	{
		if (cp->next && cp->next->c == '>')
		{
			cp = cp->next;
			if (cp->next && cp->next->c == '&')
			{
				if (!cp->next->next)
					return (type | AGGRFILE | AGGR);
				cp = cp->next;
				if (cp->next->c > 47 && cp->next->c < 51)
					if (!cp->next->next)
						return (type | AGGR);
			}
		}
	}
	return (-1);
}

int			check_right_arrow(t_inp **inp)
{
	t_inp	*cp;
	int		type;

	type = 0;
	if ((cp = (*inp)))
	{
		if (!cp->next)
			return (type | TOFILE);
		if (cp->next && cp->next->c == '>' && !cp->next->next)
			return (type | ATOFILE);
		if (cp->next && cp->next->c == '&')
		{
			if (cp->next->next)
				return (check_out_aggr(cp->next->next));
			else
				return (type | AGGRFILE | AGGR | AGGROUT);
		}
	}
	return (-1);
}
