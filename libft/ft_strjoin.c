/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:29:44 by videsvau          #+#    #+#             */
/*   Updated: 2016/11/19 17:23:26 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	lenght;
	int		i;

	i = 0;
	if (!s2 || !s1)
		return (NULL);
	lenght = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(str = (char*)malloc(sizeof(char) * lenght)))
		return (NULL);
	lenght = -1;
	while (++lenght < ft_strlen(s1))
	{
		str[i] = s1[lenght];
		i++;
	}
	lenght = 0;
	while (lenght < ft_strlen(s2))
	{
		str[i] = s2[lenght];
		lenght++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
