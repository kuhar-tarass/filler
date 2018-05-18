/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:06:47 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/18 17:30:06 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct		s_map
{
	int		player;
	int		x;
	int		y;
	short	**map;
}					t_map;

typedef struct		s_pice
{
	int		x;
	int		y;
	short	**pice;
	int		x_ins;
	int		y_ins;
}					t_pice;