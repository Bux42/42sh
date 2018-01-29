/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_myman.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 15:00:52 by drecours          #+#    #+#             */
/*   Updated: 2018/01/29 14:51:16 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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
	(void)env;
	(void)loc;
	char	*str;
	char	*file;

	if (input[1] && input[2])
		return (1);
	if (input[1])
		file = ft_strjoin(input[1], ".txt");
	if (!input[1])
		str = checkman(sh->man_path, "man.txt");
	else
		str = checkman(sh->man_path, file);
	if (!str)
			ft_putstr("doesn't exists");
	else
		ft_putstr(str);
	custom_return();
	if (input[1])
		free(file);
	free(str);
	return (0);
}
