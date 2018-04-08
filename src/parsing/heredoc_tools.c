/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 07:15:36 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 07:21:05 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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
