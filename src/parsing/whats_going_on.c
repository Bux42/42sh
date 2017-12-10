/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whats_going_on.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:55:43 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/10 07:57:18 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char		*parse_variable_name(t_inp **inp)
{
	char	*ret;
	int		len;
	t_inp	*cp;

	len = 0;
	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->c != '\n' && cp->c != ' ' && cp->c != '\t')
				len++;
			else
				break ;
			cp = cp->next;
		}
		if (!len)
			return (NULL);
	}
	if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret[len] = '\0';
	cp = (*inp);
	len = 0;
	while (cp)
	{
		if (cp->c != '\n' && cp->c != ' ' && cp->c != '\t')
			ret[len] = cp->c;
		else
			break ;
		cp = cp->next;
		len++;
	}
	return (ret);
}

int			valid_variable_char(char c)
{
	if (c == '\n')
		return (0);
	if (c == '\t')
		return (0);
	if (c == ' ')
		return (0);
	return (1);
}

void		print_variable(t_inp **cp, t_sh *sh)
{
	char	*variable;
	char	*get_variable;

	ft_putchar('{');
	(*cp) = (*cp)->next;
	variable = parse_variable_name(cp);
	if ((get_variable = get_specific_env(variable, &sh->env)))
		ft_putstr(&get_variable[1]);
	while (*cp)
	{
		if (valid_variable_char((*cp)->c))
		{
			if (!get_variable)
				ft_putchar((*cp)->c);
		}
		else
			break ;
		(*cp) = (*cp)->next;
	}
	ft_putchar('}');
}

void		dquote_inp(t_inp **cp, t_sh *sh)
{
	t_inp	*delimiter;

	delimiter = NULL;
	while ((*cp))
	{
		if ((*cp)->c == '\"' && !odd_slashes(cp))
		{
			(*cp) = (*cp)->next;
			break ;
		}
		else
			inp_insert_posat(&delimiter, (*cp)->c);
		(*cp) = (*cp)->next;
	}
	whats_going_on(&delimiter, sh);
}

void		quote_inp(t_inp **cp, t_sh *sh)
{
	t_inp	*delimiter;

	delimiter = NULL;
	while ((*cp))
	{
		if ((*cp)->c == '\'' && !odd_slashes(cp))
		{
			(*cp) = (*cp)->next;
			break ;
		}
		else
			inp_insert_posat(&delimiter, (*cp)->c);
		(*cp) = (*cp)->next;
	}
	whats_going_on(&delimiter, sh);
}

void		bquote_inp(t_inp **cp, t_sh *sh)
{
	t_inp	*delimiter;

	delimiter = NULL;
	while ((*cp))
	{
		if ((*cp)->c == '`')
		{
			(*cp) = (*cp)->next;
			break ;
		}
		else
			inp_insert_posat(&delimiter, (*cp)->c);
		(*cp) = (*cp)->next;
	}
	whats_going_on(&delimiter, sh);
}

int			working_context(int context, char c)
{
	if (c == '\"')
	{
		if (context & QUOTE)
			return (0);
	}
	if (c == '$')
	{
		if (context & QUOTE)
			return (0);
	}
	if (c == ';')
	{
		if (context & QUOTE)
			return (0);
		if (context & DQUOTE)
			return (0);
	}
	return (1);
}

void		whats_going_on(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->c == '\n')
				while (1)
					;
			if (cp->c == '\"' && !odd_slashes(&cp) && working_context(sh->context, cp->c))
			{
				ft_putchar('[');
				sh->context = update_context(sh->context, DQUOTE);
				dquote_inp(&cp->next, sh);
				sh->context = update_context(sh->context, DQUOTE);
				ft_putchar(']');
			}
			else if (cp->c == '\'')
			{
				ft_putchar('(');
				sh->context = update_context(sh->context, QUOTE);
				quote_inp(&cp->next, sh);
				sh->context = update_context(sh->context, QUOTE);
				ft_putchar(')');
			}
			else if (cp->c == '`' && !odd_slashes(&cp) && working_context(sh->context, cp->c))
			{
				ft_putchar('<');
				sh->context = update_context(sh->context, BQUOTE);
				bquote_inp(&cp->next, sh);
				sh->context = update_context(sh->context, BQUOTE);
				ft_putchar('>');
			}
			else if (cp->c == '$' && !odd_slashes(&cp) && working_context(sh->context, cp->c))
				print_variable(&cp, sh);
			else if (cp->c == ';' && !odd_slashes(&cp) && working_context(sh->context, cp->c))
				custom_return();
			else
				ft_putchar(cp->c);
			if (cp)
				cp = cp->next;
			else
				break ;
		}
	}
}
