/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 12:13:40 by videsvau          #+#    #+#             */
/*   Updated: 2016/11/22 16:00:59 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int		ft_lstcount(t_list **alst)
{
	int		i;
	t_list	*chain;

	i = 1;
	chain = *alst;
	if (!chain)
		return (0);
	while (chain->next)
	{
		i++;
		chain = chain->next;
	}
	return (i);
}
