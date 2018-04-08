/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 08:49:39 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 12:36:27 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

t_listc		*new_token(void)
{
	t_listc	*ret;

	if (!(ret = (t_listc*)malloc(sizeof(t_listc))))
		return (NULL);
	ret->func = NULL;
	ret->cont = NULL;
	ret->redirs = NULL;
	ret->prev = NULL;
	ret->next = NULL;
	ret->sep_type = 0;
	ret->nb_arg = 0;
	return (ret);
}

void		tok_push_back(t_listc **tok, t_listc *add)
{
	t_listc	*last;

	if (!*tok)
		*tok = add;
	else
	{
		last = *tok;
		while (last->next)
			last = last->next;
		add->prev = last;
		last->next = add;
	}
	if (DEBUG)
		ft_putnbr(add->sep_type);
}

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
