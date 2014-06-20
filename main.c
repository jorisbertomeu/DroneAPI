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

int		iStartBit = 0;
t_drone         drone;

void	print_error(char *msg)
{
  perror("API_ERROR ");
  exit (-1);
}

void	 SendATCmd(char *szCommand, int iLen)
{
  write(drone.slib->to_server_socket, szCommand, strlen(szCommand));
  usleep(1);
}

void		SendPCMD_AT(int enable, float roll, float pitch, float gaz, float yaw)
{
  int		fiPitch;
  int		fiRoll;
  int		fiGaz;
  int		fiYaw;
  char		szSendBuffer[4096];

  fiPitch = pitch;
  fiRoll = roll;
  fiGaz = gaz;
  fiYaw = yaw;
  memset(szSendBuffer, 0, 4096);
  sprintf(szSendBuffer, "AT*PCMD=%d,%d,%d,%d,%d,%d\r", ++drone.iSeq, enable,
	    fiRoll, fiPitch, fiGaz, fiYaw);
  SendATCmd(szSendBuffer, strlen(szSendBuffer));
}

void	*alive()
{
  char	szSendBuffer[4096];

  while (1)
    {
      if (drone.flag == 0)
	{
	  SendPCMD_AT(0, drone.params.roll,
		      drone.params.pitch,
		      drone.params.gaz,
		      drone.params.yaw);
	  memset(szSendBuffer, 0, 4096);
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++drone.iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  memset(szSendBuffer, 0, 4096);
	  sprintf(szSendBuffer, "AT*COMWDG=%d\r", ++drone.iSeq);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  usleep(250000);
	}
    }
}

void		MessageHandler(int id)
{
  pthread_t	thread;
  char		szSendBuffer[4096];

  printf("Pressed : %c\n", id);
  if (id == KEY_LEFT_TURN) /* Gauche */
    {
      drone.params.roll = -drone.params.speed;
      SendPCMD_AT(1, drone.params.roll, drone.params.pitch, drone.params.gaz, drone.params.yaw);
    }
  else if (id == KEY_FORWARD) /* Avancer */
    {
      drone.params.pitch = -drone.params.speed;
      SendPCMD_AT(1, drone.params.roll, drone.params.pitch, drone.params.gaz, drone.params.yaw);
    }
  else if (id == KEY_RIGHT_TURN) /* Droite */
    {
      drone.params.roll = drone.params.speed;
      SendPCMD_AT(1, drone.params.roll, drone.params.pitch, drone.params.gaz, drone.params.yaw);
    }
  else if (id == KEY_BACKWARD) /* reculer */
    {
      drone.params.pitch = drone.params.speed;
      SendPCMD_AT(1, drone.params.roll, drone.params.pitch, drone.params.gaz, drone.params.yaw);
    }
  else if (id == KEY_TAKEON)
    {
      if (drone.isDroneStarted == 0)
	{
	  drone.flag = 0;
	  SendATCmd("AT*CONFIG=\"general:navdata_demo\",\"TRUE\"\r",
		    strlen("AT*CONFIG=\"general:navdata_demo\",\"TRUE\"\r"));
	  SendATCmd("AT*CTRL=5,0\r", strlen("AT*CTRL=5,0\r"));
	  drone.iSeq = 1;
	  sprintf(szSendBuffer,
		    "AT*CONFIG=%d,\"CONTROL:altitude_max\",\"3000\"\r", drone.iSeq);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  memset(szSendBuffer, 0, 4096);
	  sprintf(szSendBuffer, "AT*FTRIM\r");
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  memset(szSendBuffer, 0, 4096);
	  sprintf(szSendBuffer, "AT*FTRIM=%d\r", ++drone.iSeq);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  usleep(50);
	  iStartBit = iStartBit | (1 << 9);
	  memset(szSendBuffer, 0, 4096);
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++drone.iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  memset(szSendBuffer, 0, 4096);
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++drone.iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  drone.isDroneStarted = 1;
	  pthread_create(&thread, NULL, &alive, NULL);
	  /* THREAD Toute les 250ms */
	}
      else
	{
	  drone.flag = 1;
	  /* Kill thread */
	  iStartBit = iStartBit &~ (1 << 9);
	  memset(szSendBuffer, 0, 4096);
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++drone.iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  memset(szSendBuffer, 0, 4096);
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++drone.iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  drone.isDroneStarted = 0;
	}
    }
  else if (id == KEY_ROT_LEFT) /* Rot gauche */
    {
      drone.params.yaw = -drone.params.speed;
      SendPCMD_AT(1, drone.params.roll, drone.params.pitch, drone.params.gaz, drone.params.yaw);
    }
  else if (id == KEY_ROT_RIGHT) /* rot droite */
    {
      drone.params.yaw = drone.params.speed;
      SendPCMD_AT(1, drone.params.roll, drone.params.pitch, drone.params.gaz, drone.params.yaw);
    }
  else if (id == KEY_GO_DOWN) /* descendre */
    {
      drone.params.gaz = -drone.params.speed;
      SendPCMD_AT(1, drone.params.roll, drone.params.pitch, drone.params.gaz, drone.params.yaw);
    }
  else if (id == KEY_GO_UP) /* monter */
    {
      drone.params.gaz = drone.params.speed;
      SendPCMD_AT(1, drone.params.roll, drone.params.pitch, drone.params.gaz, drone.params.yaw);
    }
  else if (id == KEY_EMERGENCY)
    {
      if (iStartBit & (1 << 8))
	{
	  iStartBit = iStartBit | (1 << 8);
	  memset(szSendBuffer, 0, 4096);
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++drone.iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  iStartBit = iStartBit &~ (1 << 8);
	  memset(szSendBuffer, 0, 4096);
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++drone.iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	}
      else
	{
	  iStartBit = iStartBit | (1 << 8);
	  iStartBit = iStartBit &~ (1 << 9);
	  memset(szSendBuffer, 0, 4096);
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++drone.iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  drone.flag = 1;
	  /* Kill thread */
	}
    }
  else
    {
      SendPCMD_AT(0, drone.params.roll, drone.params.pitch, drone.params.gaz, drone.params.yaw);
      memset(szSendBuffer, 0, 4096);
      sprintf(szSendBuffer, "AT*COMWDG=%d\r", ++drone.iSeq);
      SendATCmd(szSendBuffer, strlen(szSendBuffer));
    }
}

void	aff_directives()
{
  printf("=============== ARDRONE2.0 API By\
 Joris Bertomeu ===============\n\n");
  printf("k : Décoller / Aterrir\n");
  /* printf("SPEED : \n"); */
  printf("z : Avancer - s : Reculer - q :\
 Tourner à gauche - d : Tourner à droite\n");
  printf("8 : Monter - 5 : Descendre - 4 :\
 Rotation gauche - 6 : Rotation droite\n");
  printf("r : Arrêt d'urgence\n\n");
  printf("================================================================\n");
}

void	init_params()
{
  drone.params.roll = 0;
  drone.params.pitch = 0;
  drone.params.gaz = 0;
  drone.params.yaw = 0;
  drone.params.speed = 0.2;
}

void init_struct()
{
  drone.iSeq = 1;
  drone.isDroneStarted = 0;
  drone.flag = 0;
  init_params();
}

int		main(int ac, char **argv)
{
  char		buff[128];
  pthread_t	thread;

  if (ac == 3)
    {
      drone.slib = malloc(sizeof(*(drone.slib)));
      /* init_lib(drone.slib, argv[1], atoi(argv[2])); */
      init_struct();
      drone.slib->flag = 1;
      aff_directives();
      while (1)
	{
	  memset(buff, 0, 128);
	  write(1, "> ", 3);
	  read(0, &buff, 128);
	  MessageHandler(buff[0]);
	  printf("> Succefully sent\n");
	}
    }
  else
    printf("Usage : %s <IP_addr> <Port>\n", argv[0]);
  return (0);
}
