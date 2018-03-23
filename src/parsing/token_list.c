/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 08:49:39 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/23 14:34:51 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		free_heredoc(t_redir *tmp)
{
	int		i;

	i = 0;
	while (tmp->heredoc[i])
	{
		free(tmp->heredoc[i]);
		i++;
	}
	free(tmp->heredoc);
}

void		free_redirs(t_redir **redir)
{
	t_redir	*cp;
	t_redir	*tmp;
	int		i;

	if ((cp = (*redir)))
	{
		while (cp)
		{
			tmp = cp;
			cp = cp->next;
			if (tmp->file)
			{
				free(tmp->file);
				tmp->file = NULL;
			}
			if (tmp->redir[1] == HEREDOC)
				free_heredoc(tmp);
			i = -1;
			free(tmp);
			tmp = NULL;
		}
	}
}

void		free_tokens(t_listc **tok)
{
	t_listc	*cp;
	t_listc	*tmp;

	if ((cp = (*tok)))
	{
		while (cp)
		{
			tmp = cp;
			cp = cp->next;
			if (tmp->cont)
				free_char_array(tmp->cont);
			if (tmp->redirs)
				free_redirs(&tmp->redirs);
			free(tmp);
			tmp = NULL;
		}
	}
}
