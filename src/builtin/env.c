/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 08:45:58 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/17 11:44:08 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			parse_setenv(char **exec, t_env **env)
{
	char	*name;
	char	*value;
	int		len;

	len = 0;
	if (env)
		;
	value = NULL;
	name = NULL;
	while (exec[1][len] && exec[1][len] != '=')
		len++;
	if (!(name = (char*)malloc(sizeof(char) * (++len + 1))))
		return (-1);
	ft_bzero(name, len);
	ft_strncat(name, exec[1], len);
	while (exec[1][len])
		len++;
	if (!(value = (char*)malloc(sizeof(char) * (len - ft_strlen(name) + 1))))
		return (-1);
	ft_bzero(value, ++len - ft_strlen(name));
	ft_strcat(value, &exec[1][ft_strlen(name)]);
	set_env(env, name, value);
	free(name);
	free(value);
	return (1);
}

int			set_env_cmd(char **exec, t_env **env)
{
	int		i;
	int		equal;

	i = -1;
	equal = 0;
	if (exec[2])
		return (err_msg("setenv: too many arguments", "", -1));
	if (!exec[1])
		return (err_msg("setenv: missing argument", "", -1));
	while (exec[1][++i])
	{
		if (exec[1][i] == '=')
		{
			equal++;
			if (i < 1)
				return (err_msg("setenv: parse error near '='", "", -1));
		}
	}
	if (!equal)
		return (err_msg("setenv: missing ':'", "", -1));
	return (parse_setenv(exec, env));
}

void		print_env(t_env **env)
{
	t_env	*cp;

	if ((cp = (*env)))
	{
		while (cp)
		{
			ft_putstr(cp->env);
			custom_return();
			cp = cp->next;
		}
	}
}

int			env(char **exec, t_env **env)
{
	if (exec)
		;
	if (!exec[1])
		print_env(env);
	return (1);
}
