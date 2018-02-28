/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 05:14:26 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/28 16:41:52 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		check_pasted(t_sh *sh)
{
	int		i;
	char	buff[6];

	i = -1;
	if (sh->buff[0] == 27 || sh->buff[1] == '\0')
	{
		if (sh->search)
			treat_input_search(sh);
		else
			treat_input(sh);
	}
	else
	{
		while (sh->buff[++i])
			buff[i] = sh->buff[i];
		buff[i] = '\0';
		sh->buff[1] = '\0';
		i = -1;
		while (buff[++i])
		{
			if (buff[i] == '\t')
				buff[i] = ' ';
			sh->buff[0] = buff[i];
			if (sh->search)
				treat_input_search(sh);
			else
				treat_input(sh);
		}
	}
}

void		init_variables(t_sh *sh)
{
	sh->inpl->inp = NULL;
	sh->inpl->next = NULL;
	sh->inpl->previous = NULL;
	sh->clipboard = NULL;
	sh->history_pos = NULL;
	sh->history_len = 0;
	sh->comp_debug = NULL;
	sh->comp_remain = NULL;
	sh->comp_path = NULL;
	sh->loc = NULL;
	sh->old_len = 0;
	sh->context = 0;
	sh->search = 0;
	sh->retval = 0;
	sh->his_search = NULL;
	sh->search_pos = NULL;
	sh->close = NULL;
	ft_bzero(sh->buff, 6);
}

int			find_hist_file(char *man_path)
{
	int		fd;
	char	*cp;
	char	name[] = ".history";

	fd = -1;
	cp = ft_strdup(man_path);
	cp[21] = '\0';
	ft_strcat(cp, name);
	fd = open(cp, O_CREAT | O_RDWR, 0777);
	free(cp);
	return (fd);
}

int			main(int ac, char **av, char **env)
{
	t_sh	*sh;
	
	if (!(sh = (t_sh*)malloc(sizeof(t_sh))))
		return (0);
	if (!(sh->inpl = (t_inpl*)malloc(sizeof(t_inpl))))
		return (0);
	sh->man_path = find_man_path(av[0]);
	if ((sh->fd = find_hist_file(sh->man_path)) == -1)
		return (0);
	get_env(env, sh);
	sh->history = NULL;
	restaure_history_from_file(sh);
	if (!init_term() || !get_tty(sh, av[1]))
		return (0);
	print_prompt(sh);
	sh->width = tgetnum("co");
	if (sh->posy - 1 == sh->width)
	{
		sh->posy = 1;
		ft_putchar(' ');
		ft_putstr(tgetstr("le", NULL));
	}
	init_variables(sh);
	signal_init();
	while (ac > -1)
		if (read(1, sh->buff, 4))
			check_pasted(sh);
	return (0);
}
