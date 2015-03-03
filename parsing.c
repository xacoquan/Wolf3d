/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacoquan <xacoquan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/04 09:02:55 by xacoquan          #+#    #+#             */
/*   Updated: 2015/01/31 05:00:19 by xacoquan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "header.h"

void			draw(t_env *e)
{
	int		i;

	while (e->ystart < e->yend)
	{
		i = e->x * (e->bpp / 8) + e->ystart * e->sl;
		e->str[i] = e->color;
		e->str[i + 1] = e->color >> 8;
		e->str[i + 2] = e->color >> 16;
		e->ystart++;
	}
}

void	ft_get_data(t_env *e)
{
	int		fd;
	int		nbl;
	char	**map;
	char	*line;

	nbl = 0;
	fd = open(MAP_FILE, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		nbl++;
		free(line);
	}
	close(fd);
	map = (char **)malloc(sizeof(char *) * (nbl + 1));
	int		i;

	i = 0;
	fd = open(MAP_FILE, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		map[i] = ft_strdup(line);
		i++;
		free(line);
	}
	map[i] = NULL;
	close(fd);
	e->tab = map;
	// print_map(e);
}

// int     ft_count(char *s, char c)
// {
//     int i;
//     int res;

//     res = 0;
//     i = 0;
//     while (s[i] != c && s[i] != '\0')
//     {
//         i++;
//         res++;
//     }
//     return (res);
// }

// void ft_check_data(int ac, char **av, t_env e)
// {
// 	if (ac != 2)
// 	{
// 		ft_putstr("format : a.out [map.txt]\n");
// 		exit(0);
// 	}	
// }

// void ft_get_data(char *file, t_env *e)
// {
// 	int line;
// 	char *str;
// 	int fd;

// 	if ((fd = open(file, O_RDONLY)) == -1)
// 	{
// 		ft_putstr("usage: ./fdf [data_file]\n");
// 		exit(0);
// 	}
// 	e->tab = (int**)malloc(sizeof(int*) * BIG_MAP);
// 	fd = open("./map.txt", O_RDONLY);
// 	if (fd -= 1)
// 		ft_putstr("map not found.\n");
// 	while (get_next_line(fd, &str) == 1)
// 	{
// 		e->tab[line] = ft_strcheckint(str, ' ');
// 		free(str);
// 		line++;
// 	}
// 	close(fd);
// }

// int ft_strcheckint(char *s, char c)
// {
// 	int *tab;
// 	int i;
// 	int nb_c;

// 	i = 0;
// 	nb_c = 0;
// 	if (s == NULL)
// 		return (NULL);
// 	while (s[i] != '\0')
// 	{	
// 		if ((s[i] == c && s[i + 1] != c && s[i + 1] != '\0') || (s[0] != c && i == 0)))
// 			nb_c++;
// 		i++;
// 	}
// 	tab = (int *)malloc(sizeof(int) * nb_c);
// 	if (tab)
// 		ft_put_data(tab, nb_c, tab, s);
// }

// void ft_put_data(int *tab, int nb_c, char c, char *s)
// {
// 	int i;
// 	int j;
// 	int size;

// 	while (nb_c != '\0' && j < nb_w)
// 	{
// 		if ((s[i] == c && s[i + 1] != c && s[i + 1] != '\0') || (s[0] != c && i == 0))
// 		{
//             if (s[i] == c)
//                 i++;
//             size = ft_count(&s[i], c);
// 	        tab[j] = ft_atoi(ft_strsub(s, i, size));
//             j++;
//         }
//         i++;
// 	}
// }
void	left(t_env *e)
{
	double		olddirx;
	double		oldplanex;

	olddirx = e->dirx;
	e->dirx = e->dirx * cos(RS) - e->diry * sin(RS);
	e->diry = olddirx * sin(RS) + e->diry * cos(RS);
	oldplanex = e->planx;
	e->planx = e->planx * cos(RS) - e->plany * sin(RS);
	e->plany = oldplanex * sin(RS) + e->plany * cos(RS);
}

void	right(t_env *e)
{
	double		olddirx;
	double		oldplanex;

	olddirx = e->dirx;
	e->dirx = e->dirx * cos(-RS) - e->diry * sin(-RS);
	e->diry = olddirx * sin(-RS) + e->diry * cos(-RS);
	oldplanex = e->planx;
	e->planx = e->planx * cos(-RS) - e->plany * sin(-RS);
	e->plany = oldplanex * sin(-RS) + e->plany * cos(-RS);
}

void	down(t_env *e)
{
	if (e->tab[(int)(e->posy - e->diry * MS)][(int)(e->posx)] == '0')
		e->posy -= e->diry * MS;
	if (e->tab[(int)(e->posy)][(int)(e->posx - e->dirx * MS)] == '0')
		e->posx -= e->dirx * MS;
}

void	up(t_env *e)
{
	if (e->tab[(int)(e->posy + e->diry * MS)][(int)(e->posx)] == '0')
		e->posy += e->diry * MS;
	if (e->tab[(int)(e->posy)][(int)(e->posx + e->dirx * MS)] == '0')
		e->posx += e->dirx * MS;
}

int		key_hook(int keycode, t_env *e)
{
	if (keycode == 65307)
		exit(0);
	else if (keycode == 65361)
		left(e);
	else if (keycode == 65363)
		right(e);
	else if (keycode == 65362)
		up(e);
	else if (keycode == 65364)
		down(e);
	e->x = 0;
	while (e->x < WIDTH)
	{
		e->ystart = 0;
		e->yend = HEIGHT / 2;
		e->color = 0x007fff;
		draw(e);
		e->ystart = HEIGHT / 2;
		e->yend = HEIGHT;
		e->color = 0x80CC00;
		draw(e);		
		e->x++;
	}
	raycasting(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (keycode);
}

int		expose_hook(t_env *e)
{
	e->x = 0;
	while (e->x < WIDTH)
	{
		e->ystart = 0;
		e->yend = HEIGHT / 2;
		e->color = 0x007fff;
		draw(e);
		e->ystart = HEIGHT / 2;
		e->yend = HEIGHT;
		e->color = 0x80CC00;
		draw(e);
		e->x++;
	}
	raycasting(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}


void	init_player(t_env *e)
{
	e->posx = 4;
	e->posy = 4;
	e->dirx = -1;
	e->diry = 0;
	e->planx = 0;
	e->plany = 0.66;
}


int		main(void)
{
	t_env		e;

	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "Wolf");
	e.img = mlx_new_image(e.mlx, WIDTH, HEIGHT);
	e.str = mlx_get_data_addr(e.img, &(e.bpp), &(e.sl), &(e.endian));
	ft_get_data(&e);
	init_player(&e);
	mlx_hook(e.win, 2, 3, key_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}