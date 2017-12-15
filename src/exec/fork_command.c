/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 04:32:46 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/15 05:29:26 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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
	pid_t	father;
	int		status;

	father = fork();
	if (father == 0)
	{
		custom_return();
		tcsetattr(STDIN_FILENO, TCSADRAIN, &g_old_term);
		execve(path, exec, env);
		exit(0);
	}
	else
		waitpid(father, &status, 0);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_new_term);
	return (status);
}
