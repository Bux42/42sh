/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_tools_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 08:30:04 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 13:18:06 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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
				break ;
			if (!cp && !str[i])
				return (1);
		}
	}
	return (0);
}

void		str_to_inp(char *str, t_inp **inp)
{
	int		i;
	t_inp	*cp;
	t_inp	*tmp;

	i = -1;
	cp = *inp;
	while (str[++i])
	{
		if (str[i] > 31)
		{
			if (!cp)
			{
				cp = new_inp(str[i]);
				*inp = cp;
			}
			else
			{
				tmp = new_inp(str[i]);
				cp->next = tmp;
				tmp->previous = cp;
				cp = cp->next;
			}
		}
	}
}

t_his		*new_his(char *str)
{
	t_his	*ret;

	ret = NULL;
	if (!(ret = (t_his*)malloc(sizeof(t_his))))
		return (NULL);
	ret->next = NULL;
	ret->previous = NULL;
	ret->inp = NULL;
	str_to_inp(str, &ret->inp);
	return (ret);
}

int			inp_to_inp_cmp(t_inp **inp1, t_inp **inp2)
{
	t_inp	*cp1;
	t_inp	*cp2;

	if ((cp1 = (*inp1)))
	{
		if ((cp2 = (*inp2)))
		{
			while (cp1 && cp2)
			{
				if (cp1->c != cp2->c)
					return (0);
				cp1 = cp1->next;
				cp2 = cp2->next;
			}
			if ((!cp1 && cp2) || (cp1 && !cp2))
				return (0);
		}
	}
	return (1);
}

t_inp		*inp_dup(t_inp **inp)
{
	t_inp	*ret;
	t_inp	*cp;

	ret = NULL;
	if ((cp = (*inp)))
	{
		ret = new_inp(cp->c);
		while (cp->next)
		{
			ret->next = new_inp(cp->next->c);
			ret->next->previous = ret;
			ret = ret->next;
			cp = cp->next;
		}
		while (ret->previous)
			ret = ret->previous;
	}
	return (ret);
}
