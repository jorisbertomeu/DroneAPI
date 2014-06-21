/*
** main.c for APIDrone in /home/jobertomeu/Documents/APIDrone
** 
** Made by Joris Bertomeu
** Login   <jobertomeu@epitech.net>
** 
** Started on  Fri Jun 20 15:45:33 2014 Joris Bertomeu
** Last update Fri Jun 20 21:40:08 2014 Joris Bertomeu
*/

#include "drone_api.h"

int		main(int ac, char **argv)
{
  char		buff[128];

  init_api(ac, argv); /* Required line */
  aff_directives("fr"); /* fr || en */
  while (1)
    {
      memset(buff, 0, 128);
      write(1, "> ", 3);
      read(0, &buff, 128);
      treat_api(buff[0]);
      printf("> Succefully sent\n");
    }
  return (0);
}
