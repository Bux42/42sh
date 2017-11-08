/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:04:56 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/08 23:53:57 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int			main(int ac, char **av, char **env)
{
	t_sh	*sh;
	int		len;

	if (!(sh = (t_sh*)malloc(sizeof(t_sh))))
		return (0);
	get_env(env, sh);
	check_debug(av, sh);
	current_dir(sh);
	sh->width = tgetnum("co");
	if (!init_term())
		ft_putendl("init_term failed, why");
	sh->retval = -1;
	while (ac > -1)
		if ((len = read(1, sh->buff, 5)))
			treat_input(sh);
	return (0);
}
