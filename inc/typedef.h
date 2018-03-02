/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 13:07:47 by drecours          #+#    #+#             */
/*   Updated: 2018/03/02 09:23:12 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "../libft/includes/libft.h"

typedef struct			s_tok
{
	int					is_redir;
	int					fd[2];
	int					is_cond;
	int					flag;
	char				**cont;
	void				*func;
	struct s_tok		*next;
	struct s_tok		*previous;
}						t_tok;

typedef struct			s_close
{
	int					flag;
	struct s_close		*next;
	struct s_close		*previous;
}						t_close;

typedef struct			s_env
{
	char				*env;
	struct s_env		*next;
}						t_env;

typedef struct			s_loc
{
	char				*content;
	struct s_loc		*next;
}						t_loc;

typedef struct			s_var
{
	char				*var;
	struct s_var		*next;
}						t_var;

typedef struct			s_inp
{
	char				c;
	int					pos;
	struct s_inp		*next;
	struct s_inp		*previous;
}						t_inp;

typedef struct			s_inpl
{
	int					type;
	struct s_inp		*inp;
	struct s_inpl		*next;
	struct s_inpl		*previous;
}						t_inpl;

typedef struct			s_his
{
	struct s_inp		*inp;
	struct s_his		*next;
	struct s_his		*previous;
}						t_his;

typedef struct			s_sh
{
	char				*tty;
	char				*home_env;
	char				*clipboard;
	char				*comp_debug;
	char				*comp_remain;
	char				*comp_path;
	int					old_len;
	int					over;
	int					dec;
	char				buff[6];
	char				expected_quote;
	int					context;
	int					command_lenght;
	int					fd;
	int					posy;
	int					diff;
	int					prompt_len;
	int					pos_at;
	int					inp_len;
	int					history_len;
	struct s_his		*history_pos;
	int					hist_res;
	int					width;
	int					retval;
	int					search;
	int					failed_search;
	char				pwd[2048];
	char				*man_path;
	struct s_env		*env;
	struct s_loc		*loc;
	struct s_inpl		*inpl;
	struct s_his		*history;
	struct s_his		*search_pos;
	struct s_inp		*his_search;
	struct s_close		*close;
}						t_sh;

#endif
