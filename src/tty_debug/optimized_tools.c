/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 15:45:20 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 16:40:56 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		custom_itoa(int *pos, char *buff, int nb)
{
	char	buff2[get_len(nb) + 1];
	int		len;
	int		tmp;

	len = get_len(nb);
	buff2[len] = '\0';
	tmp = nb;
	if (nb < 0)
	{
		buff2[0] = '-';
		tmp = -tmp;
	}
	while (tmp > 9)
	{
		buff2[len - 1] = tmp % 10 + 48;
		tmp /= 10;
		len--;
	}
	buff2[len - 1] = tmp % 10 + 48;
	opti_strcat(pos, buff, buff2, 0);
}

int			special_char(char c)
{
	if (c == '\"')
		return (1);
	if (c == '`')
		return (1);
	if (c == '\\')
		return (1);
	if (c == '$')
		return (1);
	return (0);
}

void		add_close(char *buff, t_close **close)
{
	t_close *cp;

	cp = *close;
	while (cp)
	{
		if (cp->flag & QUOTE)
			ft_strcat(buff, "quote, ");
		if (cp->flag & DQUOTE)
			ft_strcat(buff, "dquote, ");
		cp = cp->next;
	}
}

void		opti_strcat(int *pos, char *buff, char *add, int esc)
{
	int		i;

	i = -1;
	if (esc == 2 && (*pos) + 50 < TTY_MAX)
	{
		if (special_char(add[0]))
			buff[(*pos)++] = '\\';
		buff[(*pos)++] = add[0];
	}
	else if (add)
	{
		while (add[++i] && (*pos) + 50 < TTY_MAX)
		{
			if (esc && special_char(add[i]))
				buff[(*pos)++] = '\\';
			buff[(*pos)++] = add[i];
		}
	}
	buff[(*pos)] = '\0';
}

int			get_len(int nb)
{
	int		len;

	len = 1;
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while (nb /= 10)
		len++;
	return (len);
}
