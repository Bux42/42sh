/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 07:15:36 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 08:01:40 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

t_inpl		*allocate_here_cont(void)
{
	t_inpl	*inpl;

	inpl = NULL;
	if (!(inpl = (t_inpl*)malloc(sizeof(t_inpl))))
		return (NULL);
	inpl->next = NULL;
	inpl->previous = NULL;
	inpl->inp = NULL;
	return (inpl);
}

char		*allocate_eof(t_inp **inp)
{
	t_inp	*cp;
	int		len;
	char	*ret;

	ret = NULL;
	cp = *inp;
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
	return (ret);
}

char		**allocate_cont(t_inpl **inp)
{
	int		len;
	char	**ret;

	ret = NULL;
	len = 0;
	while ((*inp)->previous)
		(*inp) = (*inp)->previous;
	while ((*inp)->next)
	{
		len++;
		(*inp) = (*inp)->next;
	}
	while ((*inp)->previous)
		(*inp) = (*inp)->previous;
	if (!(ret = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	ret[len] = NULL;
	return (ret);
}
