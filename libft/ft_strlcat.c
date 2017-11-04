/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 00:42:04 by videsvau          #+#    #+#             */
/*   Updated: 2016/11/22 21:09:38 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t i;
	size_t j;

	i = ft_strlen(dst);
	j = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[j])
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		if (size > i - j)
			dst[i] = '\0';
	}
	return ((size < i - j ? size : i - j) + ft_strlen(src));
}
