/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 23:12:33 by videsvau          #+#    #+#             */
/*   Updated: 2016/11/05 23:13:47 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	short i;

	i = 0;
	while (s[i])
		i++;
	while (i > 0 && s[i] != c)
		i--;
	if (s[i] == c)
		return (&((char*)s)[i]);
	return (0);
}
