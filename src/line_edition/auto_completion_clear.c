/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion_clear.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 22:22:25 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/25 00:59:04 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		free_comp(int i, t_sh *sh)
{
	if (i & 1)
	{
		if (sh->comp_remain)
		{
			free(sh->comp_remain);
			sh->comp_remain = NULL;
		}
	}
	if (i & 2)
	{
		if (sh->comp_debug)
		{
			free(sh->comp_debug);
			sh->comp_debug = NULL;
		}
	}
	if (i & 4)
	{
		if (sh->comp_path)
		{
			free(sh->comp_path);
			sh->comp_path = NULL;
		}
	}
}

void		overwrite_remaining_comp(t_sh *sh, t_inp **inp, int i)
{
	t_inp	*cp;
	int		nb;

	nb = 0;
	if ((cp = get_to_pos(inp)))
	{
		while (cp->next && (nb++ > -1))
		{
			ft_putchar(cp->next->c);
			check_endline(sh);
			cp = cp->next;
		}
		nb += i;
		while (i--)
		{
			ft_putchar(' ');
			check_endline(sh);
		}
		while (nb--)
			custom_left(sh);
	}
}
