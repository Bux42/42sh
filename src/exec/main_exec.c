/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:54:36 by jamerlin          #+#    #+#             */
/*   Updated: 2018/03/28 18:18:24 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	print_access_error(char *fullpath)
{
	access(fullpath, X_OK) ? ft_putstr_fd("Permission denied.\n", 2)
		: ft_putstr_fd("error\n", 2);
}

void	close_tabtube(int len, t_pipe *tabtube)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (tabtube[i].cote[0] > 2)
			close(tabtube[i].cote[0]);
		if (tabtube[i].cote[1] > 2)
			close(tabtube[i].cote[1]);
		i++;
	}
	free(tabtube);
}

void	run_cmd(char *fullpath, t_listc *cmd, t_sh *i_env, char **env)
{
	if (cmd->prev && (cmd->prev->sep_type == AND
		|| cmd->prev->sep_type == OR))
	{
		if (cmd->prev->sep_type == OR &&
			WEXITSTATUS(i_env->retval) != 0)
			execve(fullpath, cmd->cont, env);
		else if (cmd->prev->sep_type == AND
			&& WEXITSTATUS(i_env->retval) == 0)
			execve(fullpath, cmd->cont, env);
		else
			exit(WEXITSTATUS(i_env->retval));
	}
	else
		execve(fullpath, cmd->cont, env);
	print_access_error(fullpath);
	exit(-1);
}

void	exec_cli(char *cli, t_listc *cmd, t_sh *i_env)
{
	char	*fullpath;
	char	**env;
	pid_t	father;
	t_pipe	*tabtube;

	father = 0;
	fullpath = NULL;
	if (!(tabtube = (t_pipe *)malloc(sizeof(t_pipe) * ((cmd->nb_arg)))))
		return ;
	if (cmd->redirs && cmd->redirs->redir[1] == HEREDOC)
		heredock_redirect(cmd, tabtube, 0);
	if (cmd->sep_type == PIPE)
		i_env->retval = init_pipe(cmd, tabtube, i_env);
	else if ((fullpath = command_path(&i_env->env, cli, i_env)))
	{
		if ((father = fork()) == 0)
		{
			signal(SIGINT, SIG_DFL);
			env = env_list_to_char(&i_env->env);
			if (cmd->sep_type == 0 || cmd->sep_type == SEMICOLON
				|| (cmd->redirs && cmd->redirs->redir[1] == HEREDOC))
				redirect(cmd, tabtube, 0);
			run_cmd(fullpath, cmd, i_env, env);
		}
	}
	waitpid(father, &i_env->retval, WUNTRACED);
	if (WIFSIGNALED(i_env->retval) && WTERMSIG(i_env->retval))
 	{
		 ft_putstr_fd("Killed: 9\n",2);
		 kill(0,SIGKILL);
	}
	close_tabtube(cmd->nb_arg, tabtube);
}
