/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 09:41:22 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/02 12:32:30 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char		*concat_command_path(char *path, char *command)
{
	char	*ret;
	int		len;

	ret = NULL;
	len = ft_strlen(path) + ft_strlen(command) + 1;

	if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_bzero(ret, len);
	ft_strcat(ret, path);
	ft_strcat(ret, "/");
	ft_strcat(ret, command);
	return (ret);
}

char		*find_command_path(char **path, char *command)
{
	char			*ret;
	DIR				*od;
	struct dirent	*fl;
	int				i;

	i = -1;
	ret = NULL;
	while (path[++i])
	{
		if ((od = opendir(path[i])))
		{
			while ((fl = readdir(od)))
			{
				if (ft_strcmp(command, fl->d_name) == 0)
				{
					closedir(od);
					return (concat_command_path(path[i], command));
				}
			}
			closedir(od);
		}
	}
	return (ret);
}

char		*command_path(t_env **env, char *command)
{
	char	*path;
	char	*ret;
	char	**split;

	ret = NULL;
	if ((path = get_specific_env("PATH=", env)))
	{
		if ((split = ft_strsplit(path, ':')))
		{
			ret = find_command_path(split, command);
		}
	}
	else
		return (NULL);
	return (ret);
}

void		check_command(t_tok *tok, t_sh *sh)
{
	int		i;
	pid_t	pid;
	char	*path;

	i = -1;
	while (tok->cont[0][++i])
		if (tok->cont[0][i] == '/')
			break ;
	if (!tok->cont[0][i])
	{
		if ((path = command_path(&sh->env, tok->cont[0])))
		{
			if ((pid = fork()) != -1)
			{
				if (pid == 0)
				{
					tcsetattr(STDIN_FILENO, TCSADRAIN, &g_old_term);
					execve(path, tok->cont, NULL);
					exit(1);
				}
				else
					waitpid(pid, &sh->retval, 0);
				tcsetattr(STDIN_FILENO, TCSADRAIN, &g_new_term);
			}
			free(path);
		}
	}
}

void		execute_tokens(t_tok **tok, t_sh *sh)
{
	t_tok	*cp;
	int		(*func)(char**, t_sh *);

	if ((cp = (*tok)))
	{
		if (cp->is_redir)
			;
		else if (cp->is_cond)
			;
		else if (cp->func)
		{
			func = get_builtin_function(cp->cont[0]);
			sh->retval = func(cp->cont, sh);
		}
		else
			check_command(cp, sh);
	}
}
