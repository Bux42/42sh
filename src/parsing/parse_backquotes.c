/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_backquotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 07:30:31 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/08 20:32:32 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		concat_inp(t_inp **inp, t_inp **ret, t_inpl *inpl)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp)
		{
			inp_insert_posat(ret, cp->c);
			if (!cp->next)
				if (inpl->next)
					if (cp->c != '\\')
						inp_insert_posat(ret, '\n');
			cp = cp->next;
		}
	}
}

t_inp		*concat_inpl(t_inpl **inpl, t_sh *sh)
{
	t_inpl	*cp;
	t_inp	*ret;

	ret = NULL;
	sh->posy = sh->posy;
	if ((cp = (*inpl)))
	{
		while (cp)
		{
			concat_inp(&cp->inp, &ret, cp);
			/*while (cp->inp)
			{
				inp_insert_posat(&ret, cp->inp->c);
				if (!cp->inp->next)
					if (cp->next)
						if (cp->inp->c != '\\')
							inp_insert_posat(&ret, '\n');
				cp->inp = cp->inp->next;
			}*/
			cp = cp->next;
		}
	}
	return (ret);
}

int			update_context(int context, int flag)
{
	if (context & flag)
		return (context - flag);
	return (context | flag);
}

void		update_context_color(int context)
{
	ft_putstr("\x1b[0m");
	if (context & DQUOTE)
		ft_putstr("\x1b[36m");
}

void		parse(t_sh *sh)
{
	t_inp	*clean;

	clean = concat_inpl(&sh->inpl, sh);
	whats_going_on(&clean);
	free_list_from_beginning(&clean);
	return ;
}
