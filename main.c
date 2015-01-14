#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspthreadman.h>
#include <stdlib.h>
 
#include "callback.h"

#define VERS    1 //Talk about this
#define REVS    0
#define POS     5
#define THREADS 10
 
PSP_MODULE_INFO("Parking", PSP_MODULE_USER, VERS, REVS);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER); 
PSP_HEAP_SIZE_MAX();
 
#define printf pspDebugScreenPrintf

int i;
SceUID threads[THREADS];
int parking [POS];
int mutex;

void imprimirParking()
{
	printf("[");
	for (i = 0; i < POS; i++) {
		printf("%d", parking[i]);
		if (i == POS-1) {
			printf("]\n");
		} else {
			printf("][");
		}
	}
}

void coche()
{
	while(isRunning())
		{
			sceKernelDelayThread(1000000 * (rand() % 10 + 1));
			sceKernelWaitSema(mutex, 1, 0); //lock
				for (i = 0; i < POS; i++) {
					if (parking[i] == 0) {
						parking[i] = sceKernelGetThreadId();
						printf("Coche %d aparca en el parking.\n", sceKernelGetThreadId());
						imprimirParking();
						sceDisplayWaitVblankStart();
						break;
					}
				}
				
			sceKernelSignalSema(mutex, 1); //unlock

			//sleep
			sceKernelDelayThread(1000000 * (rand() % 10 + 1));

			sceKernelWaitSema(mutex, 1, 0); //lock
				for (i = 0; i < POS; i++) {
					if (parking[i] == sceKernelGetThreadId()) {
						parking[i] = 0;
						printf("Coche %d sale del parking.\n", sceKernelGetThreadId());
						imprimirParking();
						sceDisplayWaitVblankStart();
						break;
					}
				}
			sceKernelSignalSema(mutex, 1); //unlock

			//sleep
			//sceKernelSleepThread();
			sceKernelDelayThread(1000000 * (rand() % 10 + 1));
		}
}

int main()
{       
	pspDebugScreenInit();
	setupExitCallback();

	//Inicializamos parking a 0
	for (i = 0; i < POS; i++)
		parking[i] = 0;

	//Creamos un mutex
	mutex = sceKernelCreateSema("mutex", 0, 1, 1, 0);


	//Comenzamos a escribir desde la esquina superior izquierda
	pspDebugScreenSetXY(0, 0);

	//Creacion de los threads
	for (i = 0; i < 10; i++) {
		threads[i] = sceKernelCreateThread("coche" + i, (SceKernelThreadEntry)coche, 0x18, 0x10000, 0, NULL);
		printf("Thread creado con id %d\n",threads[i]);
		
	}
	for (i = 0; i < 10; i++) {
		printf("Arrancado thread? %d\n", sceKernelStartThread(threads[i], 0, 0));
	}
 
	//Bucle while infinito, no tengo que hacer nada
	while(isRunning())
	{
		sceKernelDelayThread(1000000 * 100000);
	}
 
	//Salida segura del modo kernel
	sceKernelExitGame();	
	return 0;
}


