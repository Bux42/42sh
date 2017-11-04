/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 05:33:30 by videsvau          #+#    #+#             */
/*   Updated: 2016/11/19 05:33:32 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void	const *content, size_t content_size)
{
	t_list *chain;

	if ((chain = (t_list*)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (!content || !content_size)
	{
		chain->content = NULL;
		chain->content_size = 0;
	}
	else
	{
		chain->content = ft_memalloc(content_size);
		ft_memcpy(chain->content, content, content_size);
		chain->content_size = content_size;
	}
	chain->next = NULL;
	return (chain);
}
