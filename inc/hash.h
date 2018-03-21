/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:41:43 by drecours          #+#    #+#             */
/*   Updated: 2018/03/21 12:32:40 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

#include "../../inc/typedef.h"
#include "../../inc/header.h"

typedef struct			s_hash
{
	unsigned int		hash;
	char				*bin;
	char				*path;
	struct s_hash		*next;
}						t_hash;

t_hash					**hash_table(char *path, t_sh *sh);
unsigned int			hash_algo(char *key, int nb);
char					*get_hash_path(t_hash ***hash_addr, char *bin, t_sh *sh);
void					hash_del(t_hash ***hash, t_sh *sh);
void					init_bin_list(t_hash **addr, char *path);

#endif
