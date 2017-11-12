/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:37:41 by videsvau          #+#    #+#             */
/*   Updated: 2016/11/19 18:26:36 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static size_t	ft_endsp(const char *s)
{
	size_t i;

	i = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i--;
	return (ft_strlen(s) - 1 - i);
}

static size_t	ft_begsp(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	return (i);
}

static int		ft_letter(const char *s)
{
	int i;

	if (ft_begsp(s) == ft_strlen(s))
		return (0);
	i = ft_strlen(s) - ft_begsp(s) - ft_endsp(s);
	return (i);
}

char			*ft_strtrim(const char *s)
{
	char	*str;
	size_t	i;
	size_t	let;

	if (!s)
		return (NULL);
	i = ft_begsp(s);
	let = ft_strlen(s) - 1 - ft_begsp(s) - ft_endsp(s);
	if (!(str = (char*)malloc(sizeof(char) * ft_letter(s) + 1)))
		return (0);
	if (ft_letter(s) > 0)
	{
		while (i < ft_strlen(s) - ft_endsp(s))
		{
			str[i - ft_begsp(s)] = s[i];
			i++;
		}
	}
	str[ft_letter(s)] = '\0';
	return (str);
}
