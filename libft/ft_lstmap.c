/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 19:41:00 by videsvau          #+#    #+#             */
/*   Updated: 2016/11/21 18:23:56 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*i;
	t_list	*tmp;
	t_list	*tmp2;

	tmp2 = f(lst);
	i = ft_lstnew(tmp2->content, tmp2->content_size);
	if (i)
		tmp = i;
	lst = lst->next;
	while (lst)
	{
		tmp2 = f(lst);
		if (!(tmp->next = ft_lstnew(tmp2->content, tmp2->content_size)))
			return (NULL);
		tmp = tmp->next;
		lst = lst->next;
	}
	return (i);
}
