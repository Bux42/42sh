/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:11:02 by videsvau          #+#    #+#             */
/*   Updated: 2016/11/17 15:33:51 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst > src)
		while (len--)
			((char*)dst)[len] = ((char*)src)[len];
	else
		while (i < len)
		{
			((char*)dst)[i] = ((char*)src)[i];
			i++;
		}
	return ((char*)dst);
}
