# include "fdf.h"


// bresenham algorithme for drawing a line here is a link to understand : https://youtu.be/m2enpQNSYEY?list=PLLOxZwkBK52DkMLAYhRLA_VtePq5wW_N4
void	draw_line(t_coord db,t_coord fin, struct s_minilib lib, unsigned int color)
{
	int pk;
	t_coord cdk;
    int swp;
    int dx;
    int dy;
    int cptx;
    int cpty;
    int i;
    int swpbool;

    i = 0;
    swpbool = 0;
    dx = abs(db.x - fin.x);
	dy = abs(db.y - fin.y);
    cptx = (db.x > fin.x) ? -1 : 1;
    cpty = (db.y > fin.y) ? -1 : 1;
    if (dy < dx)
    {
        swp = dx;
        dx = dy;
        dy = swp;
        swpbool = 1;
    }
    cdk = db;
    pk = 2 * dy - dx;
    while(i < dx && i < dy)
    {
        mlx_pixel_put(lib.mlx_ptr, lib.win, cdk.x, cdk.y, color);
        while(pk >= 0)
        {
            pk += -2 * dx;
            if (swpbool)
                cdk.x += cptx;
            else
                cdk.y += cpty;
        }
        pk += 2 * dy;
        if (swpbool)
            cdk.y += cpty;
        else
            cdk.x += cptx;
     i++;
    }
}

//get number of lines of a file
int file_len(const int fd)
{
    char *line;
    int size;

    size = 0;
    while (get_next_line(fd, &line))
        size++;
    close(fd);
    return (size);
}

//get number of existant numbers in a single line
int     line_len(char *line)
{
    int size;
    int i;

    size = 0;
    i = -1;
    while (line[++i])
    {
        if ((line[i] >= '0' && line[i] <= '9') && (line[i + 1] == ' ' || line[i + 1] == '\0'))
            size++;
    }
    return (size);
}

//fill the coordinats (x, y, z) by numbers in line passed in parametre
t_coord   *fill_line(char *line, t_coord *lst, int y)
{
    int cpt;

    cpt = 0;
    while (*line)
    {
        lst[cpt].z = ft_atoi(line);
        lst[cpt].x = 600 + (cpt * 35);
        lst[cpt].y = y;
        while ((*line >= '0' && *line <= '9') && *line)
            line++;
        while(*line == ' ' && *line)
            line++;
        cpt++;
    }
    return (lst);
}

//malloc ower double pointre and fill it with coordinates of file
t_coord  **fdf_malloc(int fd, char *file, int *len)
{
    t_coord **lst;
    int cpt;
    char *line;
    int y;

    y = 200;
    cpt = 0;
    lst = (t_coord**)malloc(sizeof(*lst) * file_len(fd)); // reconfig it
    fd = open(file, O_RDONLY);
    while (get_next_line(fd, &line))
    {
        *len = line_len(line);
        lst[cpt] = (t_coord*)malloc(sizeof(t_coord) * *len);
        lst[cpt] = fill_line(line, lst[cpt], y);
        cpt++;
        y += 35;
    }
    close(fd);
    return (lst);
}

//after fill the double pointer structre with coordinates we rotate each coordinate (x, y) to isometric
t_coord     **rotate(t_coord **cords, int len)
{
    int i;
    int j;
    t_coord cd;

    i = -1;
    while (cords[++i])
    {
        j = -1;
        while (++j < len)
        {
            cd.x = (cords[i][j].x - cords[i][j].y) * cos(0.523599);
            cd.y = -cords[i][j].z + (cords[i][j].y + cords[i][j].x) * sin(0.523599);
            cd.z = cords[i][j].z;
            cords[i][j] = cd;
        }
    }
    return (cords);
}

// initialize a new window and draw coordinate of file given in lines of pixels
int main(int argc, char **argv)
{
    t_coord **coords;
    int fd;
    int len;
    struct s_minilib lib;
    int i;
    int j;
    unsigned int color;


    fd = open(argv[1], O_RDONLY);
    coords = fdf_malloc(fd, argv[1], &len);
    lib.mlx_ptr = mlx_init();//read the manual (man minilibx/man/man1/~) to get more about minilibx lib
    lib.win = mlx_new_window(lib.mlx_ptr, 1300, 1000, "1337");
    coords = rotate(coords, len);
    i = -1;
    color = 0xFFFFFF;
    while (coords[++i])
    {
        j = -1;
        while (++j < len -1)
        {
            printf("%2d ",coords[i][j].z);
            color = (coords[i][j].z > 0 && (coords[i + 1][j].z > 0 || coords[i][j + 1].z > 0)) ? 0xFA0000 : 0xFFFFFF;
            draw_line(coords[i][j], coords[i][j + 1], lib, color);
            if (coords[i + 1])
                draw_line(coords[i][j], coords[i + 1][j], lib, color);
            if (j + 1 == (len -1) && coords[i + 1])
                draw_line(coords[i][j + 1], coords[i + 1][j + 1], lib, color);
        }
        printf("\n");
    }
    mlx_loop(lib.mlx_ptr);
    return (0);
}
// execution (cc -I fdf.h fdf.c libft/*.c libft/GNL/get_next_line.c -L minilibx_macos -lmlx -framework OpenGL -framework AppKit)