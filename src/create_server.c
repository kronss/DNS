#include "dns_server.h"

int						create_server(void)
{
	int					sockfd;
	int					enable;
	struct sockaddr_in	server;


	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		err_msg("socket() failed");

	bzero(&server, sizeof(server));				
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	// server.sin_port = htons(53); // std port
	server.sin_port = htons(5555);  // test port

	enable = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
	{
    	close(sockfd);
    	err_msg("setsockopt(SO_REUSEADDR) failed");
	}

	if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		close(sockfd);
		err_msg("bind() failed");
	}

	return (sockfd);
}
