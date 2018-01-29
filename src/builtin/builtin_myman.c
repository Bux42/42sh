/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_myman.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 15:00:52 by drecours          #+#    #+#             */
/*   Updated: 2018/01/29 15:16:57 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

char	*checkman(char *path, char *file)
{
	struct stat		data;
	char			*str;
	int				x;

	str = ft_strjoin(path, file);
	if (access(str, F_OK) != 0)
		x = -1;
	if (access(str, R_OK) != 0)	
		x = -1;
	if (stat(str, &data) == -1)	
		x = -1;
	if (!(S_ISREG(data.st_mode)))
	if (x == -1)
		return (NULL);
	return (str);
}

int		builtin_myman(char **input, t_env **env, t_loc **loc, t_sh *sh)
{
	(void)loc;
	char	*file;
	char	*(tab[4]);

	tab[0] = "env";
	tab[1] = "less";
	tab[3] = NULL;
	if (input[1] && input[2])
		return (1);
	if (input[1])
		file = ft_strjoin(input[1], ".txt");
	if (!input[1])
		tab[2] = checkman(sh->man_path, "man.txt");
	else
		tab[2] = checkman(sh->man_path, file);
	if (!tab[2])
			ft_putstr("doesn't exists");
	if (!tab[2])
		custom_return();
	else
		builtin_env(tab, env);
	if (input[1])
		free(file);
	free(tab[2]);
	return (0);
}
