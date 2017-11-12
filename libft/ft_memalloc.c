/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 20:09:48 by videsvau          #+#    #+#             */
/*   Updated: 2016/11/22 21:21:04 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_memalloc(size_t size)
{
	void *ret;

	if (!(ret = (void *)malloc(sizeof(char) * size)))
		return (NULL);
	ft_bzero(ret, size);
	return (ret);
}
