#include "header.h"
#include <math.h>
void	initray(t_env *e)
{
	e->camera = 2 * (double)e->x / (double)(WIDTH) - 1;
	e->rayposx = e->posx;
	e->rayposy = e->posy;
	e->raydirx = e->dirx + e->planx * e->camera;
	e->raydiry = e->diry + e->plany * e->camera;
	e->mapx = (int)e->rayposx;
	e->mapy = (int)e->rayposy;
	e->deltadistx = sqrt(1 + (e->raydiry * e->raydiry) / (e->raydirx * e->raydirx));
	e->deltadisty = sqrt(1 + (e->raydirx * e->raydirx) / (e->raydiry * e->raydiry));
	e->hit = 0;
}

void	dda(t_env *e)
{
	while (e->hit == 0)
	{
		if (e->sidedistx < e->sidedisty)
		{
			e->sidedistx += e->deltadistx;
			e->mapx += e->stepx;
			if (e->stepx < 0)
				e->side = 0;
			else
				e->side = 1;
		}
		else
		{
			e->sidedisty += e->deltadisty;
			e->mapy += e->stepy;
			if (e->stepy < 0)
				e->side = 2;
			else
				e->side = 3;
		}
		if (e->tab[e->mapy][e->mapx] != '0')
			e->hit = 1;
	}
}

void	heightwall(t_env *e)
{
	if (e->side == 0 || e->side == 1)
		e->perpwalldist = fabs((e->mapx - e->rayposx + (1 - e->stepx) / 2) / e->raydirx);
	else
		e->perpwalldist = fabs((e->mapy - e->rayposy + (1 - e->stepy) / 2) / e->raydiry);
	e->lineheight = fabs((int)(HEIGHT / e->perpwalldist));
	e->ystart = (HEIGHT / 2) - (e->lineheight / 2);
	if (e->ystart < 0)
		e->ystart = 0;
	e->yend = (HEIGHT / 2) + (e->lineheight / 2);
	if (e->yend >= HEIGHT)
		e->yend = HEIGHT - 1;
	if (e->tab[e->mapy][e->mapx] == '1')
		e->color = 0xff0000;
	else if (e->tab[e->mapy][e->mapx] == '2')
		e->color = 0xcccccc;
	else
		e->color = 0xFFCCCC;
	if (e->side == 1)
		e->color *= 2;
	else if (e->side == 2)
		e->color /= 2;
	else if (e->side == 3)
		e->color *= 4;
}

void	raycasting(t_env *e)
{
	e->x = 0;
	while (e->x < WIDTH)
	{
		initray(e);
		if (e->raydirx < 0)
		{
			e->stepx = -1;
			e->sidedistx = (e->rayposx - e->mapx) * e->deltadistx;
		}
		else
		{
			e->stepx = 1;
			e->sidedistx = (e->mapx + 1.0 - e->rayposx) * e->deltadistx;
		}
		if (e->raydiry < 0)
		{
			e->stepy = -1;
			e->sidedisty = (e->rayposy - e->mapy) * e->deltadisty;
		}
		else
		{
			e->stepy = 1;
			e->sidedisty = (e->mapy + 1.0 - e->rayposy) * e->deltadisty;
		}
		dda(e);
		heightwall(e);
		draw(e);
		e->x++;
	}
}