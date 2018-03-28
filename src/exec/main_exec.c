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

void				signal_handler(int inp)
{
	(void)inp;
	write(1, "\n", 1);
	//write_prompt(g_backup_env);
}

void				exec_cli(char *cli, t_listc *full_detail, t_sh *i_env)
{
	char            *fullpath;
	char			**env;
	pid_t			father;
	t_pipe			*tabTube;

	fullpath = NULL;
	father = getpid();
	if (!(tabTube = (t_pipe *)malloc(sizeof(t_pipe) * ((full_detail->nb_arg)))))
		return ;
	if (full_detail->redirs && full_detail->redirs->redir[1] == HEREDOC)
		heredock_redirect(full_detail, tabTube, 0);
	if (full_detail->sep_type == PIPE)
		i_env->retval = init_pipe(full_detail, tabTube, i_env);
	else if ((fullpath = command_path(&i_env->env, cli, i_env)) && (father = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		env = env_list_to_char(&i_env->env);
		if (full_detail->sep_type == 0 || full_detail->sep_type == SEMICOLON 
				|| (full_detail->redirs && full_detail->redirs->redir[1] == HEREDOC))
			redirect(full_detail, tabTube, 0);
		if (full_detail->prev && (full_detail->prev->sep_type == AND || full_detail->prev->sep_type == OR))
		{
			if (full_detail->prev->sep_type == OR && WEXITSTATUS(i_env->retval) != 0)
				execve(fullpath, full_detail->cont, env);
			else if (full_detail->prev->sep_type == AND && WEXITSTATUS(i_env->retval) == 0)
				execve(fullpath, full_detail->cont, env);
			else
				exit(WEXITSTATUS(i_env->retval));
		}
		else
			execve(fullpath, full_detail->cont, env);
		access(fullpath, X_OK) ? dprintf(2,"Permission denied.\n") : dprintf(2, "error\n");
		exit(-1);
	}
	waitpid(father, &i_env->retval, WUNTRACED);
	for(int i = 0; i < full_detail->nb_arg; i++)
	{
		if (tabTube[i].cote[0] > 2)
			close(tabTube[i].cote[0]);
		if (tabTube[i].cote[1] > 2)
			close(tabTube[i].cote[1]);
	}
	free(tabTube);
}
