/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 01:28:07 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/20 16:23:05 by videsvau         ###   ########.fr       */
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
			if (cp->c != '\n' && cp->c != ' ' && cp->c != '\t' && cp->c != ';')
				len++;
			else
				break ;
			cp = cp->next;
		}
		if (!len)
			return (NULL);
	}
	if (!(ret = (char*)malloc(sizeof(char) * (len + 2))))
		return (NULL);
	ret[len + 1] = '\0';
	ret[len] = '=';
	cp = (*inp);
	len = 0;
	while (cp)
	{
		if (cp->c != '\n' && cp->c != ' ' && cp->c != '\t' && cp->c != ';')
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
	int		i;

	if ((variable = parse_variable_name(&(*cp)->next)))
	{
		if ((get_variable = get_specific_env(variable, &sh->env)))
		{
			i = ft_strlen(variable);
			while (i--)
				(*cp) = (*cp)->next;
			ft_putstr(&get_variable[1]);
		}
		free(variable);
	}
}
