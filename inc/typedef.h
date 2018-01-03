/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 13:07:47 by drecours          #+#    #+#             */
/*   Updated: 2018/01/03 13:20:25 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "../libft/includes/libft.h"

typedef struct			s_env
{
	char				*env;
	struct s_env		*next;
}						t_env;

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
	int					prompt_len;
	int					pos_at;
	int					inp_len;
	int					history_len;
	struct s_his		*history_pos;
	int					hist_res;
	int					width;
	int					retval;
	char				pwd[2048];
	struct s_env		*env;
	struct s_inpl		*inpl;
	struct s_his		*history;
}						t_sh;

#endif
