/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:25:37 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/02 23:33:25 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

t_inp		*get_bquote(t_inp **inp, t_sh *sh)
{
	t_inp	*ret;
	int		fd[2];
	pid_t	pid;
	char	buff[100];
	int		len;

	ret = NULL;
	if ((pipe(fd)) != -1)
	{
		if ((pid = fork()) != -1)
		{
			if (pid == 0)
			{
				close(fd[0]);
				dup2(fd[1], 1);
				dup2(fd[1], 2);
				close(fd[1]);
				parse_backquotes(inp, sh);
				exit(0);
			}
			else
			{
				close(fd[1]);
				int i = 0;
				wait(NULL);
				while ((len = read(fd[0], buff, 99)))
				{
					while (i < len)
					{
						inp_insert_posat(&ret, buff[i]);
						i++;
					}
					i = 0;
				}
			}
		}
	}
	return (ret);
}

void		wtf(t_inp **inp)
{
	t_inp	*cp;

	if ((cp = (*inp)))
	{
		while (cp->previous)
			cp = cp->previous;
		ft_putchar('[');
		while (cp)
		{
			ft_putchar(cp->c);
			cp = cp->next;
		}
		ft_putchar(']');
	}
}

void		convert_bquote(t_inp **inp, t_sh *sh)
{
	t_inp	*bquote;
	t_inp	*start;
	t_inp	*end;
	t_inp	*exec;

	bquote = NULL;
	start = *inp;
	*inp = (*inp)->next;
	while (*inp)
	{
		inp_insert_posat(&bquote, (*inp)->c);
		if ((*inp)->c == '\\')
		{
			(*inp) = (*inp)->next;
			free((*inp)->previous);
			inp_insert_posat(&bquote, (*inp)->c);
		}
		else if ((*inp)->c == '`')
		{
			delete_letter(sh, &bquote);
			break ;
		}
		if ((*inp)->next)
		{
			(*inp) = (*inp)->next;
			free((*inp)->previous);
		}
		else
			break ;
	}
	end = (*inp);
	exec = get_bquote(&bquote, sh);
	if (start->previous)
	{
		start = start->previous;
		free(start->next);
		start->next = exec;
		exec->previous = start;
	}
	else
		free(start);
	while (exec->next)
		exec = exec->next;
	if (end->next)
	{
		end = end->next;
		free(end->previous);
		end->previous = exec;
		exec->next = end;
	}
	else
		free(end);
	*inp = exec;
	wtf(inp);
	free_list_from_beginning(&bquote);
}

void		convert_backslash_quote(t_inp **inp)
{
	char	c;
	t_inp	*after;

	c = '\0';
	if ((*inp)->next)
	{
		if ((*inp)->next->c == '\n')
			c = '\n';
		if ((*inp)->next->c == '\t')
			c = '\t';
		if (c)
		{
			after = (*inp)->next->next;;
			(*inp)->c = c;
			free((*inp)->next);
			(*inp)->next = after;
			after->previous = (*inp);
		}
	}
}

void		convert_backslash_dquote(t_inp **inp)
{
	char	c;
	t_inp	*before;
	t_inp	*after;

	c = '\0';
	before = (*inp)->previous;
	if ((*inp)->next)
	{
		if ((*inp)->next->c == 'n')
			c = '\n';
		if ((*inp)->next->c == 't')
			c = '\t';
		if (c)
		{
			after = (*inp)->next->next;
			(*inp)->c = c;
			(*inp)->next = after;
			free(after->previous);
			after->previous = (*inp);
		}
		else
		{
			(*inp) = (*inp)->next;
			free((*inp)->previous);
			if (before)
				before->next = (*inp);
			(*inp)->previous = before;
		}
	}
}

void		convert_dquote(t_inp **inp, t_sh *sh)
{
	t_inp	*previous;
	t_inp	*after;

	previous = (*inp)->previous;
	(*inp) = (*inp)->next;
	free((*inp)->previous);
	if (previous)
		previous->next = (*inp);
	(*inp)->previous = previous;
	while ((*inp)->c != '\"')
	{
		if ((*inp)->c == '$')
			try_insert_variable(inp, sh);
		if ((*inp)->c == '\\')
			convert_backslash_dquote(inp);
		(*inp) = (*inp)->next;
	}
	after = (*inp)->next;
	if (after)
		after->previous = (*inp)->previous;
	(*inp) = (*inp)->previous;
	free((*inp)->next);
	(*inp)->next = after;
}

void		convert_quote(t_inp **inp)
{
	t_inp	*previous;
	t_inp	*after;

	previous = (*inp)->previous;
	(*inp) = (*inp)->next;
	free((*inp)->previous);
	if (previous)
		previous->next = (*inp);
	(*inp)->previous = previous;
	while ((*inp)->c != '\'')
	{
		if ((*inp)->c == '\\')
			convert_backslash_quote(inp);
		(*inp) = (*inp)->next;
	}
	after = (*inp)->next;
	(*inp) = (*inp)->previous;
	if (after)
		after->previous = (*inp);
	free((*inp)->next);
	(*inp)->next = after;
}
