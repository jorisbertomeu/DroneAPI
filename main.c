/*
** main.c for APIDrone in /home/jobertomeu/Documents/APIDrone
** 
** Made by Joris Bertomeu
** Login   <jobertomeu@epitech.net>
** 
** Started on  Fri Jun 20 15:45:33 2014 Joris Bertomeu
** Last update Fri Jun 20 20:12:35 2014 Joris Bertomeu
*/

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libclient.h"
#include "stdafx.h"
#include "Drone.h"

int	iSeq=1;
int	isDroneStarted = 0;
char	szSendBuffer[4096];
float	fSpeed= (float) 0.2;
int	iStartBit = 0;
int	bKeyIsPressed = 0;
int	sockATCMD;
t_libclient	*slib;
int	flag = 0;

void	print_error(char *msg)
{
  perror("API_ERROR ");
  /* printf("Error : %s\n", msg); */
  exit (-1);
}

void	 SendATCmd(char *szCommand, int iLen)
{
  write(slib->to_server_socket, szCommand, strlen(szCommand));
  usleep(1);
}

void		SendPCMD_AT(int enable, float roll, float pitch, float gaz, float yaw)
{
  int		fiPitch;
  int		fiRoll;
  int		fiGaz;
  int		fiYaw;

  fiPitch = pitch;
  fiRoll = roll;
  fiGaz = gaz;
  fiYaw = yaw;
  sprintf(szSendBuffer, "AT*PCMD=%d,%d,%d,%d,%d,%d\r", ++iSeq, enable,
	    fiRoll, fiPitch, fiGaz, fiYaw);
  SendATCmd(szSendBuffer, strlen(szSendBuffer));
}

void	*alive()
{
  float pitch = 0;
  float roll = 0;
  float gaz = 0;
  float yaw = 0;

  while (1)
    {
      if (flag == 0)
	{
	  SendPCMD_AT(0, roll, pitch, gaz, yaw);
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r",++iSeq,iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  sprintf(szSendBuffer, "AT*COMWDG=%d\r",++iSeq);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  usleep(250000);
	}
    }
}

void	MessageHandler(char *str)
{
  float pitch = 0;
  float roll = 0;
  float gaz = 0;
  float yaw = 0;
  pthread_t	thread;

  if (str[0] == 'q') /* Gauche */
    {
      roll = -fSpeed;
      SendPCMD_AT(1, roll, pitch, gaz, yaw);
    }
  else if (str[0] == 'z') /* Avancer */
    {
      pitch = -fSpeed;
      SendPCMD_AT(1, roll, pitch, gaz, yaw);
    }
  else if (str[0] == 'd') /* Droite */
    {
      roll = fSpeed;
      SendPCMD_AT(1, roll, pitch, gaz, yaw);
    }
  else if (str[0] == 's') /* reculer */
    {
      pitch = fSpeed;
      SendPCMD_AT(1, roll, pitch, gaz, yaw);
    }
  else if (str[0] == 'k')
    {
      if (isDroneStarted == 0)
	{
	  flag = 0;
	  SendATCmd("AT*CONFIG=\"general:navdata_demo\",\"TRUE\"\r",
		    strlen("AT*CONFIG=\"general:navdata_demo\",\"TRUE\"\r"));
	  SendATCmd("AT*CTRL=5,0\r", strlen("AT*CTRL=5,0\r"));
	  iSeq = 1;
	  sprintf(szSendBuffer,
		    "AT*CONFIG=%d,\"CONTROL:altitude_max\",\"3000\"\r", iSeq);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  sprintf(szSendBuffer, "AT*FTRIM\r");
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  sprintf(szSendBuffer, "AT*FTRIM=%d\r", ++iSeq);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  usleep(50);
	  iStartBit = iStartBit | (1 << 9);
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  isDroneStarted = 1;
	  pthread_create(&thread, NULL, &alive, NULL);
	  /* THREAD Toute les 250ms */
	}
      else
	{
	  flag = 1;
	  /* Kill thread */
	  iStartBit = iStartBit &~ (1 << 9);
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  isDroneStarted = 0;
	}
    }
  else if (str[0] == '4')
    {
      yaw = -fSpeed;
      SendPCMD_AT(1, roll, pitch, gaz, yaw);
    }
  else if (str[0] == '6')
    {
      yaw = fSpeed;
      SendPCMD_AT(1, roll, pitch, gaz, yaw);
    }
  else if (str[0] == '5')
    {
      gaz = -fSpeed;
      SendPCMD_AT(1, roll, pitch, gaz, yaw);
    }
  else if (str[0] == '8')
    {
      gaz = fSpeed;
      SendPCMD_AT(1, roll, pitch, gaz, yaw);
    }
  else if (str[0] == 'r')
    {
      if (iStartBit & (1 << 8))
	{
	  iStartBit = iStartBit | (1 << 8);
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  iStartBit = iStartBit &~ (1 << 8);
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	}
      else
	{
	  iStartBit = iStartBit | (1 << 8);
	  iStartBit = iStartBit &~ (1 << 9);
	  sprintf(szSendBuffer, "AT*REF=%d,%d\r", ++iSeq, iStartBit);
	  SendATCmd(szSendBuffer, strlen(szSendBuffer));
	  flag = 1;
	  /* Kill thread */
	}
    }
  else
    {
      SendPCMD_AT(0, roll, pitch, gaz, yaw);
      sprintf(szSendBuffer, "AT*COMWDG=%d\r", ++iSeq);
      SendATCmd(szSendBuffer, strlen(szSendBuffer));
    }
  /* ReleaseMutex(hMyMutex); */
}

int			SetUpATSocket()
{
  struct hostent	*localHost;
  char			*ip;
  struct sockaddr_in	LocalAddr;
  int			LocalAddrSize = sizeof (LocalAddr);
  int			rc;

  ip = malloc((INET_ADDRSTRLEN + 15) * sizeof(char));
  memset(ip, 0, (INET_ADDRSTRLEN + 15));
  LocalAddr.sin_family = AF_INET;
  LocalAddr.sin_addr.s_addr = INADDR_ANY;
  LocalAddr.sin_port = htons(AT_PORT + 100);
  sockATCMD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sockATCMD == -1)
    print_error("Socket Failed");
  localHost = gethostbyname("");
  rc = bind(sockATCMD, (struct sockaddr *) &LocalAddr, LocalAddrSize);
  if (rc == -1)
    return (0);
  return (1);
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

int		main(int ac, char **argv)
{
  char		buff[128];
  pthread_t	thread;

  if (ac == 3)
    {
      slib = malloc(sizeof(*slib));
      init_lib(slib, argv[1], atoi(argv[2]));
      slib->flag = 1;
      aff_directives();
      while (1)
	{
	  memset(buff, 0, 128);
	  write(1, "> ", 3);
	  read(0, &buff, 128);
	  MessageHandler(buff);
	  printf("> Succefully sent\n");
	}
    }
  else
    printf("Usage : %s <IP_addr> <Port>\n", argv[0]);
  return (0);
}

void	WndProc()
{
  /* HWND hWndOwner; */
  /* RECT rcOwner,rcDlg,rc; */
  /* int wmId, wmEvent; */
  /* HDC hdc; */
  /* float pitch=0; */
  /* float roll=0; */
  /* float gaz=0; */
  /* float yaw=0; */

  /* switch (message) */
  /*   { */
  /*   case WM_CREATE: */
  /*     { */
  /* 	/\* hMyMutex=CreateMutex(NULL,false,"MyMutex_ArDrone"); *\/ */
  /* 	if (SetUpATSocket() == 0) */
  /* 	  print_error("Socket creation failed"); */
  /*     } */
  /*     break; */
  /*   case WM_TIMER: */
  /*     { */
  /* 	if (idletime >=200) */
  /* 	  { */
  /* 	    SendPCMD_AT(0, roll, pitch, gaz, yaw); */
  /* 	    sprintf(szSendBuffer, "AT*REF=%d,%d\r",++iSeq,iStartBit); */
  /* 	    SendATCmd(szSendBuffer, strlen(szSendBuffer)); */
  /* 	    sprintf(szSendBuffer, "AT*COMWDG=%d\r",++iSeq); */
  /* 	    SendATCmd(szSendBuffer, strlen(szSendBuffer)); */
  /* 	  } */
  /* 	/\* ReleaseMutex(hMyMutex); *\/ */
  /*     } */
  /*     break; */
  /*   } */
  /* return (0); */
}
