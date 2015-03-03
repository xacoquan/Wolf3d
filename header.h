/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xacoquan <xacoquan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/04 09:02:46 by xacoquan          #+#    #+#             */
/*   Updated: 2015/01/31 05:23:45 by xacoquan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# define BIG_MAP 1000
# define WIDTH 1000
# define HEIGHT 1000
# define MS 0.3
# define RS 0.3
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include "libft.h"
# define MAP_FILE "./toto"
typedef struct s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*str;

	int			bpp;
	int			endian;
	int			sl;

	char		**tab; // map
	int			x; // pixel de 0 a la taille de la fenetre

	double		posx; // pos perso
	double		posy; 
	double		dirx; // vu perso
	double		diry; 
	double		planx; //largeur vue
	double		plany;

	double		camera; 
	double		rayposy; // les position des rayons
	double		rayposx;
	double		raydiry;
	double		raydirx;

	int			mapx; //position dans la map
	int			mapy;
	double		deltadistx; //position dans la case
	double		deltadisty; //
	double		sidedistx; //distance de la limite de la case la plus proche
	double		sidedisty;

	int			hit; // mur
	int			stepx; //  direction de la vue par rapport au mur
	int			stepy; 

	double		perpwalldist; // distance de posx et posy avec mur (lance de rayon)
	int			side; // les 4 phase par rapport au difference entre stepx et stepy

	int			lineheight; // hauteur du mur en fonction de la distance du joueur 
	int			ystart; // debut du mur recentre
	int			yend; // fin du mur recentre

	int			color; // couleur
}				t_env;
void ft_check_data(int ac, char **av, t_env e);
void ft_get_data(t_env *e);
#endif