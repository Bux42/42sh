/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:08:14 by drecours          #+#    #+#             */
/*   Updated: 2018/03/19 16:08:18 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

unsigned int 	ft_pow(int x, unsigned int y)
{
	int temp;

	if (y == 0)
		return (1);
	temp = ft_pow(x, y / 2);
	if (y % 2 == 0)
		return (temp * temp);
	else
		return (x * temp * temp);
}

unsigned int	hash_algo(char *key, int nb)
{
	int				i;
	unsigned int	hash;

	i = (-1);
	hash = 0;
	if (!(key) || nb <= 0)
		return (0);
	while (key[++i])
		hash += key[i] * (unsigned int)ft_pow(5, i);
	return (hash %= nb);
}

char			*get_hash_path(t_hash ***hash_addr, char *bin, t_sh *sh)
{
	unsigned int	id;
	t_hash			*hash;

	if (!(*hash_addr) || !(bin))
		return (NULL);
	id = hash_algo(bin, sh->hash_size);
	hash = (*hash_addr)[id];
	while (hash)
	{
		if (hash->bin != NULL)
			if ((ft_strcmp(hash->bin, bin)) == 0)
				return (hash->path);
		hash = hash->next;
	}
	return (NULL);
}

void			hash_del(t_hash ***hash, t_sh *sh)
{
	unsigned int	i;
	t_hash			*tmp;

	i = (-1);
	tmp = NULL;
	while (++i < sh->hash_size)
		if ((*(*hash + i)) != NULL)
			while ((*(*hash + i)) != NULL)
			{
				if ((*(*hash + i))->bin != NULL)
					ft_strdel(&((*(*hash + i))->bin));
				if ((*(*hash + i))->path != NULL)
					ft_strdel(&((*(*hash + i))->path));
				tmp = (*(*hash + i));
				(*(*hash + i)) = (*(*hash + i))->next;
				if (tmp != NULL)
					ft_memdel((void **)&tmp);
			}
	ft_memdel((void **)hash);
	sh->hash_size = 0;
}
