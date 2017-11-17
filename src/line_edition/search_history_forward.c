/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_history_forward.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:32:05 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/17 16:24:20 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		search_history_forward(t_sh *sh, t_his **history)
{
	if ((history))
	{
		if (sh->inpl->inp)
			free_list_from_beginning(&sh->inpl->inp);
		if ((*history)->previous)
			(*history) = (*history)->previous;
		search_history_inp(sh, &(*history)->inp);
	}
}
