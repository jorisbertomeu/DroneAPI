/*
** drone_api.h for APIDrone in /home/jobertomeu/Documents/APIDrone/cldr
** 
** Made by Joris Bertomeu
** Login   <jobertomeu@epitech.net>
** 
** Started on  Fri Jun 20 21:15:03 2014 Joris Bertomeu
** Last update Fri Jun 20 21:38:36 2014 Joris Bertomeu
*/

#ifndef APIDRONE_H_
#define APIDRONE_H_

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include "libclient.h"

# define AT_PORT	5556
# define KEY_LEFT_TURN	'q'
# define KEY_RIGHT_TURN	'd'
# define KEY_FORWARD	'z'
# define KEY_BACKWARD	's'
# define KEY_TAKEON	'k'
# define KEY_ROT_LEFT	'4'
# define KEY_ROT_RIGHT	'6'
# define KEY_GO_UP	'8'
# define KEY_GO_DOWN	'5'
# define KEY_EMERGENCY	'r'

typedef struct s_params t_params
struct s_params
{
  float roll;
  float pitch;
  float gaz;
  float yaw;
}

typedef struct s_globl t_drone
struct s_globl
{
  t_libclient *slib;
  int iSeq;
  int isDroneStarted;
  int flag;
  t_params params;
}

#endif /* APIDRONE_H */
