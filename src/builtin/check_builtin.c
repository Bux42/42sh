/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 08:13:10 by videsvau          #+#    #+#             */
/*   Updated: 2018/01/15 20:02:38 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int				err_msg(char *message, char *name, int ret)
{
	ft_putstr(message);
	ft_putstr(name);
	custom_return();
	return (ret);
}

void			*get_builtin_function(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (&change_dir);
	if (ft_strcmp(command, "env") == 0)
		return (&builtin_env);
	if (ft_strcmp(command, "setenv") == 0)
		return (&builtin_setenv);
	if (ft_strcmp(command, "unsetenv") == 0)
		return (&builtin_unsetenv);
	if (ft_strcmp(command, "echo") == 0)
		return (&builtin_echo);
	if (ft_strcmp(command, "exit") == 0)
		return (&builtin_exit);
	if (ft_strcmp(command, "set") == 0)
		return (&builtin_set);
	return (NULL);
}

int				fork_builtin(int (*ptr)(char**, char**), char **exec, char **env)
{
	pid_t	father;
	int		status;

	status = -1;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_old_term);
	if ((father = fork()) != -1)
	{
		if (father == 0)
			ptr(exec, env);
		else
			waitpid(father, &status, 0);
		tcsetattr(STDIN_FILENO, TCSADRAIN, &g_new_term);
	}
	return (status);
}
