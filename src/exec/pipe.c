/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:54:57 by jamerlin          #+#    #+#             */
/*   Updated: 2018/04/07 05:25:51 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	ft_cmd_pipe(t_listc *cmd, t_sh *sh)
{
	char	*fullpath;
	int		(*func)(char **, t_sh*);

	if (cmd->func)
	{
		func = cmd->func;
		sh->retval = func(cmd->cont, sh);
		exit(sh->retval);
	}
	else if (!(fullpath = command_path(&sh->env, cmd->cont[0], sh)))
		exit(1);
	execve(fullpath, cmd->cont, NULL);
	perror("execve");
	exit(1);
}

void	pipe_tmp(t_listc *cmd, int i, t_pipe *tabtube, t_sh *sh)
{
	closed_unused_fd(i, cmd->nb_arg - 1, tabtube);
	if (i > 0)
	{
		close(STDIN_FILENO);
		dup2(tabtube[i - 1].cote[0], STDIN_FILENO);
	}
	if (i < (cmd->nb_arg - 1))
	{
		close(STDOUT_FILENO);
		dup2(tabtube[i].cote[1], STDOUT_FILENO);
	}
	if (cmd->redirs && cmd->redirs->redir[1] == 4)
		heredock_redirect(cmd, tabtube, i);
	redirect(cmd, tabtube, i);
	ft_cmd_pipe(cmd, sh);
}

void	ft_pipe(t_listc *cmd, int *pid_tab, t_pipe *tabtube, int i, t_sh *sh)
{
	pid_t son;

	son = -1;
	son = fork();
	if (son == -1)
	{
		close(tabtube[i].cote[0]);
		close(tabtube[i].cote[1]);
		perror("fork");
		exit(1);
	}
	else if (son == 0)
		pipe_tmp(cmd, i, tabtube, sh);
	pid_tab[i] = son;
}

int		do_pipe(t_listc *cmd, int *pid_tab, t_pipe *tabtube, t_sh *sh)
{
	int		nu_cmd;
	int		wt_cpt;
	t_listc	*cpy;

	nu_cmd = 0;
	wt_cpt = -1;
	cpy = cmd;
	while (nu_cmd < cmd->nb_arg - 1)
	{
		ft_pipe(cmd, pid_tab, tabtube, nu_cmd, sh);
		cmd = cmd->next;
		nu_cmd++;
	}
	signal(SIGINT, SIG_IGN);
	ft_pipe(cmd, pid_tab, tabtube, nu_cmd, sh);
	closed_unused_fd(-1, cmd->nb_arg - 1, tabtube);
	while (++wt_cpt < cmd->nb_arg)
	{
		waitpid(pid_tab[wt_cpt], &cpy->status, 0);
		sh->retval = cpy->status;
		cpy = cpy->next;
	}
	free(pid_tab);
	return (sh->retval);
}

int		init_pipe(t_listc *cmd, t_pipe *tabtube, t_sh *sh)
{
	int		*pid_tab;
	int		i;

	i = 0;
	if (!(pid_tab = (int *)malloc(sizeof(int) * (cmd->nb_arg + 1))))
		exit(-1);
	while (i < (cmd->nb_arg - 1))
	{
		if (pipe(tabtube[i].cote) != 0)
		{
			perror("pipe");
			free(tabtube);
			exit(-2);
		}
		i++;
	}
	return (do_pipe(cmd, pid_tab, tabtube, sh));
}
