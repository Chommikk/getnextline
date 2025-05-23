#include <unistd.h>

ssize_t ft_read(int fd, void *buf, size_t nbyte)
{
	static int	i;
	if(i == 2)
		return(-1);
	i++;
	return (read(fd, buf, nbyte));
}
