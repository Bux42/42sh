/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_bin_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 22:16:58 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/31 22:58:21 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

t_bin		*new_bin(char *name)
{
	t_bin	*ret;

	if (!(ret = (t_bin*)malloc(sizeof(t_bin))))
		return (NULL);
	ret->name = ft_strdup(name);
	ret->next = NULL;
	return (ret);
}

void		bin_push_front(t_bin **bin, char *name)
{
	t_bin	*add;

	if (!*bin)
		*bin = new_bin(name);
	else
	{
		add = new_bin(name);
		add->next = *bin;
		*bin = add;
	}
}
