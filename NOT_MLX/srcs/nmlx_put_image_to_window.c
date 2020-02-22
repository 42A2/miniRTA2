/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmlx_put_image_to_window.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 07:34:10 by mbrunel           #+#    #+#             */
/*   Updated: 2020/02/11 16:03:36 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <not_mlx.h>

int	mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y)
{
	t_img		*img;
	t_win		*win;

	img = (t_img*)img_ptr;
	win = (t_win*)win_ptr;
	(void)x;(void)y;(void)mlx_ptr;
	if (SDL_UpdateTexture(img->tex, NULL, img->img, img->width * sizeof (Uint32)) == -1)
		return (-1);
	if (SDL_RenderCopy(win->render,img->tex, NULL, NULL) == -1)
		return (-1);
	SDL_RenderPresent(win->render);
	return (0);
}
