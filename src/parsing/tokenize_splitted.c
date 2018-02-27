/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_splitted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:33:23 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/27 22:07:50 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

t_tok		*new_tok(int *settings, void *func, char **cont)
{
	t_tok	*ret;

	if (!(ret = (t_tok*)malloc(sizeof(t_tok))))
		return (NULL);
	ret->is_redir = settings[0];
	ret->fd[0] = settings[1];
	ret->fd[1] = settings[2];
	ret->is_cond = settings[3];
	ret->flag = settings[4];
	ret->cont = cont;
	ret->func = func;
	ret->next = NULL;
	ret->previous = NULL;
	return (ret);
}

void		tok_push_back(t_tok **tok, int *settings, void *func, char **cont)
{
	t_tok	*cp;
	t_tok	*add;

	if (!(*tok))
		(*tok) = new_tok(settings, func, cont);
	else
	{
		cp = *tok;
		while (cp->next)
			cp = cp->next;
		add = new_tok(settings, func, cont);
		cp->next = add;
		add->previous = cp;
	}
}

int			valid_condition(t_inpl **inpl)
{
	if ((*inpl)->previous && (*inpl)->next)
	{
		if ((*inpl)->previous->type < 128)
			return (0);
		if ((*inpl)->next->type < 128)
			return (0);
		return (1);
	}
	return (0);
}

void		is_a_directory(char *str)
{
	ft_putstr("21sh: is a directory: ");
	ft_putstr(str);
}

int			valid_tofile(t_inpl **inpl)
{
	int			fd;
	int			len;
	char		*file;
	struct stat	st;

	len = 1;
	if ((*inpl)->previous && (*inpl)->next)
	{
		(*inpl) = (*inpl)->next;
		while ((*inpl)->inp->next)
		{
			(*inpl)->inp = (*inpl)->inp->next;
			len++;
		}
		if (!(file = (char*)malloc(sizeof(char) * (len + 1))))
			return (-1);
		file[len] = '\0';
		while ((*inpl)->inp->previous)
		{
			len--;
			file[len] = (*inpl)->inp->c;
			(*inpl)->inp = (*inpl)->inp->previous;
		}
		file[len - 1] = (*inpl)->inp->c;
		(*inpl) = (*inpl)->previous;
		fd = open(file, O_WRONLY | O_CREAT, 0666);
		if (fd == -1)
			if ((lstat(file, &st)) != -1)
				if (S_ISDIR(st.st_mode))
					is_a_directory(file);
		return (fd);
	}
	return (-1);
}

int			tokenize_splitted(t_inpl **inpl, t_sh *sh, t_tok *tok)
{
	t_inpl	*cp;
	int		settings[5];

	settings[0] = 0;
	if ((cp = (*inpl)))
	{
		sh->posy++;
		while (cp)
		{
			if (cp->type & AND || cp->type & OR || cp->type & PIPE)
			{
				if (valid_condition(&cp))
				{
					if (cp->type & OR || cp->type & AND)
					{
						settings[0] = 0;
						settings[3] = 1;
					}
					else
					{
						settings[0] = 1;
						settings[1] = 1;
						settings[2] = 0;
					}
					settings[4] = cp->type;
					tok_push_back(&tok, settings, NULL, NULL);
				}
				else
					return ((int)special_error(&cp->inp));
			}
			if (cp->type & TOFILE || cp->type & ATOFILE)
			{
				if ((settings[2] = valid_tofile(&cp)) != -1)
				{
					settings[0] = 1;
					settings[1] = 1;
					tok_push_back(&tok, settings, NULL, NULL);
				}
				else
					return (0);
			}
			cp = cp->next;
		}
	}
	return (1);
}
