/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 01:28:07 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/02 16:56:43 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			check_key(char key)
{
	if (key == '\n'|| key == ' ' || key == '\t'|| key == ';' || key == '>'||
			key == '<' || key == '&'|| key == '|' || key == '$')
		return (0);
	return (1);
}

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
			if (check_key(cp->c))
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
		if (check_key(cp->c))
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

void		remove_key(t_inp **cp, int lg)
{
	while (lg -- > 0)
	{
		ft_putchar('|');
		ft_putchar((*cp)->c);
		if ((*cp)->next)
			*(*cp) = *(*cp)->next;
		else
		{
			*(*cp) = *new_inp('\0');
			break;
		}
	}
	/*if (!key->previous)
	{
		key = key->next;
		free(key->previous);
	}*/
}

void		replace_variable(t_inp **cp, char *get_variable)
{
	int		i;
	t_inp	*new;
	t_inp	*tmp;
	t_inp	*first;

	i = 0;
	new = NULL;
	first = *cp;
	tmp = ((*cp)->previous) ? (*cp)->previous : NULL;
	while (get_variable[i])
	{
		new = new_inp(get_variable[i]);
		if (tmp == NULL)
			new->next = (*cp);
		if (tmp == NULL)
			(*cp)->previous = new;
		if (tmp == NULL)
			(*cp) = new;
		else
			insert_middle(tmp, new);
		tmp = new;
		i++;
	}
}

void		print_variable(t_inp **cp, t_sh *sh)
{
	char	*variable;
	char	*get_variable;
	int		i;
	i = 0;

	if ((variable = parse_variable_name(&(*cp)->next)))
	{
		ft_putnbr(i);
		i++;
		if ((get_variable = get_specific_loc(variable, &sh->loc)) || 
				(get_variable = get_specific_env(variable, &sh->env)))
			replace_variable(cp, get_variable);
		remove_key(cp, ft_strlen(variable));
		if (variable)
			free(variable);
	}
}
