/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 19:04:20 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/01/04 13:34:37 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void line(int x0, int y0, int x1, int y1, t_ptr ptr, t_window *w) 
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;
    
    dx = abs(x1 - x0);
    dy = abs(y1 - y0);
    sx = x0 < x1 ? 1 : -1;;
    sy = y0 < y1 ? 1 : -1;
    err = (dx > dy ? dx : -dy) / 2;
    while (x0 != x1 || y0 != y1)
    {
        if (w[0].width > x0 && w[0].height > y0 && x0 > 0 && y0 > 0)
            mlx_pixel_put(ptr.mlx, ptr.win, x0, y0, 0xFFFFFF);
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
}

t_coord     *midle_of_list(t_coord *head)
{
    t_coord *c;
    t_coord *first;

    c = head;
    first = c;
    while (first->right)
    {
        c = c->right;
        first = first->right;
        if (!first->right)
            break;
        first = first->right;
    }
    first = c;
    while (first->down)
    {
        c = c->down;
        first = first->down;
        if (!first->down)
            break;
        first = first->down;
    }
    return (c);
}

void     ft_regle_shape(t_coord *head, t_window *w)
{
    t_coord *row;
    t_coord *col;
    int d_x;
    int d_y;

    row = midle_of_list(head);
    d_x = (w[0].width / 2) - row->x;
    d_y = (w[0].height / 2) - row->y;
    row = head;
    while (row)
    {
        col = row;
        while (col)
        {
            col->x += d_x;
            col->y += d_y;
            col = col->right;
        }
        row = row->down;
    }
}

t_coord         *get_coordinates(t_coord *mainhead, int fd, t_window *w)
{
	t_coord     *linehead;
	char        **splited;
	char        *line;
	int         i;

	get_next_line(fd, &line);
	splited = ft_strsplit(line, ' ');
	mainhead = new_coord(0, 0, ft_atoi(*splited));
	linehead = mainhead;
	w[1].width = get_line_data(0,linehead, splited);
	i = 1;
	while (get_next_line(fd, &line))
	{
		splited = ft_strsplit(line, ' ');
		linehead->down = new_coord(0, i, ft_atoi(*splited));
		get_line_data(i,linehead->down, splited);
		linke_list(linehead, linehead->down);
		linehead = linehead->down;
		i++;
	}
    w[1].height = i;
	return mainhead;
}


void            ft_draw(t_coord *head, t_ptr ptr, t_window *w)
{
    t_coord *row;
    t_coord *col;

    row = head;
    while (row)
    {
        col = row;
        while (col)
        {
            if (col->right)
                line(col->x, col->y,col->right->x, col->right->y, ptr, w);
            if (col->down)
                line(col->x, col->y,col->down->x, col->down->y, ptr, w);
            col = col->right;
        }
        row = row->down;
    }
}

t_coord         *rotate(t_coord *head)
{
    t_coord *row;
    t_coord *col;

    row = head;
    while (row)
    {
        col = row;
        while (col)
        {
            col->x = (col->x - col->y) * cos(-0.785398);
            col->y = -col->z + (col->y + col->x) * sin(0.785398);
            col = col->right;
        }
        row = row->down;
    }
    return (head);
}

t_coord         *x_rotate(t_coord *head)
{
    t_coord *row;
    t_coord *col;

    row = head;
    while (row)
    {
        col = row;
        while (col)
        {
            col->y = (col->y * cos(1.8)) + (col->z * sin(1.8));
            col->z = (col->z * cos(1.8)) - (col->y * sin(1.8));
            col = col->right;
        }
        row = row->down;
    }
    return (head);
}

t_coord         *y_rotate(t_coord *head)
{
    t_coord *row;
    t_coord *col;

    row = head;
    while (row)
    {
        col = row;
        while (col)
        {
            col->x = (col->x * cos(0.5)) - (col->y * sin(0.5));
            col->z = (col->z * cos(0.5)) - (col->x * sin(0.5));
            col = col->right;
        }
        row = row->down;
    }
    return (head);
}

t_coord         *z_rotate(t_coord *head)
{
    t_coord *row;
    t_coord *col;

    row = head;
    while (row)
    {
        col = row;
        while (col)
        {
            col->x = (col->x * cos(0.5)) - (col->y * sin(0.5));
            col->y = (col->y * cos(0.5)) + (col->x * sin(0.5));
            col = col->right;
        }
        row = row->down;
    }
    return (head);
}

t_coord         *ft_add_cell(t_coord *head, t_window *w)
{
    t_coord *row;
    t_coord *col;
    int     cell;

    cell = (w[1].width > w[1].height) ? ((2 * w[0].width / 3) / w[1].width) :
            ((2 * w[0].height / 3) / w[1].height);
    //w[1].width *= cell;
    //w[1].height *= cell; 
    row = head;
    while (row)
    {
        col = row;
        while (col)
        {
            col->x *= cell;
            col->y *= cell;
            col = col->right;
        }
        row = row->down;
    }
    return (head);
}

int key_press(int keycode, void *param)
{
    t_coord **c;

    c = param;
    // exit by clicking ESC 
    if (keycode == 53)
        exit_x();
    return (1);
}


int main(int ac, char **av)
{
    t_window    window[2];
    t_coord     *coord;
    t_ptr       ptr;
    int         fd;

    if (ac == 2 || ac == 4)
    {
        ptr.mlx = mlx_init();
        set_dimention(ac, av, window);
        ptr.win = mlx_new_window(ptr.mlx, window[0].width, window[0].height, "1337");
        if ((fd = open(av[1], O_RDONLY)) < 0)
            my_exit("invalid file\n", EXIT_FAILURE);
        coord = NULL;
        coord = get_coordinates(coord, fd, window);
        close(fd);
        coord = ft_add_cell(coord, window);
        coord = rotate(coord);
        //coord = x_rotate(coord);
        ft_regle_shape(coord, window);
        ft_draw(coord, ptr, window);
        mlx_key_hook(ptr.win, key_press, coord);
        mlx_hook(ptr.win, 17, 1L << 17, exit_x, NULL);
        mlx_loop(ptr.mlx);
    }
    else
        my_exit("usage: ./Fdf file [win_width] [win_height]\n", EXIT_FAILURE);
    return (0);
}