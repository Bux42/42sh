/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_myman.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 15:00:52 by drecours          #+#    #+#             */
/*   Updated: 2018/03/03 14:40:49 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int		man_error(int err)
{
	if (err == 1)
		ft_putstr_fd("myman: Too many arguments.", STDERR_FILENO);
	else if (err == 2)
		ft_putstr_fd("myman: This builtin doesn't exists.", STDERR_FILENO);
	custom_return();
	return (err);
}

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

int		builtin_myman(char **input, t_sh *sh)
{
	char	*file;
	char	*(tab[4]);

	tab[0] = "env";
	tab[1] = "less";
	tab[3] = NULL;
	if (input[1] && input[2])
		return (man_error(1));
	if (input[1])
		file = ft_strjoin(input[1], ".txt");
	if (!input[1])
		tab[2] = checkman(sh->man_path, "myman.txt");
	else
		tab[2] = checkman(sh->man_path, file);
	if (!tab[2])
		return (man_error(2));
	builtin_env(tab, sh);
	if (input[1])
		free(file);
	free(tab[2]);
	return (0);
}
