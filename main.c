# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <math.h>

typedef struct      s_minilib
{
    void            *mlx_ptr;
    void            *win;
}                   t_minilib;

typedef struct      s_coord
{
    int             x;
    int             y;
    int             z;
    unsigned int    color;
}                   t_coord;
//--------------------------------------------------------

int         number_of_lines(char *file)
{
    int fd;
    int lines;
    int error;
    char *line;

    fd = open(file, O_RDONLY);
    lines = 0;
    while ((error = get_next_line(fd, &line)))
    {
        if (error < 0)
        {
            ft_putstr("error during reading file\n");
            return(0);
        }
        lines++;
    }
    close(fd);
    return (lines);
}

t_coord     **get_coordinates(char *file)
{
    t_coord **coordinates;
    int len;
    int i;

    len = number_of_lines(file);
    coordinates = (t_coord**)malloc((len + 1) * sizeof(t_coord*));
    while (i < len)
    {
        coordinates[i] = fill_coordinates()
    }
    return (NULL);
}

int main(int ac, char **av)
{
    t_coord **coordinates;

    if (ac == 2)
    {
        coordinates = get_coordinates(av[1]);
    }
    else
        ft_putstr("usage: ./fdf wireframe_file\n");
    return (0);
}