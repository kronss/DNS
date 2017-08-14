#include "dns_server.h"

t_host_name			*create_host(char *line2)
{
	t_host_name	*new_elem;
	
	new_elem = malloc(sizeof(t_host_name));
	if (new_elem)
	{
		new_elem->host_name = ft_strdup(line2);
		new_elem->ip = 0;
		new_elem->next = NULL;
	}
	else
		err_msg("can not allocate memmory");
	return (new_elem);
}

void				add_host(t_host_name **head, char *line2)
{
	t_host_name		*tmp;

	tmp = *head;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_host(line2);
	}
	else
		*head = create_host(line2);
}

void				read_black_list(t_host_name **head, int fd)
{
	char			*line;
	int				check;

	line = NULL;
	while ((check = get_next_line(fd, &line) > 0))
	{
		if (ft_strcmp(line, ""))
			add_host(head, line);
		else
			break ;
	}
	if (check == -1)
		err_msg("read file.conf failed");
	ft_strdel(&line);
}

void				read_wall(char *wall_ip, int fd)
{
	char 			*line;
	int				check;

	line = NULL;
	check = get_next_line(fd, &line);
	if (check == -1)
		err_msg("read file.conf failed");

	ft_strcpy(wall_ip, line);
	ft_strdel(&line);
}

void				read_nameserver(char *dns_ip, int fd)
{
	char			*line;
	int				check;

	line = NULL;
	check = get_next_line(fd, &line);
	if (check == -1)
		err_msg("read file.conf failed");

	ft_strcpy(dns_ip, line);
	ft_strdel(&line);
}

void				read_conf_file(t_data *data, int fd)
{
	char			*line;
	int				check;

	init_data(data, &line);

	while ((check = get_next_line(fd, &line) > 0))
	{
		if (!ft_strcmp(line, "black_list:"))
			read_black_list(&data->head, fd);
		else if (!ft_strcmp(line, "redirect:"))
			read_wall(data->wall_ip, fd);
		else if (!ft_strcmp(line, "nameserver:"))
			read_nameserver(data->dns_ip, fd);
	}
	if (check == -1)
		err_msg("read file.conf failed");

	ft_strdel(&line);
	if (close(fd) == -1)
		err_msg("close()");
}
