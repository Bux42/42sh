/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 08:53:51 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/07 10:24:16 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char		*get_ending_here(t_inp **inp)
{
	int		len;
	t_inp	*cp;
	char	*ret = NULL;

	if ((cp = (*inp)))
	{
		len = 0;
		while (cp)
		{
			if (cp->c > 31)
				len++;
			cp = cp->next;
		}
		if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		ret[len] = '\0';
		cp = *inp;
		len = 0;
		while (cp)
		{
			if (cp->c > 31)
				ret[len] = cp->c;
			len++;
			cp = cp->next;
		}
	}
	return (ret);
}

void		print_heredoc(char *ending, t_sh *sh)
{
	ft_bzero(sh->buff, 6);
	sh->width = tgetnum("co");
	custom_return();
	sh->posy = 1;
	print_str("heredoc('", sh);
	print_str(ending, sh);
	print_str("') ", sh);
	sh->prompt_len = sh->posy;
	if (sh->prompt_len > sh->width)
		sh->posy = sh->prompt_len % sh->width;
}

char		*here_to_char(t_inp **inp)
{
	char	*ret;
	t_inp	*cp;
	int		len;

	len = 0;
	ret = NULL;
	if ((cp = (*inp)))
	{
		while (cp)
		{
			len++;
			cp = cp->next;
		}
		if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		ret[len] = '\0';
		cp = *inp;
		len = 0;
		while (cp)
		{
			ret[len] = cp->c;
			cp = cp->next;
			len++;
		}
	}
	return (ret);
}

char		**inpl_to_here(t_inpl **inpl)
{
	t_inpl	*cp;
	char	**cont;
	int		len;

	cont = NULL;
	if ((cp = (*inpl)))
	{
		len = 0;
		while (cp && cp->previous)
			cp = cp->previous;
		while (cp->next)
		{
			len++;
			cp = cp->next;
		}
		if (!(cont = (char**)malloc(sizeof(char*) * (len + 1))))
			return (NULL);
		while (cp && cp->previous)
			cp = cp->previous;
		len = 0;
		while (cp->next)
		{
			cont[len] = here_to_char(&cp->inp);
			len++;
			cp = cp->next;
		}
		while (cp && cp->previous)
			cp = cp->previous;
		free_inpl(&cp);
		cont[len] = NULL;
	}
	return (cont);
}

char		**get_heredoc(t_inp **inp)
{
	char	**here;
	t_inpl	*inpl;
	int		ret;
	char	*ending;
	int		test;

	ret = 1;
	here = NULL;
	inpl = NULL;
	if (!(inpl = (t_inpl*)malloc(sizeof(t_inpl))))
		return (NULL);
	inpl->next = NULL;
	inpl->previous = NULL;
	inpl->inp = NULL;
	if ((ending = get_ending_here(inp)))
	{
		print_heredoc(ending, g_sh);
		while (ret && (test = read(1, g_sh->buff, 6)))
		{
			if (test == -1)
			{
				free(ending);
				free(inpl);
				return (NULL);
			}
			ret = check_pasted_here(g_sh, &inpl, ending);
			ft_bzero(g_sh->buff, 6);
		}
		custom_return();
		here = inpl_to_here(&inpl);
		free(ending);
	}
	return (here);
}
