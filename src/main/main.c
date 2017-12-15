/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 05:14:26 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/15 03:54:48 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		check_pasted(t_sh *sh)
{
	int		i;
	char	buff[6];

	i = -1;
	if (sh->buff[0] == 27 || sh->buff[1] == '\0')
		treat_input(sh);
	else
	{
		while (sh->buff[++i])
			buff[i] = sh->buff[i];
		buff[i] = '\0';
		sh->buff[1] = '\0';
		i = -1;
		while (buff[++i])
		{
			sh->buff[0] = buff[i];
			treat_input(sh);
		}
	}
}

int			main(int ac, char **av, char **env)
{
	t_sh	*sh;

	if (!(sh = (t_sh*)malloc(sizeof(t_sh))))
		return (0);
	if (!(sh->inpl = (t_inpl*)malloc(sizeof(t_inpl))))
		return (0);
	if (!(sh->fd = open("./.history", O_CREAT | O_RDWR)))
		return (0);
	if (fchmod(sh->fd, 00777) == -1)
		return (0);
	get_env(env, sh);
	sh->history = NULL;
	restaure_history_from_file(sh);
	sh->retval = 0;
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
	sh->inpl->inp = NULL;
	sh->inpl->next = NULL;
	sh->inpl->previous = NULL;
	sh->clipboard = NULL;
	sh->history_pos = NULL;
	sh->history_len = 0;
	sh->comp_debug = NULL;
	sh->comp_remain = NULL;
	sh->comp_path = NULL;
	sh->old_len = 0;
	sh->expected_quote = '\0';
	sh->context = 0;
	ft_bzero(sh->buff, 6);
	while (ac > -1)
		if ((sh->retval = read(1, sh->buff, 5)))
			check_pasted(sh);
	return (0);
}
