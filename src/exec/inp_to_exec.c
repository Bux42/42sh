/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_to_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 05:49:52 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/15 07:20:05 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			command_length(t_inp **inp)
{
	int		i;
	t_inp	*cp;

	i = 0;
	if ((cp = (*inp)))
	{
		while (cp && is_space(cp->c))
			cp = cp->next;
		while (cp && cp->next && !is_space(cp->c) && ++i)
			cp = cp->next;
	}
	return (i);
}

char		*get_command(t_inp **inp, t_sh *sh)
{
	int		i;
	int		len;
	char	*command;

	command = NULL;
	sh->posy = sh->posy;
	i = 0;
	if ((len = command_length(inp)))
	{
		if (!(command = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		command[len] = '\0';
		while ((*inp) && is_space((*inp)->c))
			(*inp) = (*inp)->next;
		while ((*inp) && !is_space((*inp)->c))
		{
			command[i] = (*inp)->c;
			(*inp) = (*inp)->next;
			i++;
		}
		command = check_exec_path(command, &sh->env, 1);
	}
	return (command);
}

char		**get_full_command(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;
	char	**full_cmd;
	int		i;

	i = 0;
	full_cmd = NULL;
	if ((cp = (*inp)))
	{
		while (cp)
		{
			while (cp->next && is_space(cp->c))
				cp = cp->next;
			if (cp && !is_space(cp->c))
			{
				i++;
				while (cp && !is_space(cp->c))
					cp = cp->next;
			}
			if (cp)
				cp = cp->next;
		}
		if (i == 0 || !(full_cmd = (char**)malloc(sizeof(char*) * (i + 1))))
			return (NULL);
		sh->command_lenght = i;
		full_cmd[i] = NULL;
	}
	return (full_cmd);
}

void		exec_command(t_inp **inp, t_sh *sh)
{
	char	**exec;
	char	**env;
	char	*path;
	int		i;
	t_inp	*cp;

	i = 0;
	if ((cp = (*inp)) && (exec = get_full_command(inp, sh)))
	{
		while (i < sh->command_lenght)
		{
			if (!(exec[i] = get_command(&cp, sh)))
				return ;
			i++;
		}
		if (!(path = existing_command(exec[0], &sh->env)))
			sh->retval = 127;
		else
		{
			env = env_list_to_char(&sh->env);
			sh->retval = fork_command(path, exec, env);
			ft_putnbr(sh->retval);
			for (int i = 0; env[i]; i++)
				free(env[i]);
			free(env);
			for (int i = 0; exec[i]; i++)
				free(exec[i]);
			free(exec);
		}
	}
}

void	valid_command(t_inp **inp, t_sh *sh)
{
	exec_command(inp, sh);
}
