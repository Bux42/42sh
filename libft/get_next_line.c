/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 01:48:52 by videsvau          #+#    #+#             */
/*   Updated: 2017/02/07 12:24:29 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_manage_fd(int fd, t_list **chain)
{
	t_list	*tmp;

	tmp = *chain;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(tmp = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	tmp->content = ft_strnew(1);
	tmp->content_size = (size_t)fd;
	tmp->next = NULL;
	ft_lstadd(chain, tmp);
	tmp = *chain;
	return (tmp);
}

void	join(t_list **alst, char *buff, int end)
{
	char	*ret;

	ret = ft_strdup((*alst)->content);
	free((*alst)->content);
	if (((*alst)->content = (char*)malloc(sizeof(char)
	* ft_strlen(ret) + end + 1)) == NULL)
		return ;
	bzero((*alst)->content, ft_strlen(ret) + end + 1);
	ft_strcpy((*alst)->content, ret);
	ft_strncat((*alst)->content, buff, end);
	free(ret);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*chain = NULL;
	t_list			*curr;
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int				end;

	if (fd < 0 || line == NULL || read(fd, NULL, 0) == -1)
		return (-1);
	curr = ft_manage_fd(fd, &chain);
	while (!ft_strchr(curr->content, 10) && (end = read(fd, buff, BUFF_SIZE)))
		join(&curr, buff, end);
	if (end < BUFF_SIZE && !ft_strlen(curr->content))
		return (0);
	*line = ft_strsub(curr->content, 0, ft_stroccur(curr->content, 10));
	tmp = ft_strsub(curr->content, ft_stroccur(curr->content, 10) + 1,
			ft_strlen(curr->content) - ft_stroccur(curr->content, 10));
	free((curr->content));
	(curr)->content = tmp;
	return (1);
}
