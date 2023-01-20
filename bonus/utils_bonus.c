#include <libft.h>
# include "structs_bonus.h"

//tv_sec = seconds, tv.usec = micro seconds;
//gettimeofday: returns time in microseconds
//init_time returns time in milliseconds
int	get_time(void)
{
	struct timeval	cur_time;
	unsigned int	time;

	gettimeofday(&cur_time, NULL);
	time = (cur_time.tv_sec * 1000000) + cur_time.tv_usec;
	return (time);
}

//in milliseconds
int	get_cur_time(t_ctx *ctx)
{
	unsigned int	t;

	t = (get_time() - ctx->time.init_time);
	return (t);
}

//pas oublier free
void	error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
//	system("leaks cub3D");
	exit(EXIT_FAILURE);
}
