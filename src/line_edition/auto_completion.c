/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 20:23:08 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/09 13:25:57 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		insert_completion(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		i;

	if (sh->comp_remain)
	{
		if ((cp = get_to_pos(inp)))
		{
			i = -1;
			while (sh->comp_remain[++i])
			{
				inp_insert_posat(&sh->inpl->inp, sh->comp_remain[i]);
				ft_putchar(sh->comp_remain[i]);
				check_endline(sh);
				overwrite_remaining(sh, &sh->inpl->inp);
			}
		}
		free_comp(3, sh);
	}
}

void		do_shit(t_inp **inp)
{
	t_inp	*cp;

	cp = (*inp);
	while (cp)
	{
		ft_putchar_fd(cp->c, g_sh->tty_fd);
		cp = cp->next;
	}
}

int			left_word_len(int *slash, t_inp **cp)
{
	int		i;

	i = 1;
	while ((*cp)->previous && !is_space((*cp)->previous->c))
	{
		if ((*cp)->previous->c == '/')
		{
			(*slash)++;
			break ;
		}
		i++;
		(*cp) = (*cp)->previous;
	}
	return (i);
}

char		*get_left_word(t_inp *cp, t_sh *sh)
{
	char	*ret;
	int		i;
	int		slash;

	slash = 0;
	free_comp(6, sh);
	if ((i = left_word_len(&slash, &cp)) == -1)
		return (NULL);
	if (!(ret = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (slash)
		sh->comp_path = get_comp_path(sh, cp);
	else
		sh->comp_path = ft_strdup("./");
	ret[i] = '\0';
	i = 0;
	while (cp && !is_space(cp->c))
	{
		ret[i++] = cp->c;
		cp = cp->next;
	}
	return (ret);
}

void		erase_completion(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		dec;

	if (!sh->comp_remain)
		return ;
	dec = 0;
	if ((cp = get_to_pos(inp)))
	{
		while (cp)
		{
			dec++;
			cp = cp->next;
		}
	}
	dec += ft_strlen(sh->comp_remain);
	free_comp(1, sh);
	print_spaces(dec, sh);
	while (dec--)
		custom_left(sh);
	overwrite_remaining(sh, inp);
}

void		autocompletion(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;

	if ((cp = get_to_pos(inp)) && cp->pos != 2)
	{
		if (!cp->next || is_space(cp->next->c))
		{
			if (!is_space(cp->c))
			{
				if (cp->c != '/')
				{
					if ((sh->comp_debug = get_left_word(cp, sh)))
						print_completion(sh, &sh->inpl->inp);
				}
				else
					free_comp(11, sh);
			}
			else
				free_comp(11, sh);
		}
		else
			free_comp(3, sh);
	}
	else if (sh->comp_remain)
		rewrite_beginning(sh, cp);
}
