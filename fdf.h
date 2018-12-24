#ifndef FDF_H
# define FDF_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "libft/GNL/get_next_line.h"
# include <stdio.h>
# include <math.h>

typedef struct s_coord t_coord;

struct s_minilib
{
    void *mlx_ptr;
    void *win;
};

struct s_coord
{
    int     x;
    int     y;
    int     z;
    unsigned int color;
};

#endif