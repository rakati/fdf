/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 19:04:59 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/01/03 22:01:36 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int exit_x(void)
{
    exit(1);
}

void		my_exit(char *message, int stat)
{
	if (stat == EXIT_FAILURE)
		ft_putstr("error : ");
	ft_putstr(message);
	exit(stat);
}

void        set_dimention(int ac, char **av, t_window *window)
{
    int x;

    x = 0;
    if (ac == 4)
    {
        window->width = ((x = atoi(av[2])) >= 1200) ? (x) : (1200);
        window->height = ((x = atoi(av[3])) >= 1000) ? (x) : (1000);
    }
    else
    {
        window->height = 1000;
        window->width = 1200;
    }
}

t_coord         *new_coord(int x, int y, int z)
{
	t_coord     *new;

	new = (t_coord*)malloc(sizeof(t_coord));
	new->x = x;
	new->y = y;
	new->z = z;
	new->right = NULL;
	new->down = NULL;
	return (new);
}

void            linke_list(t_coord *up, t_coord *down)
{
	while (up)
	{
		up->down = down;
		up = up->right;
		down = down->right;
	}
}

int             get_line_data(int line, t_coord *head, char **splited)
{
	int         i;

	i = 0;
	while (splited[++i])
	{
		head->right = new_coord(i, line, ft_atoi(splited[i]));
		head = head->right;
	}
	return (i);
}