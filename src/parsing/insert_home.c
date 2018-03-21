/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 11:21:15 by drecours          #+#    #+#             */
/*   Updated: 2018/03/21 07:46:24 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	try_insert_home(t_inp **inp, t_sh *sh)
{
	char	*variable;
	t_inp	*before;
	t_inp	*after;
	t_inp	*new;

	if (!(*inp)->previous || ending_char((*inp)->previous->c))
	{
		if ((variable = get_specific_env("HOME=", &sh->env)))
		{
			before = (*inp)->previous;
			after = (*inp)->next;
			new = replace_inp(inp, variable);
			*inp = relink_inp(before, after, new);
			free(variable);
		}
	}
}
