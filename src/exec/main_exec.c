/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:54:36 by jamerlin          #+#    #+#             */
/*   Updated: 2018/04/07 15:11:53 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	print_access_error(char *fullpath)
{
	if (access(fullpath, X_OK))
		ft_putstr_fd("Permission denied.\n", 2);
	else
		ft_putstr_fd("error\n", 2);
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

void	run_cmd(char *fullpath, t_listc *cmd, t_sh *sh, char **env)
{
	if (cmd->prev && (cmd->prev->sep_type == AND
				|| cmd->prev->sep_type == OR))
	{
		if (cmd->prev->sep_type == OR &&
				WEXITSTATUS(sh->retval) != 0)
			execve(fullpath, cmd->cont, env);
		else if (cmd->prev->sep_type == AND
				&& WEXITSTATUS(sh->retval) == 0)
			execve(fullpath, cmd->cont, env);
		else
			exit(WEXITSTATUS(sh->retval));
	}
	else
		execve(fullpath, cmd->cont, env);
	print_access_error(fullpath);
	exit(-1);
}

t_pipe	*new_tabtube(int len)
{
	t_pipe	*ret;
	int		i;

	ret = NULL;
	i = 0;
	if (!(ret = (t_pipe*)malloc(sizeof(t_pipe) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		ret[i].cote[0] = 0;
		ret[i].cote[1] = 0;
		i++;
	}
	return (ret);
}

void	exec_cli(char *cli, t_listc *cmd, t_sh *sh)
{
	char	*fullpath;
	char	**env;
	pid_t	pid;
	t_pipe	*tabtube;

	pid = 0;
	fullpath = NULL;
	if (!(tabtube = new_tabtube(cmd->nb_arg)))
		return ;
	if (cmd->redirs && cmd->redirs->redir[1] == HEREDOC)
		heredock_redirect(cmd, tabtube, 0);
	if (cmd->sep_type == PIPE)
		sh->retval = init_pipe(cmd, tabtube, sh);
	else if ((fullpath = command_path(&sh->env, cli, sh)))
	{
		if ((pid = fork()) == 0)
		{
			signal_exec();
			env = env_list_to_char(&sh->env);
			redirect(cmd, tabtube, 0, &cmd->redirs);
			run_cmd(fullpath, cmd, sh, env);
		}
		signal_init();
		signal(SIGINT, &signal_newline);
		free(fullpath);
	}
	else
	{
		sh->retval = -1;
		return ((void)close_tabtube(cmd->nb_arg, tabtube));
	}
	waitpid(pid, &sh->retval, WUNTRACED);
	if (WIFSIGNALED(sh->retval) && WTERMSIG(sh->retval) == 9)
	{
		ft_putstr_fd("Killed: 9\n",2);
		kill(0,SIGKILL);
	}
	close_tabtube(cmd->nb_arg, tabtube);
}
