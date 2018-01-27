/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_search_history_result.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 03:12:11 by videsvau          #+#    #+#             */
/*   Updated: 2018/01/27 05:18:17 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		erase_inp_spaces(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			ft_putchar(' ');
			check_endline(sh);
			cp = cp->next;
		}
	}
}

void		restaure_inp(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			cp->pos = 0;
			ft_putchar(cp->c);
			check_endline(sh);
			if (cp->next)
				cp = cp->next;
			else
				break ;
		}
		cp->pos = 1;
	}
}

void		insert_found_history(t_sh *sh, t_inp **search_pos)
{
	t_inp		*cp;

	if ((cp = (*search_pos)))
	{
		while (cp)
		{
			inp_insert_posat(&sh->inpl->inp, cp->c);
			cp = cp->next;
		}
	}
}

void		hide_history_search(t_sh *sh, t_inp **his_search, t_inp **his_pos)
{
	t_inp	*cp;
	int		i;
	int		j;

	i = 14;
	if ((cp = (*his_search)))
		while (cp && i++)
			cp = cp->next;
	j = i;
	while (j--)
		custom_left(sh);
	print_spaces(i, sh);
	j = i;
	i = 3;
	if (sh->search_pos && (cp = (*his_pos)))
		while (cp && i++)
			cp = cp->next;
	j += i;
	print_spaces(i, sh);
	while (j--)
		custom_left(sh);
}

void		insert_search(t_sh *sh, t_inp **his_search, t_inp **his_pos)
{
	hide_history_search(sh, his_search, his_pos);
	print_prompt(sh);
	if (sh->search_pos && !sh->failed_search)
	{
		free_list_from_beginning(&sh->inpl->inp);
		insert_found_history(sh, &sh->search_pos->inp);
	}
	restaure_inp(sh, &sh->inpl->inp);
	ft_putstr(tgetstr("ve", NULL));
	sh->search = 0;
}
