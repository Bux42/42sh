/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 05:14:26 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/09 11:11:05 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		check_pasted(t_sh *sh)
{
	int		i;
	char	buff[6];

	i = -1;
	if (sh->buff[0] == 27 || sh->buff[1] == '\0')
		sh->search ? treat_input_search(sh) : treat_input(sh);
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
			sh->search ? treat_input_search(sh) : treat_input(sh);
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
	sh->hash = NULL;
	sh->hash_size = 0;
	sh->bin = NULL;
	ft_bzero(sh->buff, 6);
	g_sh->hash = hash_table(get_specific_env("PATH=", &g_sh->env), g_sh);
	get_bin(&g_sh->env, g_sh);
	signal_init();
}

int			find_hist_file(char *man_path)
{
	int		fd;
	char	*cp;

	fd = -1;
	if (!(cp = (char*)malloc(sizeof(char) * (ft_strlen(man_path) + 9))))
		return (0);
	ft_bzero(cp, ft_strlen(man_path) + 9);
	ft_strcat(cp, man_path);
	ft_strcat(cp, ".history");
	//fd = open(cp, O_CREAT | O_RDWR, 0777);
	free(cp);
	return (fd);
}

int			main(int ac, char **av, char **env)
{
	if (!(g_sh = (t_sh*)malloc(sizeof(t_sh))))
		return (0);
	if (!(g_sh->inpl = (t_inpl*)malloc(sizeof(t_inpl))))
		return (0);
	g_sh->man_path = find_man_path(av[0]);
	//if ((g_sh->fd = find_hist_file(g_sh->man_path)) == -1)
	//	return (0);
	get_env(env, g_sh);
	g_sh->history = NULL;
	//restore_history_from_file(g_sh);
	if (!init_term() || !get_tty(g_sh, av[1]))
		return (0);
	g_sh->retval = 0;
	print_prompt(g_sh);
	g_sh->width = tgetnum("co");
	if (g_sh->posy - 1 == g_sh->width && g_sh->posy--)
	{
		check_endline(g_sh);
		ft_putchar('1');
	}
	init_variables(g_sh);
	while (ac > -1)
		if (read(1, g_sh->buff, 4))
			check_pasted(g_sh);
	return (0);
}
