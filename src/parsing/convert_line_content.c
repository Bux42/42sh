/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_line_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 14:30:45 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/22 18:26:10 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		convert_line_content(t_inp **inp, t_sh *sh)
{
	t_inp	*tmp;

	tmp = NULL;
	while (*inp)
	{
		if ((*inp)->c == '$')
			try_insert_variable(inp, sh);
		tmp = *inp;
		(*inp) = (*inp)->next;
	}
	while (tmp && tmp->previous)
		tmp = tmp->previous;
	*inp = tmp;
}
