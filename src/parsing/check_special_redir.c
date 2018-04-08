/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 06:12:50 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 06:15:04 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int		check_left_arrow(t_inp **inp)
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
		else
			return (check_left_aggr(cp));
	}
	return (-1);
}

int		check_out_aggr(t_inp *inp)
{
	int		type;

	type = 0;
	if (inp->c > 47 && inp->c < 51)
		return (type | AGGROUT | AGGR);
	return (-1);
}

int		check_left_aggr(t_inp *cp)
{
	int		type;

	type = 0;
	if (cp->next && cp->next->c == '&')
	{
		cp = cp->next;
		if (cp->next)
		{
			if (cp->next->c > 47 && cp->next->c < 51)
				if (!cp->next->next)
					return (type | LAGGR);
		}
		else
			return (type | LAGGRIN);
	}
	return (-1);
}

int		check_mult_aggr(t_inp **inp)
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
					if (!cp->next->next || ending_char(cp->next->next->c))
						return (type | AGGR);
			}
		}
		if (cp->next && cp->next->c == '<')
			return (check_left_aggr(cp->next));
	}
	return (-1);
}

int		check_right_arrow(t_inp **inp)
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
