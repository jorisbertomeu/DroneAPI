/*
** drone_api.h for APIDrone in /home/jobertomeu/Documents/APIDrone/cldr
** 
** Made by Joris Bertomeu
** Login   <jobertomeu@epitech.net>
** 
** Started on  Fri Jun 20 21:15:03 2014 Joris Bertomeu
** Last update Fri Jun 20 21:17:55 2014 Joris Bertomeu
*/

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "libclient.h"

#define AT_PORT	5556
