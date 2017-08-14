#include "dns_server.h"

int					check_list(char *str, t_host_name *tmp)
{
	while (tmp)
	{
		if (ft_strstr(str, tmp->host_name))
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int					check_blacklist(char *buffer, t_data *data)
{
	char			*str;
	char			*tmp;
	char			*buf;

	buf = &buffer[12]; // skip header datagram;

	str = ft_strsub(buf, 1, ft_strlen(buf));
	tmp = str;
	
	while (*tmp != '\0')
	{
		if (!ft_isprint(*tmp))
			*tmp = '.';
		tmp++;
	}

	printf("data ==> %s\nft_strlen(str) == %d\n", str, ft_strlen(str)); // verbose
	// printf("%p\n", data->head);
	// printf("============= %s\n", data->head->host_name);

	if (check_list(str, data->head))
	{
		ft_putendl("black_list");
		ft_strdel(&str);
		return (1);
	}
	else
	{
		/* if not contain in black list */
		ft_putendl("white_list");
		ft_strdel(&str);
		return (0);
	}
}