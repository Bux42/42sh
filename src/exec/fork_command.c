/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 04:32:46 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/10 09:40:58 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "../builtin/builtin.h"

char		**env_list_to_char(t_env **env)
{
	char	**ret;
	int		len;
	t_env	*cp;

	ret = NULL;
	len = 0;
	if ((cp = (*env)))
	{
		while (cp && ++len)
			cp = cp->next;
		if (!(ret = (char**)malloc(sizeof(char*) * (len + 1))))
			return (NULL);
		ret[len] = NULL;
		cp = (*env);
		len = 0;
		while (cp)
		{
			ret[len++] = ft_strdup(cp->env);
			cp = cp->next;
		}
	}
	return (ret);
}

int		fork_command(char *path, char **exec, char **env)
{
	pid_t	pid;
	int		status;

	status = -1;
	if ((pid = fork()) == 0)
	{
		signal_exec();
		execve(path, exec, env);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, WUNTRACED);
	signal_init();
	if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
		ft_putstr("\n");
	if (WIFSIGNALED(status) && WTERMSIG(status) == 9)
	{
		ft_putstr_fd("Killed: 9\n",2);
		kill(0,SIGKILL);
	}
	return (status);
}
