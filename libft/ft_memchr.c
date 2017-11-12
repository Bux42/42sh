/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:13:16 by videsvau          #+#    #+#             */
/*   Updated: 2016/11/17 21:17:47 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	v;
	unsigned char	*str;
	size_t			i;

	v = (unsigned char)c;
	str = (unsigned char*)s;
	i = 0;
	while (i < n && str[i] != v)
		i++;
	if (i < n && str[i] == v)
		return (&str[i]);
	return (NULL);
}
