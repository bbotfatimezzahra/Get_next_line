#include "get_next_line.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	char *str;
	int fd;

	fd = open("../Fdf/test_maps/pylone.fdf", O_RDONLY);
	if (fd == -1)
	{
		printf("error in open function\n");
		return (0);
	}
	str = get_next_line(fd);
	if (!str)
	{
		printf("Empty file\n");
		return (0);
	}
	while(str)
	{
		printf("%s",str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
}
