/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 01:28:07 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/28 17:49:09 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			check_key(char key)
{
	if (key == '\n'|| key == ' ' || key == '\t'|| key == ';' || key == '>'||
			key == '<' || key == '&'|| key == '|' || key == '$' ||
			key == '\'' || key == '`' || key == '\"')
		return (0);
	return (1);
}

char		*get_variable_name(t_inp **inp)
{
	char	*ret = NULL;
	int		len;
	t_inp	*cp;

	cp = (*inp);
	len = 1;
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

t_inp		*replace_inp(t_inp **inp, char *content)
{
	t_inp	*ret;
	t_inp	*del;
	int		len;

	ret = NULL;
	len = -1;
	while (content[++len])
		inp_insert_posat(&ret, content[len]);
	while ((*inp)->next && check_key((*inp)->next->c))
	{
		del = (*inp);
		(*inp) = (*inp)->next;
		free(del);
		del = NULL;
	}
	free(*inp);
	(*inp) = NULL;
	return (ret);
}

t_inp		*get_end(t_inp **inp)
{
	t_inp	*ret;

	ret = (*inp);
	while (ret->next && check_key(ret->next->c))
		ret = ret->next;
	return (ret->next);
}

t_inp		*relink_inp(t_inp *before, t_inp *after, t_inp *new)
{
	if (before)
		before->next = new;
	new->previous = before;
	while (new->next)
		new = new->next;
	if (after)
		after->previous = new;
	new->next = after;
	return (new);
}

void		try_insert_variable(t_inp **inp, t_sh *sh)
{
	char	*variable;
	char	*content;
	int		i;

	i = -1;
	custom_return();
	if ((*inp)->next && (variable = get_variable_name(inp)))
	{
		if ((content = get_specific_loc(variable, &sh->loc)) ||
				(content = get_specific_env(variable, &sh->env)))
		{
			ft_putchar((*inp)->c);
			while (content[++i])
				inp_insert_posat(inp, content[i]);
			free(content);
		}
		free(variable);
	}
	else
		return ;
	custom_return();
}
