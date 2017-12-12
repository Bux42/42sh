/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_an_slash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 23:28:18 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/12 08:48:44 by videsvau         ###   ########.fr       */
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

void		print_quote(char quote, t_sh *sh)
{
	if (quote == '\'')
	{
		ft_putstr("quote> ");
		sh->posy = ft_strlen("quote> ") + 1;
	}
	else if (quote == '\"')
	{
		ft_putstr("dquote> ");
		sh->posy = ft_strlen("dquote> ") + 1;
	}
	else if (quote == '`')
	{
		ft_putstr("bquote> ");
		sh->posy = ft_strlen("bquote> ") + 1;
	}
}

int			odd_slashes(t_inp **inp)
{
	t_inp	*cp;
	int		count;

	count = 0;
	if ((cp = (*inp)))
	{
		while (cp->previous)
		{
			if (cp->previous->c == '\\')
				count++;
			else
				break ;
			cp = cp->previous;
		}
	}
	return (count % 2);
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
			if (is_quote_or_slash(cp->c) && !odd_slashes(&cp))
			{
				if (tmp == '\0')
					tmp = cp->c;
				else if (cp->c == tmp)
					tmp = '\0';
				else
					tmp = cp->c;
			}
			if (cp->next)
				cp = cp->next;
			else
				break ;
		}
		if (tmp != sh->expected_quote)
		{
			print_quote(sh->expected_quote, sh);
			return (NULL);
		}
		else if (tmp != sh->expected_quote)
		{
			sh->expected_quote = tmp;
			print_quote(tmp, sh);
			return (NULL);
		}
		else if (tmp == sh->expected_quote)
		{
			sh->expected_quote = '\0';
			if (cp->c == '\\' && !odd_slashes(&cp))
			{
				ft_putstr("> ");
				sh->posy = ft_strlen("> ") + 2;
				return (NULL);
			}
			return (cp);
		}
	}
	print_quote(sh->expected_quote, sh);
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
			if (is_quote_or_slash(cp->c) && !odd_slashes(&cp))
			{
				if (tmp == '\0')
					tmp = cp->c;
				else if (cp->c == tmp)
					tmp = '\0';
			}
			else if (tmp == '\'' && cp->c == tmp && odd_slashes(&cp))
				tmp = '\0';
			if (cp->next)
				cp = cp->next;
			else
				break ;
		}
	}
	if (tmp != '\0')
	{
		sh->expected_quote = tmp;
		print_quote(tmp, sh);
		return (cp);
	}
	if (cp && cp->c == '\\' && !odd_slashes(&cp))
	{
		ft_putstr("> ");
		sh->posy = ft_strlen("> ") + 2;
		return (cp);
	}
	return (NULL);
}
