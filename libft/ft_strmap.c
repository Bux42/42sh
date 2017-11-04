/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 15:09:23 by videsvau          #+#    #+#             */
/*   Updated: 2016/11/19 17:28:04 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	char	*str;
	short	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (0);
	while (s[i])
	{
		str[i] = f(((char*)s)[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
