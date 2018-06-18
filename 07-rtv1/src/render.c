/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

/*
**static void		render_debug(t_mlx *mlx, t_camera *camera, t_matrix *matrix)
**{
**	int		length;
**	char	*str;
**
**	length = 48;
**	if (!(str = (char *)malloc(length)))
**		return ;
**	snprintf(str, length, "%f,%f, %f", camera->lat, camera->lon, camera->zoom);
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 20, 0xFFFFFF, "CAMERA->");
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 20, 0xFFFFFF, ft_itoa(camera->render));
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 40, 0xFFFFFF, "Anchor:");
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 40, 0xFFFFFF, vector_tostr(&camera->anchor));
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 60, 0xFFFFFF, "Vector:");
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 60, 0xFFFFFF, vector_tostr(&camera->pos));
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 80, 0xFFFFFF, "Lat,Lon,Zoom:");
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 90, 80, 0xFFFFFF, str);
**
**	snprintf(str, length, "u:(%f,%f,%f)", matrix->u->x, matrix->u->y, matrix->u->z);
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 300, 20, 0xFFFFFF, str);
**	snprintf(str, length, "v:(%f,%f,%f)", matrix->v->x, matrix->v->y, matrix->v->z);
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 300, 40, 0xFFFFFF, str);
**	snprintf(str, length, "w:(%f,%f,%f)", matrix->w->x, matrix->w->y, matrix->w->z);
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 300, 60, 0xFFFFFF, str);
**	if (matrix->t)	snprintf(str, length, "t:(%f,%f,%f)", matrix->t->x, matrix->t->y, matrix->t->z);
**	else			snprintf(str, length, "t:(NULL)");
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 300, 80, 0xFFFFFF, str);
**	free(str);
**}
*/

/*
**	Returns true if the ray intersects an object, false otherwise.
**	- orig is the ray origin
**	- dir is the ray direction
**	- objects is the list of objects the scene contains
**	-[out] tNear contains the distance to the cloesest intersected object.
**	-[out] index stores the index of the intersect triangle if the interesected object is a mesh.
**	-[out] uv stores the u and v barycentric coordinates of the intersected point
**	-[out] *hitObject stores the pointer to the intersected object (used to retrieve material information, etc.)
**	- isShadowRay is it a shadow ray. We can return from the function sooner as soon as we have found a hit.
*
static int		trace( 
	const t_vector &orig, const t_vector &dir, 
	const std::vector<std::unique_ptr<Object>> &objects, 
	float &tNear, uint32_t &index, Vec2f &uv, Object **hitObject) 
{ 
	*hitObject = nullptr; 
	for (uint32_t k = 0; k < objects.size(); ++k)
	{
		float tNearK = kInfinity; 
		uint32_t indexK; 
		Vec2f uvK; 
		if (objects[k]->intersect(orig, dir, tNearK, indexK, uvK) && tNearK < tNear)
		{
			*hitObject = objects[k].get(); 
			tNear = tNearK; 
			index = indexK; 
			uv = uvK; 
		}
	}
	return (*hitObject != nullptr); 
} 

static t_vector	*cast_ray(t_mlx *mlx, t_vector *origin, t_vector *direction)
{
	t_vector color = options.backgroundColor; 
	float tnear = kInfinity; 
	Vec2f uv; 
	t_u32 index = 0; 
	Object *hitObject = nullptr; 
	if (trace(orig, dir, objects, tnear, index, uv, &hitObject))
	{
		t_vector hitPoint = orig + dir * tnear; 
		t_vector N; // normal 
		Vec2f st; // st coordinates 
		hitObject->getSurfaceProperties(hitPoint, dir, index, uv, N, st); 
		t_vector tmp = hitPoint; 
		switch (hitObject->materialType)
		{
			//We use the Phong illumation model int the default case. The phong model is composed of a diffuse and a specular reflection component. 
			t_vector lightAmt = 0, specularColor = 0; 
			t_vector shadowPointOrig = (vector_scalar(dir, N) < 0) ? 
				hitPoint + N * options.bias :
				hitPoint - N * options.bias;
			//Loop over all lights in the scene and sum their contribution up We also apply the lambert cosine law here though we haven't explained yet what this means. 
			for (uint32_t i = 0; i < lights.size(); ++i)
			{
				t_vector lightDir = lights[i]->position - hitPoint; 
				// square of the distance between hitPoint and the light
				float lightDistance2 = vector_scalar(lightDir, lightDir); 
				lightDir = normalize(lightDir); 
				float LdotN = std::max(0.f, vector_scalar(lightDir, N)); 
				Object *shadowHitObject = nullptr; 
				float tNearShadow = kInfinity; 
				// is the point in shadow, and is the nearest occluding object closer to the object than the light itself?
				bool inShadow = trace(shadowPointOrig, lightDir, objects, tNearShadow, index, uv, &shadowHitObject) && 
				    tNearShadow * tNearShadow < lightDistance2; 
				lightAmt += (1 - inShadow) * lights[i]->intensity * LdotN; 
				Vec3f reflectionDirection = reflect(-lightDir, N); 
				specularColor += powf(std::max(0.f, -vector_scalar(reflectionDirection, dir)), hitObject->specularExponent) * lights[i]->intensity; 
			}
			color = lightAmt * hitObject->evalDiffuseColor(st) * hitObject->Kd + specularColor * hitObject->Ks; 
			break ;
		}
	}
	return (color); 
}
*/
static t_vector	*cast_ray(t_mlx *mlx, t_vector *origin, t_vector *direction)
{
	if (mlx ||origin || direction)
		return (NULL);
	else return (NULL);
}

void			render(t_mlx *mlx, t_camera *camera)
{
	t_vector	origin;
	t_vector	*pixel;
	t_vector	*direction;
	float		scale = tan(camera->fov * 0.5 * M_PI / 180);
	float		ratio = ((float)WIDTH / (float)HEIGHT);
	float		x;
	float		y;
	t_u32		*buffer = (t_u32 *)mlx->image->buffer;
	t_u32		color;
	int			index;

	ft_bzero(mlx->image->buffer, HEIGHT * mlx->image->line);
	vector_set(&origin, 0, 0, 0);
	for (t_u32 j = 0; j < HEIGHT; ++j)
	for (t_u32 i = 0; i < WIDTH; ++i)
	{
		x =     (2 * (i + 0.5) / (float)WIDTH - 1) * ratio * scale;
		y = (1 - 2 * (j + 0.5) / (float)HEIGHT) * scale;
		direction = vector_new(x, y, -1);
		vector_normalize(direction);
		pixel = cast_ray(mlx, &origin, direction);
		color = color_new(0, pixel->x, pixel->y, pixel->z);
		buffer[index++] = color;
	}
	mlx_put_image_to_window(
		mlx->mlx_ptr,
		mlx->win_ptr,
		mlx->img_ptr, 0, 0);
	//render_debug(mlx, camera, &camera->matrix);
}
