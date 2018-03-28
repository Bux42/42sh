/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:54:57 by jamerlin          #+#    #+#             */
/*   Updated: 2018/03/28 18:05:24 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	ft_cmd_pipe(t_listc *cmd, t_sh *i_env)
{
	char	*fullpath;
	int		(*func)(char **, t_sh*);

	if (cmd->func)
	{
		func = cmd->func;
		i_env->retval = func(cmd->cont, i_env);
		exit(i_env->retval);
	}
	else if (!(fullpath = command_path(&i_env->env, cmd->cont[0], i_env)))
		exit(1);
	execve(fullpath, cmd->cont, NULL);
	perror("execve");
}

void	pipe_tmp(t_listc *cmd, int i, t_pipe *tabTube, t_sh *i_env)
{
	/** Fermeture tubes inutilisés par ce processus **/
	//fprintf(stderr, "fils (%d) - pid=%d\n", i, getpid());
	fermeture(i, cmd->nb_arg - 1, tabTube);
	if (i > 0)
	{/** Redirection entrée venant du tube précédent **/
		close(STDIN_FILENO);
		//fprintf(stderr, "dup | i = [%d] -val=%d vers 0\n", i, tabTube[i - 1].cote[0]);
		dup2(tabTube[i - 1].cote[0], STDIN_FILENO);
	}
	if (i < (cmd->nb_arg - 1) )
	{/** Redirection sortie sur mon tube **/
		close(STDOUT_FILENO);
		//fprintf(stderr, "dup | i = [%d] -val=%d vers 1\n", i, tabTube[i].cote[1]);
		dup2(tabTube[i].cote[1], STDOUT_FILENO);
	}
	if (cmd->redirs && cmd->redirs->redir[1] == 4)
		heredock_redirect(cmd, tabTube, i);
	redirect(cmd, tabTube, i);
	ft_cmd_pipe(cmd, i_env);
}

void	ft_pipe(t_listc *cmd, int *pid_tab, t_pipe *tabTube, int i, t_sh *i_env)
{
	pid_t son;
	son = -1;
	son = fork();
	if (son == -1)
	{
		close(tabTube[i].cote[0]);
		close(tabTube[i].cote[1]);
		perror("fork");
		exit(1);
	}
	else if (son == 0)
		pipe_tmp(cmd, i, tabTube, i_env);
	pid_tab[i] = son;
}

int		do_pipe(t_listc *cmd, int *pid_tab, t_pipe *tabTube, t_sh *i_env)
{
	int		nu_cmd;
	int		wt_cpt;
	t_listc	*cpy;

	nu_cmd = 0;
	wt_cpt = -1;
	cpy = cmd;
	while (nu_cmd < cmd->nb_arg - 1)
	{
		ft_pipe(cmd, pid_tab, tabTube, nu_cmd, i_env);
		cmd = cmd->next;
		nu_cmd++;
	}
	signal(SIGINT, SIG_IGN);
	ft_pipe(cmd, pid_tab, tabTube, nu_cmd, i_env);
	fermeture(-1, cmd->nb_arg - 1, tabTube);
	while (++wt_cpt < cmd->nb_arg)
	{
		waitpid(pid_tab[wt_cpt], &cpy->status, 0);
		i_env->retval = cpy->status;
		cpy = cpy->next;
	}
	return (i_env->retval);
}

int		init_pipe(t_listc *cmd, t_pipe *tabTube, t_sh *i_env)
{
	int		*pid_tab;
	int		i;

	i = 0;
	if (!(pid_tab = (int *)malloc(sizeof(int) * (cmd->nb_arg + 1))))
		exit(-1);
	while (i < (cmd->nb_arg - 1))
	{
		if (pipe(tabTube[i].cote) != 0)
		{
			perror("pipe");
			free(tabTube);
			exit(-2);
		}
		i++;
	}
	return (do_pipe(cmd, pid_tab, tabTube, i_env));
}
