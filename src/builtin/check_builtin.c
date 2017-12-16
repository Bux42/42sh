/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 08:13:10 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/16 10:47:03 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void			*get_builtin_function(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (&change_dir);
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
