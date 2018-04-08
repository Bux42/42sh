/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 01:28:07 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 12:24:15 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char		*get_variable_name(t_inp **inp)
{
	char	*ret;
	int		len;
	t_inp	*cp;

	cp = (*inp);
	len = 1;
	ret = NULL;
	while (cp->next && check_key(cp->next->c))
	{
		cp = cp->next;
		len++;
	}
	if (!len || !(ret = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	ret[len] = '\0';
	ret[len - 1] = '=';
	len = 0;
	cp = (*inp);
	while (cp->next && check_key(cp->next->c))
	{
		ret[len] = cp->next->c;
		len++;
		cp = cp->next;
	}
	return (ret);
}

t_inp		**free_variable_name(t_inp **inp)
{
	t_inp	*tmp;

	tmp = (*inp);
	(*inp) = (*inp)->next;
	free(tmp);
	while (*inp && check_key((*inp)->c))
	{
		tmp = (*inp);
		(*inp) = (*inp)->next;
		free(tmp);
	}
	return (inp);
}

t_inp		*variable(char *value)
{
	t_inp	*ret;
	int		i;

	ret = NULL;
	i = -1;
	while (value[++i])
		inp_insert_posat(&ret, value[i]);
	return (ret);
}

void		insert_and_replace(t_inp **inp, char *value)
{
	t_inp	*before;
	t_inp	*add;

	before = (*inp)->previous;
	inp = free_variable_name(inp);
	add = variable(value);
	if (before)
		before->next = add;
	add->previous = before;
	while (add->next)
		add = add->next;
	if (*inp)
		(*inp)->previous = add;
	add->next = *inp;
	*inp = add;
}

void		try_insert_variable(t_inp **inp, t_sh *sh)
{
	char	*variable;
	char	*content;

	if ((*inp)->next && (variable = get_variable_name(inp)))
	{
		if ((content = get_specific_loc(variable, &sh->loc)) ||
				(content = get_specific_env(variable, &sh->env)))
		{
			insert_and_replace(inp, content);
			free(content);
		}
		free(variable);
	}
	else
		return ;
}
