/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 18:59:30 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/01/04 13:38:50 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include "./libft/libft.h"

typedef struct		s_ptr
{
	void			*mlx;
	void			*win;
	void			*img;
}					t_ptr;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_coord
{
	int				x;
	int				y;
	int				z;
	struct s_coord	*right;
	struct s_coord	*down;
}					t_coord;

typedef struct		s_container
{
	t_coord			
}					t_container;

int					exit_x(void);
void				my_exit(char *message, int stat);
void        		set_dimention(int ac, char **av, t_window *window);
t_coord         	*new_coord(int x, int y, int z);
void            	linke_list(t_coord *up, t_coord *down);
int             	get_line_data(int line, t_coord *head, char **splited);

#endif
