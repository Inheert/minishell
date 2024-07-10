#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("./test.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	line = NULL;
	return (0);
}
