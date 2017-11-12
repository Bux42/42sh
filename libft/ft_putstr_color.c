/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:50:02 by videsvau          #+#    #+#             */
/*   Updated: 2016/11/21 16:50:23 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	ft_putstr_color(char *str, int color)
{
	write(1, "\x1B[", 2);
	write(1, ft_itoa(color), 3);
	write(1, "m", 1);
	ft_putstr(str);
	write(1, "\x1B[0m", 4);
}
