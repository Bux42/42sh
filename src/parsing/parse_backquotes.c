/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_backquotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 07:30:31 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/02 16:46:07 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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
			while (cp->inp)
			{
				if (!cp->inp->next)
				{
					if (cp->next)
					{
						if (cp->inp->c == '\\')
							;
						else if (cp->inp->c == '\"')
							inp_insert_posat(&ret, '\n');
						else if (cp->inp->c == '\'')
							inp_insert_posat(&ret, '\n');
						else
							inp_insert_posat(&ret, cp->inp->c);
					}
					else
						inp_insert_posat(&ret, cp->inp->c);
					break ;
				}
				inp_insert_posat(&ret, cp->inp->c);
				cp->inp = cp->inp->next;
			}
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
	while (clean)
	{
		ft_putchar(clean->c);
		clean = clean->next;
	}
	return ;
	ft_putstr("zsh: command not found: ");
	while (clean)
	{
		if (clean->c == '\"')
			sh->context = update_context(sh->context, DQUOTE);
		if (clean->c == '\'')
			sh->context = update_context(sh->context, QUOTE);
		if (clean->c == '`')
			sh->context = update_context(sh->context, BQUOTE);
		if (clean->c == '$')
			;
		if (clean->c == '<')
			;
		update_context_color(sh->context);
		ft_putchar(clean->c);
		clean = clean->next;
	}
}
