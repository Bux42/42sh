/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:40:55 by drecours          #+#    #+#             */
/*   Updated: 2018/04/03 15:02:40 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

int		get_by_last(t_inp *inp, t_sh *sh, t_inp **input)
{
	char	str[20];
	int		i;
	int		j;
	t_his	*his;

	his = sh->history;
	ft_bzero(&str, 20);
	i = 0;
	*input = NULL;
	inp = inp->next;
	fill_str(inp, &str);
	i = ft_atoi(str);
	j = i;
	if (his && his->inp)
	{
		while (i-- > 1 && his && his->next && his->inp)
			his = his->next;
		if (i > 1)
			return (no_event(j));
		*input = (his)->inp;
	}
	return ((ft_strlen(str) + 1));
}

int		get_by_first(t_inp *inp, t_sh *sh, t_inp **input)
{
	char	str[20];
	int		i;
	int		j;
	t_his	*his;

	his = sh->history;
	ft_bzero(&str, 20);
	i = 0;
	*input = NULL;
	fill_str(inp, &str);
	i = ft_atoi(str);
	j = i;
	if (his && his->inp)
	{
		while (his && his->next && his->next->inp)
			his = his->next;
		while (i-- > 1 && his->previous && his->previous->inp)
			his = his->previous;
		if (i > 1)
			return (no_event(j));
		*input = (his)->inp;
	}
	return (ft_strlen(str));
}

int		find_in_his(t_inp *his, t_inp *inp, int *i, int flag)
{
	static char	*stop = ";:-*^$%\'\"`";
	static char	*last = "@#!";

	while (inp && inp->c && his && his->c)
	{
		if (ft_strchr(stop, inp->c) ||
				(flag % 2 == 0 && inp->c == '?' && (++(*i)) > -1))
		{
			return (0);
		}
		if (flag > 2)
			ft_putchar(inp->c);
		else if (ft_strchr(last, inp->c))
			return ((inp->c == his->c) ? 0 : 1);
		else if (inp->c == '\\' && !(inp->next || 
					(inp->next && inp->next->c && ft_isalnum(inp->next->c))))
			return ((inp->c == his->c) ? 0 : 1);
		else if (inp->c != his->c)
			return (-1);
		*i = *i + 1;
		inp = inp->next;
		his = his->next;
	}
	if (inp && inp->c)
		return (-1);
	return (0);
}

int		get_by_beg(t_inp *inp, t_sh *sh, t_inp **input)
{
	int		i;
	t_his	*his;

	his = sh->history;
	while (his && his->inp)
	{
		i = 0;
		if (find_in_his(his->inp, inp, &i, 2) == 0)
		{
			*input = (his)->inp;
			return (i);
		}
		his = his->next;
	}
	return (name_no_event(i, inp, 3));
}

int		get_by_name(t_inp *inp, t_sh *sh, t_inp **input)
{
	int		i;
	t_his	*his;
	t_inp	*cp;

	his = sh->history;
	if (!(inp->next))
		return (-1);
	inp = inp->next;
	while (his && his->inp)
	{
		cp = his->inp;
		while (cp)
		{
			i = 0;
			if (find_in_his(cp, inp, &i, 2) == 0)
			{
				*input = (his)->inp;
				return (i + 1);
			}
			cp = cp->next;
		}
		his = his->next;
	}
	return (name_no_event(i, inp, 4));
}
