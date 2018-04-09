/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cli.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:39:54 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/09 15:36:07 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

/*void		exec_cli(char *cli, t_listc *tok, t_sh *sh)
  {
  if (cli && tok && sh)
  ;
  }*/
/*******************************--REDIRECTIONS--*******************************/

void    left_redirect(t_listc *cmd, t_pipe *tabtube, int i) //redirection d'un fichier vers une sortie
{
	int ret;
	if (!(ret = open(cmd->redirs->file, O_RDONLY)))
	{
		close(ret);
		errExit(cmd->redirs->file);
	}
	tabtube[i].cote[0] = (cmd->redirs->file) ? ret : cmd->redirs->redir[2];
	tabtube[i].cote[1] = (i == 0) ? cmd->redirs->redir[0] : tabtube[i].cote[1];
}

void right_redirect(t_listc *cmd, t_pipe *tabtube, int i) //redirection d'une sortie vers un fichier
{
	tabtube[i].cote[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR| O_TRUNC | O_CREAT, S_IRWXU) 
		: cmd->redirs->redir[2];
	tabtube[i].cote[1] = (i == 0) ? cmd->redirs->redir[0] : tabtube[i].cote[1];
}

void    double_right_redirect(t_listc *cmd, t_pipe *tabtube, int i)// redirection d'une sortie vers la fin d'un fichier
{
	tabtube[i].cote[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR | O_APPEND | O_CREAT, S_IRWXU ) : cmd->redirs->redir[2];
	tabtube[i].cote[1] = (i == 0) ? cmd->redirs->redir[0] : tabtube[i].cote[1];
}

void errExit(char *str)
{
	printf("[%s]\n", str);
	exit(1);
}

void   redirect(t_listc *cmd, t_pipe *tabtube , int i) // gestion des redirections
{
	int j = 0;

	while (cmd->redirs != NULL)
	{
		if (cmd->redirs && cmd->redirs->redir[1] == 0)
			left_redirect(cmd, tabtube, i); // une liste de 1 maillon avec le fichier renseigne 
		else if (cmd->redirs && cmd->redirs->redir[1] == 1)
			right_redirect(cmd, tabtube, i); // une liste de 1 maillon avec le fichier renseigne
		else if (cmd->redirs && cmd->redirs->redir[1] == 3)
			double_right_redirect(cmd, tabtube, i); // une liste de 1 maillon avec le fichier renseigne
		//dprintf(2,"tabtube.cote[0] == [%d] ; tabtube.cote[1] == [%d] ; i == [%d]\n", tabtube[i].cote[0], tabtube[i].cote[1], i/*j**/);

		if (cmd->redirs->redir[1] != 0)
			dup2(tabtube[i].cote[0], STDOUT_FILENO);
		else 
			dup2(tabtube[i].cote[0], STDIN_FILENO);
		close(tabtube[i].cote[0]);
		cmd->redirs = cmd->redirs->next;
		j++;
	}
	i++;
}

/**********************************--PIPES--******************************************/

void    prepare_pipe(t_listc *cmd)
{
	t_listc *cpy;
	//    t_listc *last;
	int nb_cmd;
	int i;

	cpy = cmd;
	nb_cmd = 0;
	i = 0;
	while (cpy->sep_type == PIPE) 
	{
		//      last = cpy;
		if (cpy->sep_type == PIPE)
			nb_cmd++;
		cpy = cpy->next;
	}
	cpy = cmd;
	nb_cmd++;
	while (cpy && i < nb_cmd)
	{
		cpy->nb_arg = nb_cmd;
		i++;
		//cpy->prev = cpy;
		cpy = cpy->next;
	}
}

void	fermeture(int fils, int nb_tube, t_pipe *tabtube)
{
	int i;

	i = 0;
	//fprintf(stderr, "fermeture tubes processus(%d)\n", fils);
	while (i < nb_tube)
	{
		//fprintf(stderr, "\ti = [%d] && fd[0] = [%d]\n", i, tabtube[i].cote[0]);
		//fprintf(stderr, "\ti = [%d] && fd[1] = [%d]\n", i, tabtube[i].cote[1]);
		if (i != (fils - 1)) {
			//fprintf(stderr, "\tfermeture(%d) %d.lire fd[%d]\n", fils, i, tabtube[i].cote[0]);
			close(tabtube[i].cote[0]);
		}
		if (i != fils) {
			//fprintf(stderr, "\tfermeture(%d) %d.ecrire fd[%d]\n", fils, i, tabtube[i].cote[1]);
			close(tabtube[i].cote[1]);
		}
		i++;
	}
}

void	ft_cmd_pipe(t_listc *cmd, t_sh *i_env)
{
	//char fullpath[MAXPATHLEN * 2 + 1];
	char *fullpath;

	//if (filter_cli(cmd->cont, fullpath, cmd->cont[0], g_backup_env) < 0)
	if (!(fullpath = command_path(&i_env->env, cmd->cont[0], i_env)))
		return ;
	execve(fullpath, cmd->cont, NULL);
	errExit("execve");
}

void	pipe_tmp(t_listc *cmd, int i, t_pipe *tabtube, t_sh *i_env)
{
	/** Fermeture tubes inutilisés par ce processus **/
	//fprintf(stderr, "fils (%d) - pid=%d\n", i, getpid());
	fermeture(i, cmd->nb_arg - 1, tabtube);
	if (i > 0)
	{/** Redirection entrée venant du tube précédent **/
		close(STDIN_FILENO);
		//fprintf(stderr, "dup | i = [%d] -val=%d vers 0\n", i, tabtube[i - 1].cote[0]);
		dup2(tabtube[i - 1].cote[0], STDIN_FILENO);
	}
	if (i < (cmd->nb_arg - 1) )
	{/** Redirection sortie sur mon tube **/
		close(STDOUT_FILENO);
		//fprintf(stderr, "dup | i = [%d] -val=%d vers 1\n", i, tabtube[i].cote[1]);
		dup2(tabtube[i].cote[1], STDOUT_FILENO);
	}
	redirect(cmd, tabtube, i);
	ft_cmd_pipe(cmd, i_env);
}

void	ft_pipe(t_listc *cmd, int *pid_tab, t_pipe *tabtube, int i, t_sh *i_env)
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
		pipe_tmp(cmd, i, tabtube, i_env);
	pid_tab[i] = son;
}

int		do_pipe(t_listc *cmd, int *pid_tab, t_pipe *tabtube, t_sh *i_env)
{
	int		status;
	int		nu_cmd;
	int		wt_cpt;
	t_listc	*cpy;

	status = 0;
	nu_cmd = 0;
	wt_cpt = -1;
	cpy = cmd;
	while (nu_cmd < cmd->nb_arg - 1)
	{
		ft_pipe(cmd, pid_tab, tabtube, nu_cmd, i_env);
		cmd = cmd->next;
		nu_cmd++;
	}
	signal(SIGINT, SIG_IGN);
	ft_pipe(cmd, pid_tab, tabtube, nu_cmd, i_env);
	fermeture(-1, cmd->nb_arg - 1, tabtube);
	while (++wt_cpt < cmd->nb_arg)
	{
		waitpid(pid_tab[wt_cpt], &cpy->status, 0);
		status = cpy->status;
		cpy = cpy->next;
	}
	return (status);
}

int		init_pipe(t_listc *cmd, t_pipe *tabtube, t_sh *i_env)
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
	return (do_pipe(cmd, pid_tab, tabtube, i_env));
}

/******************************--MAIN_EXEC--**************************/

void				close_tabtube(t_pipe *tabtube, t_listc *full_detail)
{
	int				i;

	i = -1;
	while (++i < full_detail->nb_arg)
	{
		if (tabtube[i].cote[0] > 2)
			close(tabtube[i].cote[0]);
		if (tabtube[i].cote[1] > 2)
			close(tabtube[i].cote[1]);
	}
}

void				exec_cli(char *cli, t_listc *full_detail, t_sh *i_env)
{
	char            *fullpath;
	char			**env;
	pid_t			father;
	static int		status;
	t_pipe			*tabtube;

	father = getpid();
	if (!(tabtube = (t_pipe *)malloc(sizeof(t_pipe) * ((full_detail->nb_arg)))))
		|| (!(fullpath = command_path(&i_env->env, cli, i_env)))
		return ;
	if (fullpath[0] && full_detail->sep_type == PIPE)
		status = init_pipe(full_detail, tabtube, i_env);
	else if (fullpath[0] && (father = fork()) == 0)
	{
		signal_exec();
		env = env_list_to_char(&i_env->env);
		if (full_detail->sep_type == 0 || full_detail->sep_type == SEMICOLON)
			redirect(full_detail, tabtube, 0);
		if (full_detail->prev && (full_detail->prev->sep_type == AND ||
			full_detail->prev->sep_type == OR))
		{
			if (full_detail->prev->sep_type == OR && WEXITSTATUS(status) != 0)
				execve(fullpath, full_detail->cont, env);
			else if (full_detail->prev->sep_type == AND && 
				WEXITSTATUS(status) == 0)
				execve(fullpath, full_detail->cont, env);
			else
				exit(WEXITSTATUS(status));
		}
		else
			execve(fullpath, full_detail->cont, env);
		access(fullpath, X_OK) ?	ft_putstr_fd("Permission denied.\n", 2) :
									ft_putstr_fd("error\n", 2);
		exit(-1);
	}
	(fullpath[0]) ? signal(SIGINT, &signal_newline) : 0;
	waitpid(father, &status, WUNTRACED);
	signal_init();
	free(tabtube);
}
