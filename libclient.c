/*
** libclient.c for libclient in /home/jobertomeu/Work/ftp
** 
** Made by Joris Bertomeu
** Login   <jobertomeu@epitech.net>
** 
** Started on  Sat May 10 15:21:44 2014 Joris Bertomeu
** Last update Fri Jun 20 21:31:50 2014 Joris Bertomeu
*/

#include "libclient.h"

void	print_error_lib(char *str)
{
  fprintf(stderr, "/!\\========== ERROR ==========/!\\\n\nNETWORK\
_ERROR : (Code error : 0x568) >%s\n\t*Check connection between Drone\
 and Computer\n\t*Check your firewall\n\t*Check functionment with\
 another device\n\n/!\\========== ERROR ==========/!\\\n\n", str);
  exit(EXIT_FAILURE);
}

void	check_hostaddr(t_libclient *slib, char *ip)
{
  if ((long) slib->hostaddr != (long) -1)
    {
      bcopy(&(slib->hostaddr), &(slib->serversockaddr.sin_addr),
	    sizeof (slib->hostaddr));
      return ;
    }
  slib->serverhostent = gethostbyname(ip);
  if (slib->serverhostent == NULL)
    print_error_lib("Get host failed\n");
  bcopy(&(slib->serverhostent->h_addr), &(slib->serversockaddr.sin_addr),
	slib->serverhostent->h_length);
}

void	init_lib(t_libclient *slib, char *ip, int port)
{
  slib->to_server_socket = -1;
  memset(&(slib->serversockaddr), 0, sizeof (slib->serversockaddr));
  slib->hostaddr = inet_addr(ip);
  check_hostaddr(slib, ip);
  slib->serversockaddr.sin_port = htons(port);
  slib->serversockaddr.sin_family = AF_INET;
  if ((slib->to_server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    print_error_lib("Socket creation failed\n");
  if(connect(slib->to_server_socket,
	      (struct sockaddr *) &slib->serversockaddr,
	      sizeof (slib->serversockaddr)) < 0 )
    print_error_lib("Connection request failed\n");
}
