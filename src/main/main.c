/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 05:14:26 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/12 05:27:51 by videsvau         ###   ########.fr       */
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
	if (!init_term() || !get_tty(sh, av[1]))
		return (0);
	sh->width = tgetnum("co");
	if (sh->posy - 1 == sh->width)
	{
		sh->posy = 1;
		ft_putchar(' ');
		ft_putstr(tgetstr("le", NULL));
	}
	signal_init();
	while (ac > -1)
		if (read(1, sh->buff, 5))
			treat_input(sh);
	return (0);
}
