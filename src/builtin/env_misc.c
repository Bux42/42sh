/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:41:57 by drecours          #+#    #+#             */
/*   Updated: 2018/01/11 17:51:15 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char	**unset_key(char **tab, char *key)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(key, tab[i], ft_strlen(key)) == 0)
		{
			if (i == 0)
			return (tab);
		}
	}
	return (tab);
}
