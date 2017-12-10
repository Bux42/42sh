/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whats_going_on.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:55:43 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/10 05:08:38 by videsvau         ###   ########.fr       */
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
		if ((*cp)->c != '\n' && (*cp)->c != ' ' && (*cp)->c != '\t')
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

void		whats_going_on(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;
	int		quote;
	int		dquote;

	quote = 0;
	dquote = 0;
	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->c == '\"' && !quote && !odd_slashes(&cp))
			{
				if (dquote)
				{
					ft_putchar(']');
					dquote = 0;
				}
				else
				{
					ft_putchar('[');
					dquote = 1;
				}
			}
			else if (cp->c == '\'' && !dquote)
			{
				if (quote)
				{
					ft_putchar(')');
					quote = 0;
				}
				else
				{
					if (!odd_slashes(&cp))
					{
						ft_putchar('(');
						quote = 1;
					}
				}
			}
			else if (cp->c == '$' && !quote && !odd_slashes(&cp))
				print_variable(&cp, sh);
			else
				ft_putchar(cp->c);
			if (cp)
				cp = cp->next;
			else
				break ;
		}
		custom_return();
	}
}
