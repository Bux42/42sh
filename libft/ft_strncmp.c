/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:45:31 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/17 14:23:08 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*s11;
	unsigned char	*s22;

	s11 = ((unsigned char*)s1);
	s22 = ((unsigned char*)s2);
	i = 0;
	while (s11[i] == s22[i] && s11[i] != '\0' && s22[i] != '\0' && n > 0)
	{
		n--;
		i++;
	}
	if (n == 0)
		return (0);
	return (s11[i] - s22[i]);
}
