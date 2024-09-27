#include "fillit.h"

static char	**tmtype_to_strls_2(t_tmtype type)
{
	if (type == l_nrm_rot180)
		return (ft_strdivide("##.#.#", 2));
	if (type == l_nrm_rot270)
		return (ft_strdivide("..####", 3));
	if (type == l_rev_rot0)
		return (ft_strdivide(".#.###", 2));
	if (type == l_rev_rot90)
		return (ft_strdivide("#..###", 3));
	if (type == l_rev_rot180)
		return (ft_strdivide("###.#.", 2));
	if (type == l_rev_rot270)
		return (ft_strdivide("###..#", 3));
	if (type == t_rot0)
		return (ft_strdivide("###.#.", 3));
	if (type == t_rot90)
		return (ft_strdivide(".###.#", 2));
	if (type == t_rot180)
		return (ft_strdivide(".#.###", 3));
	if (type == t_rot270)
		return (ft_strdivide("#.###.", 2));
	return (NULL);
}

char		**tmtype_to_strls(t_tmtype type)
{
	if (type == square)
		return (ft_strdivide("####", 2));
	if (type == line_hrz)
		return (ft_strdivide("####", 4));
	if (type == line_vrt)
		return (ft_strdivide("####", 1));
	if (type == s_hrz)
		return (ft_strdivide(".####.", 3));
	if (type == s_vrt)
		return (ft_strdivide("#.##.#", 2));
	if (type == z_hrz)
		return (ft_strdivide("##..##", 3));
	if (type == z_vrt)
		return (ft_strdivide(".####.", 2));
	if (type == l_nrm_rot0)
		return (ft_strdivide("#.#.##", 2));
	if (type == l_nrm_rot90)
		return (ft_strdivide("####..", 3));
	return (tmtype_to_strls_2(type));
}
