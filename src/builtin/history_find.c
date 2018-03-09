/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:40:55 by drecours          #+#    #+#             */
/*   Updated: 2018/03/09 16:22:46 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

int		no_event(int i)
{
	ft_putstr("!: No such event: ");
	ft_putnbr(i);
	custom_return();
	return (-1);
}

int		 get_by_last(t_inp *inp, t_sh *sh, t_inp **input)
{
	char	str[20];
	int		i;
	int		j;
	t_his	*his;

	ft_putstr("1");
	his = sh->history;
	ft_bzero(&str, 20);
	i = 0;
	*input = NULL;
	inp = inp->next;
	while (inp && inp->c && inp->c >= '0' && inp->c <= '9' && i < 19)
	{
		str[i] = inp->c;
		inp = inp->next;
		i++;
	}
	ft_putstr("on traverse");
	i = ft_atoi(str);
	ft_putstr("atoi");
	custom_return();
	j = i;
	if (his && his->inp)
	{
		ft_putstr("present");
		while (i-- > 1 && his && his->next && his->inp)
			his = his->next;
		ft_putstr("next");
		if (i > 1)
			return (no_event(j));
		*input = (his)->inp;
		ft_putstr("give");
		ft_putchar((*input)->c);
	}
	return ((ft_strlen(str) + 1));
}

int		 get_by_first(t_inp *inp, t_sh *sh, t_inp **input)
{
	char	str[20];
	int		i;
	int		j;
	t_his	*his;

	ft_putstr("2");
	his = sh->history;
	ft_bzero(&str, 20);
	i = 0;
	*input = NULL;
	while (inp && inp->c && inp->c >= '0' && inp->c <= '9')
	{
		str[i] = inp->c;
		inp = inp->next;
		i++;
	}
	ft_putstr("on traverse");
	i = ft_atoi(str);
	ft_putstr("atoi");
	custom_return();
	j = i;
	if (his && his->inp)
	{
		ft_putstr("present");

		while (his && his->next && his->next->inp)
			his = his->next;
		ft_putstr("next");

		while (i-- > 1 && his->previous && his->previous->inp)
			his = his->previous;
		ft_putstr("prev");
		if (i > 1)
			return (no_event(j));
		*input = (his)->inp;
		ft_putstr("give");
		ft_putchar((*input)->c);
	}
	return (ft_strlen(str));
}

int		find_in_his(t_inp *his, t_inp *inp, int *i)
{
	static char	*stop = ";:-*^$%\'\"`";
	static char	*last = "@#!";

	while (inp && inp->c && his && his->c)
	{
		if (ft_strchr(stop, inp->c))
			return (0);
		else if (ft_strchr(last, inp->c))
			return ((inp->c == his->c) ? 0 : 1);
		else if (inp->c == '\\' && !(inp->next || ft_isalnum(inp->next->c)))
		{
			if (inp->c == his->c)
				return (0);
			else
				return (-1);
		}
		else if (inp->c != his->c)
				return (-1);
		*i = *i + 1;
		inp = inp->next;
		his = his->next;
	}
	return (0);
}

int		get_by_beg(t_inp *inp, t_sh *sh, t_inp **input)
{
	int		i;
	t_his	*his;
//	t_inp	*cp;
//	t_inp	*h;

	//cp = inp;
	his = sh->history;
	while (his && his->inp)
	{
		//h = his->inp;
		i = 0;
		if (find_in_his(his->inp, inp, &i) == 0)
		{
			*input = (his)->inp;
			return (i);
		}
	//		return (no_event(0));
	//	while (cp && cp->c)
	//	{
	//		
	//		i++;	
	//	}
		his = his->next;
	//	cp = inp;
	}
	return (-1);
}
