#include "../../inc/header.h"

void				signal_handler(int inp)
{
	(void)inp;
	write(1, "\n", 1);
	//write_prompt(g_backup_env);
}

void				exec_cli(char *cli, t_listc *full_detail, t_sh *i_env)
{
	//char			fullpath[MAXPATHLEN * 2 + 1];
    char            *fullpath;
	char			**env;
	//int				bin;
	pid_t			father;
	static int		status;
	t_pipe			*tabTube;
	//int				(*func)(char **, t_sh*);

	father = getpid();
    if (!(tabTube = (t_pipe *)malloc(sizeof(t_pipe) * ((full_detail->nb_arg)))))
		return ;
    if (!(fullpath = command_path(&i_env->env, cli, i_env)))
        return ;
	printf("%d\n",full_detail->sep_type);
	if (full_detail->redirs && full_detail->redirs->redir[1] == HEREDOC)
		heredock_redirect(full_detail, tabTube, 0);
	if (/*!bin && */fullpath[0] && full_detail->sep_type == PIPE)
		status = init_pipe(full_detail, tabTube, i_env);
	else if (/*!bin && */fullpath[0] && (father = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		env = env_list_to_char(&i_env->env);
		if (full_detail->sep_type == 0 || full_detail->sep_type == SEMICOLON 
			|| (full_detail->redirs && full_detail->redirs->redir[1] == HEREDOC))
			redirect(full_detail, tabTube, 0);
		if (full_detail->prev && (full_detail->prev->sep_type == AND || full_detail->prev->sep_type == OR))
		{
			if (full_detail->prev->sep_type == OR && WEXITSTATUS(status) != 0)
				execve(fullpath, full_detail->cont, env);
			else if (full_detail->prev->sep_type == AND && WEXITSTATUS(status) == 0)
				execve(fullpath, full_detail->cont, env);
			else
				exit(WEXITSTATUS(status));
		}
		else
			execve(fullpath, full_detail->cont, env);
		access(fullpath, X_OK) ? dprintf(2,"Permission denied.\n") : dprintf(2, "error\n");
		exit(-1);
	}
	(fullpath[0]) ? signal(SIGINT, &signal_newline) : 0;
	waitpid(father, &status, WUNTRACED);
	for(int i = 0; i < full_detail->nb_arg; i++)
	{
		if (tabTube[i].cote[0] > 2)
			close(tabTube[i].cote[0]);
		if (tabTube[i].cote[1] > 2)
			close(tabTube[i].cote[1]);
	}
	free(tabTube);
}