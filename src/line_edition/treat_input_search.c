/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:35:54 by videsvau          #+#    #+#             */
/*   Updated: 2018/01/27 03:08:51 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "../builtin/builtin.h"

void		erase_previous_search(t_sh *sh, t_inp **search_pos)
{
	t_inp	*cp;
	int		i;

	i = 0;
	if ((cp = (*search_pos)))
	{
		while (i++ < 3)
			custom_right(sh);
		while (cp)
		{
			ft_putchar(' ');
			check_endline(sh);
			cp = cp->next;
		}
		ft_putchar(' ');
		check_endline(sh);
		cp = (*search_pos);
		while (cp)
		{
			custom_left(sh);
			cp = cp->next;
		}
		i = 0;
		while (i++ < 4)
			custom_left(sh);
	}
}

void		print_match(t_sh *sh)
{
	int		i;

	i = 0;
	while (i++ < 3)
		custom_right(sh);
	while (sh->search_pos->inp->previous)
		sh->search_pos->inp = sh->search_pos->inp->previous;
	while (sh->search_pos->inp)
	{
		ft_putchar(sh->search_pos->inp->c);
		check_endline(sh);
		if (sh->search_pos->inp->next)
			sh->search_pos->inp = sh->search_pos->inp->next;
		else
			break ;
	}
	while (sh->search_pos->inp->previous)
	{
		sh->search_pos->inp = sh->search_pos->inp->previous;
		custom_left(sh);
	}
	i = 0;
	while (i++ < 4)
		custom_left(sh);
	sh->failed_search = 0;
}

void		print_search_forward(t_sh *sh, t_inp **his_search, t_his **his, int repeat)
{
	t_inp	*cp;

	if (repeat || !sh->search_pos)
		sh->search_pos = (*his);
	else if (sh->search_pos->previous)
		sh->search_pos = sh->search_pos->previous;
	else
		sh->failed_search = 1;;
	if ((cp = (*his_search)))
	{
		while (sh->search_pos)
		{
			while (cp->c == sh->search_pos->inp->c)
			{
				if (!cp->next)
					return ((void)print_match(sh));
				if (!sh->search_pos->inp->next)
					break ;
				cp = cp->next;
				sh->search_pos->inp = sh->search_pos->inp->next;
			}
			while (sh->search_pos->inp->previous)
				sh->search_pos->inp = sh->search_pos->inp->previous;
			cp = (*his_search);
			sh->search_pos = sh->search_pos->previous;
		}
	}
	sh->failed_search = 1;;
}

void		print_search_backward(t_sh *sh, t_inp **his_search, t_his **his, int repeat)
{
	t_inp	*cp;

	if (repeat || !sh->search_pos)
		sh->search_pos = (*his);
	else if (sh->search_pos->next)
		sh->search_pos = sh->search_pos->next;
	else
		sh->failed_search = 1;;
	if ((cp = (*his_search)))
	{
		while (sh->search_pos)
		{
			while (cp->c == sh->search_pos->inp->c)
			{
				if (!cp->next)
					return ((void)print_match(sh));
				if (!sh->search_pos->inp->next)
					break ;
				cp = cp->next;
				sh->search_pos->inp = sh->search_pos->inp->next;
			}
			while (sh->search_pos->inp->previous)
				sh->search_pos->inp = sh->search_pos->inp->previous;
			cp = (*his_search);
			if (sh->search_pos->next)
				sh->search_pos = sh->search_pos->next;
			else
				break ;
		}
	}
	sh->failed_search = 1;;
}

void		switch_search_mode(t_sh *sh, t_inp **his_search)
{
	int		i;
	t_inp	*cp;

	i = 14;
	while (i--)
		custom_left(sh);
	if ((cp = (*his_search)))
	{
		while (cp)
		{
			cp = cp->next;
			custom_left(sh);
		}
	}
	if (sh->search == 1)
	{
		ft_putstr_endline("fwd", sh);
		sh->search = 2;
	}
	else if (sh->search == 2)
	{
		ft_putstr_endline("bcl", sh);
		sh->search = 1;
	}
	i = 11;
	while (i--)
		custom_right(sh);
	if ((cp = (*his_search)))
	{
		while (cp)
		{
			cp = cp->next;
			custom_right(sh);
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

void		insert_search(t_sh *sh, t_inp **his_search, t_inp **his_pos)
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
	j = i;
	while (j--)
	{
		ft_putchar(' ');
		check_endline(sh);
	}
	j = i;
	i = 3;
	if (sh->search_pos && (cp = (*his_pos)))
		while (cp && i++)
			cp = cp->next;
	j += i;
	while (i--)
	{
		ft_putchar(' ');
		check_endline(sh);
	}
	while (j--)
		custom_left(sh);
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

void		treat_input_search(t_sh *sh)
{
	sh->pos_at = pos_at(&sh->his_search, 15);
	if (!check_dimentions(sh))
		return ;
	sh->width = tgetnum("co");
	if (!sh->buff[1])
	{
		if (sh->buff[0] > 31 && sh->buff[0] <= 127)
		{
			if (sh->buff[0] != 127)
			{
				ft_putchar(sh->buff[0]);
				check_endline(sh);
				inp_insert_posat(&sh->his_search, sh->buff[0]);
			}
			else
				delete_letter(sh, &sh->his_search);
			ft_putstr_endline("): ", sh);
			custom_left(sh);
			custom_left(sh);
			custom_left(sh);
		}
		else if (sh->buff[0] == 4)
		{
			char *tab[3];
			tab[0] = "exit";
			tab[1] = "0";
			tab[2] = NULL;
			ft_putstr(tgetstr("ve", NULL));
			builtin_exit(tab, &sh->env);
		}
		else if (sh->buff[0] == 27)
			return ((void)insert_search(sh, &sh->his_search, &sh->search_pos->inp));
		if (sh->search_pos)
			erase_previous_search(sh, &sh->search_pos->inp);
		if (sh->buff[0] == 18)
		{
			if (sh->search == 2)
				switch_search_mode(sh, &sh->his_search);
			print_search_backward(sh, &sh->his_search, &sh->history, 0);
		}
		else if (sh->buff[0] == 6)
		{
			if (sh->search == 1)
				switch_search_mode(sh, &sh->his_search);
			print_search_forward(sh, &sh->his_search, &sh->history, 0);
		}
		else if (sh->search == 1)
			print_search_backward(sh, &sh->his_search, &sh->history, 1);
		else if (sh->search == 2)
			print_search_forward(sh, &sh->his_search, &sh->history, 1);
	}
	if (sh->tty)
		tty_debug(sh, &sh->inpl->inp);
	ft_bzero(sh->buff, 6);
}
