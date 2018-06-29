/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

int		intersect_plane(t_object *object, t_ray *ray)
{
	t_vector	hitpos;
	t_vector	normal;
	t_vector	tmp;
	float		d;

	getnormal_plane(&normal, object, NULL);
	d = vector_scalar(&normal, &ray->dir);
	if (d > 0.000001)
	{
		vector_set(&hitpos,
			ray->orig.x - ray->dir.x * ray->t,
			ray->orig.y - ray->dir.y * ray->t,
			ray->orig.z - ray->dir.z * ray->t);
		vector_set(&tmp,
			hitpos.x - ray->orig.x,
			hitpos.y - ray->orig.y,
			hitpos.z - ray->orig.z);
		ray->t = vector_scalar(&tmp, &normal) / d;
		return (ray->t >= 0);
	}
	return (0);
}
/*
static int	intersect_cube_axis(t_ray *ray, t_vector *vector, t_vector *axis)
{
	float	t1;
	float	t2;
	float	e;
	float	f;

	e = vector_scalar(axis, vector);
	f = vector_scalar(ray->dir, axis);
	if (fabs(f) > 0.001)
	{
		t1 = (e + aabb_min.z) / f;
		t2 = (e + aabb_max.z) / f;
		if (t1 > t2)
			ft_swap(&t1, &t2, sizeof(float));
		if (t2 < tMax)
			tMax = t2;
		if (t1 > tMin)
			tMin = t1;
		if (tMin > tMax)
			return (1);
	}
	else if (-e + aabb_min.z > 0 || -e + aabb_max.z < 0)
		return (1);
	return (0);
}

int		intersect_cube(t_object *object, t_ray *ray)
{
	t_vector *vector;
	t_vector *axis;

	vector_set(&vector,
		object->position.x - ray->orig.x,
		object->position.y - ray->orig.y,
		object->position.z - ray->orig.z);
	if (intersect_cube_axis(ray, vector, axis))
		return (0);
	if (intersect_cube_axis(ray, vector, axis))
		return (0);
	if (intersect_cube_axis(ray, vector, axis))
		return (0);
	ray->t = tMin;
}

bool TestRayOBBIntersection(
	glm::vec3 ray_origin,        // Ray origin, in world space
	glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
	glm::vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
	glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
	glm::mat4 ModelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
	float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
	)
{
	float tMin = 0.0f;
	float tMax = 100000.0f;

	glm::vec3 OBBposition_worldspace(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);

	glm::vec3 delta = OBBposition_worldspace - ray_origin;

	// Test intersection with the 2 planes perpendicular to the OBB's X axis
	{
		glm::vec3 xaxis(ModelMatrix[0].x, ModelMatrix[0].y, ModelMatrix[0].z);
		float e = glm::dot(xaxis, delta);
		float f = glm::dot(ray_direction, xaxis);

		if ( fabs(f) > 0.001f ){ // Standard case

			float t1 = (e+aabb_min.x)/f; // Intersection with the "left" plane
			float t2 = (e+aabb_max.x)/f; // Intersection with the "right" plane
			// t1 and t2 now contain distances betwen ray origin and ray-plane intersections

			// We want t1 to represent the nearest intersection, 
			// so if it's not the case, invert t1 and t2
			if (t1>t2){
				float w=t1;t1=t2;t2=w; // swap t1 and t2
			}

			// tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
			if (t2 < tMax)
				tMax = t2;
			// tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
			if (t1 > tMin)
				tMin = t1;

			// And here's the trick :
			// If "far" is closer than "near", then there is NO intersection.
			// See the images in the tutorials for the visual explanation.
			if (tMax < tMin)
				return false;
		}
		else if(-e+aabb_min.x > 0.0f || -e+aabb_max.x < 0.0f)
				return false;
		}
	}
	// Test intersection with the 2 planes perpendicular to the OBB's Y axis
	// Exactly the same thing than above.
	{
		glm::vec3 yaxis(ModelMatrix[1].x, ModelMatrix[1].y, ModelMatrix[1].z);
		float e = glm::dot(yaxis, delta);
		float f = glm::dot(ray_direction, yaxis);

		if (fabs(f) > 0.001)
		{
			float t1 = (e+aabb_min.y)/f;
			float t2 = (e+aabb_max.y)/f;

			if (t1>t2){float w=t1;t1=t2;t2=w;}

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
				return false;
		}
		else if(-e+aabb_min.y > 0.0f || -e+aabb_max.y < 0.0f)
			return false;
	}
	// Test intersection with the 2 planes perpendicular to the OBB's Z axis
	// Exactly the same thing than above.
	{
		glm::vec3 zaxis(ModelMatrix[2].x, ModelMatrix[2].y, ModelMatrix[2].z);
		float e = glm::dot(zaxis, delta);
		float f = glm::dot(ray_direction, zaxis);

		if (fabs(f) > 0.001)
		{
			float t1 = (e+aabb_min.z)/f;
			float t2 = (e+aabb_max.z)/f;

			if (t1>t2){float w=t1;t1=t2;t2=w;}

			if ( t2 < tMax )
				tMax = t2;
			if ( t1 > tMin )
				tMin = t1;
			if (tMin > tMax)
				return false;
		}
		else if (-e+aabb_min.z > 0.0f || -e+aabb_max.z < 0.0f)
			return false;
	}
	intersection_distance = tMin;
	return true;
}
*/

void	getnormal_plane(t_vector *result, t_object *object, t_vector *hit_pos)
{
	if (result && object && (hit_pos || !hit_pos))
	{
		vector_set(result,
			object->rotation.x,
			object->rotation.y,
			object->rotation.z);
	}
}
