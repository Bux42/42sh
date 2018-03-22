/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 23:08:05 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/22 10:26:05 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int			count_words(const char *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (j);
}

char		*get_word_2(const char *s, int i, int len)
{
	char	*ret;

	if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret[len] = '\0';
	while (len--)
		ret[len] = s[--i];
	return (ret);
}

char		*get_word(const char *s, int pos, char c)
{
	int		i;
	int		j;
	int		len;
	char	*ret;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			len = 0;
			while (s[i] && s[i] != c)
			{
				len++;
				i++;
			}
			if (j == pos)
				ret = get_word_2(s, i, len);
			j++;
		}
		i++;
	}
	return (ret);
}

char		**ft_strsplit(const char *s, char c)
{
	char	**ret;
	int		len;
	int		i;

	if (s == NULL || c == 0)
		return (NULL);
	len = count_words(s, c);
	if (!len)
		return (NULL);
	if (!(ret = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	ret[len] = NULL;
	i = 0;
	while (i < len)
	{
		ret[i] = get_word(s, i, c);
		i++;
	}
	return (ret);
}
