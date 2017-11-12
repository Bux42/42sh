/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 05:14:26 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/12 03:06:37 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			main(int ac, char **av, char **env)
{
	t_sh	*sh;

	if (!(sh = (t_sh*)malloc(sizeof(t_sh))))
		return (0);
	get_env(env, sh);
	print_prompt(sh);
	if (ac > 0 && av[0])
	{
	}
	return (0);
}
