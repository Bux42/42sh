/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:46:02 by jamerlin          #+#    #+#             */
/*   Updated: 2018/04/10 15:46:03 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	errexit(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	print_access_error(char *fullpath)
{
	if (access(fullpath, X_OK))
		ft_putstr_fd("Permission denied.\n", 2);
	else
		ft_putstr_fd("error\n", 2);
}
