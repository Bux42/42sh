/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 07:30:31 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/10 18:51:10 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "../builtin/builtin.h"

void		inp_insert_posat_remake(t_inp **ret, char c)
{
	t_inp	*tmp;

	if (!*ret)
		*ret = new_inp(c);
	else
	{
		if ((tmp = new_inp(c)))
		{
			tmp->previous = *ret;
			(*ret)->next = tmp;
			(*ret) = (*ret)->next;
		}
	}
}

void		concat_inp(t_inp **inp, t_inp **ret, t_inpl *inpl)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			if (cp->c == '\\' && !cp->next && inpl->next)
				;
			else
				inp_insert_posat_remake(ret, cp->c);
			if (!cp->next)
				if (inpl->next)
					if (cp->c != '\\')
						inp_insert_posat_remake(ret, '\n');
			cp = cp->next;
		}
	}
}

t_inp		*concat_inpl(t_inpl **inpl, t_sh *sh)
{
	t_inpl	*cp;
	t_inp	*ret;
	t_inpl	*tmp;

	ret = NULL;
	sh->posy = sh->posy;
	if ((cp = (*inpl)))
	{
		while (cp)
		{
			concat_inp(&cp->inp, &ret, cp);
			tmp = cp;
			cp = cp->next;
			free_list_from_beginning(&tmp->inp);
			free(tmp);
			tmp = NULL;
		}
		if (!(sh->inpl = allocate_here_cont()))
			return (NULL);
	}
	while (ret && ret->previous)
		ret = ret->previous;
	return (ret);
}

int			empty_inp(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;
	int		i;

	i = 0;
	if (history_exclaim(inp, sh))
		return (0);
	if ((cp = (*inp)))
	{
		while (cp && cp->c)
		{
			if (!is_space(cp->c))
				i++;
			cp = cp->next;
		}
	}
	if (i)
	{
		cp = *inp;
		history_push_front(&sh->history, cp, sh);
	}
	sh->context = 0;
	return (i);
}

void		parse(t_sh *sh)
{
	t_inp	*clean;
	t_inpl	*splitted;
	t_listc	*tok;

	clean = concat_inpl(&sh->inpl, sh);
	tok = NULL;
	if (empty_inp(&clean, sh))
	{
		splitted = NULL;
		split_line(&splitted, &clean, sh);
		if (splitted && convert_splitted(&splitted, sh) != NULL &&
				check_special_surrounding(&splitted))
		{
			if (DEBUG)
				print_splitted(&splitted);
			tokenize_splitted(&splitted, sh, &tok);
			tcsetattr(STDIN_FILENO, TCSADRAIN, &g_old_term);
			execute_tokens(&tok, sh);
			signal_init();
			free_tokens(&tok);
			tcsetattr(STDIN_FILENO, TCSADRAIN, &g_new_term);
		}
		free_inpl(&splitted);
	}
	free_list_from_beginning(&clean);
}
