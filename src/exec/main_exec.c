/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:54:36 by jamerlin          #+#    #+#             */
/*   Updated: 2018/04/09 10:32:55 by videsvau         ###   ########.fr       */
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
	if (condition_is_valid(sh, cmd))
		execve(fullpath, cmd->cont, env);
	else
		exit(WEXITSTATUS(sh->retval));
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

void	fork_exec(char *fullpath, t_listc *cmd, t_pipe *tabtube, t_sh *sh)
{
	char	**env;

	if ((sh->pid = fork()) == 0)
	{
		signal_exec();
		env = env_list_to_char(&sh->env);
		redirect(cmd, tabtube, 0, &cmd->redirs);
		run_cmd(fullpath, cmd, sh, env);
	}
	signal(SIGINT, SIG_IGN);
	free(fullpath);
}

void	check_signal(t_sh *sh)
{
	if (WIFSIGNALED(sh->retval) && WTERMSIG(sh->retval) == 2)
		ft_putstr("^C\n");
	if (WIFSIGNALED(sh->retval) && WTERMSIG(sh->retval) == 9)
	{
		ft_putstr_fd("Killed: 9\n", 2);
		kill(0, SIGKILL);
	}
}

void	exec_cli(char *cli, t_listc *cmd, t_sh *sh)
{
	char	*fullpath;
	t_pipe	*tabtube;

	sh->pid = 0;
	fullpath = NULL;
	if (!(tabtube = new_tabtube(cmd->nb_arg)))
		return ;
	if (cmd->redirs && cmd->redirs->redir[1] == HEREDOC)
		heredock_redirect(cmd, tabtube, 0);
	if (cmd->sep_type == PIPE)
		sh->retval = init_pipe(cmd, tabtube, sh);
	else if ((fullpath = command_path(&sh->env, cli, sh)))
		fork_exec(fullpath, cmd, tabtube, sh);
	else
	{
		sh->retval = -1;
		return ((void)close_tabtube(cmd->nb_arg, tabtube));
	}
	waitpid(sh->pid, &sh->retval, WUNTRACED);
	signal_init();
	check_signal(sh);
	close_tabtube(cmd->nb_arg, tabtube);
}
