/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion_clear.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 22:22:25 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/26 08:35:52 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		rewrite_beginning(t_sh *sh, t_inp *cp)
{
	int		dec1;
	int		dec2;

	dec1 = ft_strlen(sh->comp_remain) + 1;
	dec2 = 0;
	while (cp)
	{
		ft_putchar(cp->c);
		check_endline(sh);
		dec1++;
		dec2++;
		cp = cp->next;
	}
	print_spaces(dec1, sh);
	dec1 += dec2;
	while (dec1--)
		custom_left(sh);
	free_comp(3, sh);
}

void		free_null(char **str)
{
	if ((*str))
	{
		free((*str));
		(*str) = NULL;
	}
}

void		print_spaces(int nb, t_sh *sh)
{
	while (nb-- > 0)
	{
		ft_putchar(' ');
		check_endline(sh);
	}
}

void		free_comp(int i, t_sh *sh)
{
	if (i & 8)
		erase_completion(sh, &sh->inpl->inp);
	if (i & 1)
		free_null(&sh->comp_remain);
	if (i & 2)
		free_null(&sh->comp_debug);
	if (i & 4)
		free_null(&sh->comp_path);
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
		print_spaces(i, sh);
		while (nb--)
			custom_left(sh);
	}
}
