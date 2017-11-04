/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 13:57:15 by videsvau          #+#    #+#             */
/*   Updated: 2016/11/21 14:03:22 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	ft_list_push_back(t_list **alst, void *content, size_t size)
{
	t_list *first;
	t_list *after;

	first = ft_lstnew(content, size);
	if (!*alst)
		*alst = first;
	else
	{
		after = *alst;
		while (after->next)
			after = after->next;
		after->next = first;
	}
}
