ARDrone API 1.0
===============

General
-------

This project aims to do a simple API for controlling Parrot ARDrone 2.0 in C.
For the moment, simples commands are available :
-
    * Take on / off
    * Turn left / right
    * Go forward / backward
    * Rotate left / right
    * Go up / down

Here's key mapping :
-
       * Take on / off => 'k'
       * Turn left / right => 'q' / 'd'
       * Go forward / backward => 'z' / 's'
       * Rotate left / right => '4' / '6'
       * Go up / down => '8' / '5'

Compilation :
-------------
```sh
gcc *.c -o ardrone2 -lpthread
```

Functionement :
---------------
* A simple communication between drone and computere is made with UDP socket creation.
* Messages must be sent to the drone ( 192.168.1.1 ) with specific order.
* Parallely, watchdog must be running : When first command is sent, thread start and sends sames messages each 250ms.
* When user want sent command ( pressed key ), watchdog must be stopped during sending.

Next release ..
---------------
* GUI integrated
* API realization