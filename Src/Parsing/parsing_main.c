#include "../../Inc/cube3d.h"

int	main(int ac, char **av)
{
	t_parse	*data;

	if (ac != 2 || !av)
		return (parse_error("Wrong number of arguments"));
	data = NULL;
	if (init_parse_data(&data))
		return (1);
	if (parse_check_fname(av[1], data))
		return (free_data(data), 1);
	if (parse_textures(data))
	{
		/*printf("Ceiling->%X,<-\n", data->ceiling);
		printf("Floor->%X<-\n", data->floor);
		printf("NO->%s<-\n", data->n_face);
		printf("SO->%s<-\n", data->s_face);
		printf("EA->%s<-\n", data->e_face);
		printf("WE->%s<-\n", data->w_face);*/
		return (free_data(data), 1);
	}
	/*printf("Ceiling->%X<-\n", data->ceiling);
	printf("Floor->%X<-\n", data->floor);
	printf("NO->%s<-\n", data->n_face);
	printf("SO->%s<-\n", data->s_face);
	printf("EA->%s<-\n", data->e_face);
	printf("WE->%s<-\n", data->w_face); */
	free_data(data);
	return (0);
}
