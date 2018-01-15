/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_builtin_.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 13:18:02 by drecours          #+#    #+#             */
/*   Updated: 2018/01/15 13:39:41 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

char	*env_key(char *env_v)
{
	char	*key;
	size_t	i;

	i = 0;
	while (env_v[i] != '=' && env_v[i] != '\0')
		++i;
	if (!(key = malloc((i + 1) * sizeof(char))))
		return (NULL);
	key[i] = '\0';
	while (i != 0)
	{
		--i;
		key[i] = env_v[i];
	}
	return (key);
}

char	**manage_env(char *key, char **env, int i)
{
	char	**new_env;
	char	*tmp;
	int		j;

	if (!(new_env = (char**)malloc(sizeof(char*) * i)))
	{
		write(STDERR_FILENO, "Malloc error.\n", 14);
		return (env);
	}
	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		tmp = env_key(env[i]);
		if (!(ft_strcmp(tmp, key) == 0))
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		++i;
		free(tmp);
	}
	new_env[j] = NULL;
	return (new_env);
}

int		env_free(char **env)
{
	size_t		i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		++i;
	}
	free(env);
	return (0);
}

char	*env_val(char *env_v)
{
	char	*key;
	size_t	i;
	size_t	size;

	i = 0;
	while (env_v[i] != '=' && env_v[i] != '\0')
		++i;
	size = i++;
	while (env_v[size] != '\0')
		++size;
	if (!(key = malloc((size - i + 1) * sizeof(char))))
		return (NULL);
	size -= i;
	key[size] = '\0';
	while (size != 0)
	{
		--size;
		key[size] = env_v[size + i];
	}
	return (key);
}

char	*env_read(char **env, const char *key)
{
	size_t	i;
	char	*env_k;

	i = 0;
	while (env[i] != NULL)
	{
		env_k = env_key(env[i]);
		if (ft_strcmp(env_k, key) == 0)
		{
			free(env_k);
			return (env_val(env[i]));
		}
		free(env_k);
		++i;
	}
	return (NULL);
}

char			**unsetenv_tab(char **env, char *key)
{
	char		**new_env;
	char		*tmp;
	size_t		i;

	i = 0;
	if ((tmp = env_read(env, key)) == NULL)
	{
		free(tmp);
		return (env);
	}
	else
		free(tmp);
	while (env[i] != NULL)
		++i;
	new_env = manage_env(key, env, i);
	env_free(env);
	return (new_env);
}
