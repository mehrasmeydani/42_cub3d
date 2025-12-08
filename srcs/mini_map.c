#include "../header/cubed.h"

ssize_t is_in(char c, char *str)
{
	ssize_t i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

static char	char_set(t_cubed *cube, char c, ssize_t k, ssize_t l)
{
	t_player *player;
	float	rot;

	player = cube->player;
	rot = is_in(c, "ENWS");
	if (rot != -1 && l == MINISQ / 2 && k == MINISQ / 2)
		return (player->rad = cube->pie / 2 * rot, c);
	else if (rot != -1)
		return ('0');
	return (c);
}

void	mini_map_helper(t_cubed *cube, ssize_t i, ssize_t k)
{
	ssize_t	l;
	ssize_t	j;

	j = -1;
	while (cube->map[i][++j])
	{
		l = -1;
		while (++l < MINISQ)
			cube->mini_map[i * MINISQ + k][j * MINISQ + l] = char_set(cube, cube->map[i][j], k, l);
	}
}

bool	mini_map(t_cubed *cube)
{
	ssize_t	i;
	ssize_t	k;

	cube->mini_map = (char **)ft_calloc(cube->max_y * MINISQ + 1, sizeof(char *));
	if (!cube->mini_map)
		return (ft_free(cube->map), 0);
	i = -1;
	while (++i < cube->max_y)
	{
		k = -1;
		while (++k < MINISQ)
		{
			cube->mini_map[i * MINISQ + k] = ft_calloc(ft_strlen(cube->map[i])
				* MINISQ + 1 , sizeof(char));
			if (!cube->mini_map[i * MINISQ + k])
				return (ft_free(cube->mini_map), ft_free(cube->map), 0);
			mini_map_helper(cube, i, k);
		}
	}
	return (1);
}
