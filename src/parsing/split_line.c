/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:36:59 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/23 19:22:19 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			right_context(int flag)
{
	if (flag & QUOTE)
		return (0);
	if (flag & BQUOTE)
		return (0);
	if (flag & DQUOTE)
		return (0);
	return (1);
}

int			check_quoting(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (1);
	if (c == '`')
		return (1);
	return (0);
}

void		add_token(t_inpl **inpl, t_inp **cp, t_sh *sh)
{
	if (!((*inpl)->inp = (t_inp*)malloc(sizeof(t_inp))))
		return ;
	while (*cp)
	{
		if (!(sh->context & QUOTE) && (*cp)->c == '\\')
			if ((*cp)->next && (*cp)->next->next)
				(*cp) = (*cp)->next->next;
		if (check_quoting((*cp)->c))
			sh->context = try_update_context((*cp)->c, sh->context);
		if (right_context(sh->context) && !check_key((*cp)->c))
			break ;
		ft_putchar((*cp)->c);
		inp_insert_posat(&(*inpl)->inp, (*cp)->c);
		(*cp) = (*cp)->next;
	}
	if (!((*inpl)->next = (t_inpl*)malloc(sizeof(t_inpl))))
		return ;
	(*inpl)->next->previous = (*inpl);
	(*inpl) = (*inpl)->next;
	custom_return();
}
// base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e 's/1/Yes/g' -e 's/0/No/g'"

void		add_special_token(t_inpl **inpl, t_inp **cp, t_sh *sh)
{
	if (!((*inpl)->inp = (t_inp*)malloc(sizeof(t_inp))))
		return ;
	if (inpl && cp &&sh)
		;
	while (*cp)
	{
		if ((*cp)->c == '\\')
			if ((*cp)->next && (*cp)->next->next)
				(*cp) = (*cp)->next->next;
		if ((*cp)->c == ' ')
			break ;
		ft_putchar((*cp)->c);
		inp_insert_posat(&(*inpl)->inp, (*cp)->c);
		(*cp) = (*cp)->next;
	}
	if (!((*inpl)->next = (t_inpl*)malloc(sizeof(t_inpl))))
		return ;
	(*inpl)->next->previous = (*inpl);
	(*inpl) = (*inpl)->next;
	custom_return();
}

int			special_tok(char c)
{
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	if (c == '|')
		return (1);
	if (c == '&')
		return (1);
	return (0);
}

void		split_line(t_inpl *inpl, t_inp **clean, t_sh *sh)
{
	t_inp	*cp;

	cp = *clean;
	while (cp)
	{
		while (cp && cp->c == ' ')
			cp = cp->next;
		if (special_tok(cp->c))
			add_special_token(&inpl, &cp, sh);
		else
			add_token(&inpl, &cp, sh);
		if (cp && cp->next)
			cp = cp->next;
	}
}
