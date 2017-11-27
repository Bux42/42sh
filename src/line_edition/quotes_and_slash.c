/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_an_slash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 23:28:18 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/27 04:15:10 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			is_quote_or_slash(char c)
{
	if (c == '\"')
		return (1);
	if (c == '\'')
		return (1);
	if (c == '`')
		return (1);
	return (0);
}

t_inp		*get_closing_quote(t_sh *sh, t_inp **inpl)
{
	t_inp	*cp;
	char	tmp;

	sh->posy = sh->posy;
	tmp = '\0';
	if ((cp = (*inpl)))
	{
		while (cp)
		{
			if (is_quote_or_slash(cp->c))
			{
				if (tmp == '\0')
					tmp = cp->c;
				else if (cp->c == tmp)
					tmp = '\0';
			}
			if (cp->next)
				cp = cp->next;
			else
				break ;
		}
		ft_putchar(tmp);
		if (tmp == '\0')
		{
			if (sh->expected_quote == '\'')
			{
				ft_putstr("quote> ");
				sh->posy = ft_strlen("quote> ") + 2;
			}
			else if (sh->expected_quote == '\"')
			{
				ft_putstr("dquote> ");
				sh->posy = ft_strlen("dquote> ") + 2;
			}
			else if (sh->expected_quote == '`')
			{
				ft_putstr("bquote> ");
				sh->posy = ft_strlen("bquote> ") + 2;
			}
			return (NULL);
		}
		else if (tmp == sh->expected_quote)
			return (cp);
	}
	return (NULL);
}

t_inp		*cut_from_quote(t_sh *sh, t_inp **inpl)
{
	t_inp	*cp;
	char	tmp;

	tmp = '\0';
	if ((cp = (*inpl)))
	{
		while (cp)
		{
			if (is_quote_or_slash(cp->c))
			{
				if (tmp == '\0')
					tmp = cp->c;
				else if (cp->c == tmp)
					tmp = '\0';
			}
			if (cp->next)
				cp = cp->next;
			else
				break ;
		}
	}
	if (tmp != '\0')
	{
		sh->expected_quote = tmp;
		if (tmp == '\'')
		{
			ft_putstr("quote> ");
			sh->posy = ft_strlen("quote> ") + 2;
		}
		else if (tmp == '\"')
		{
			ft_putstr("dquote> ");
			sh->posy = ft_strlen("dquote> ") + 2;
		}
		else if (tmp == '`')
		{
			ft_putstr("bquote> ");
			sh->posy = ft_strlen("bquote> ") + 2;
		}
		return (cp);
	}
	else if (cp->c == '\\')
	{
		ft_putstr("> ");
		sh->posy = ft_strlen("> ") + 2;
		return (cp);
	}
	return (NULL);
}
