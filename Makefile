TARGET		= parking
OBJS		= main.o callback.o

#BUILD_PRX = 1

INCDIR		=
CFLAGS		= -G0 -Wall -O2
CXXFLAGS	= $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS		= $(CFLAGS)

LIBDIR =

EXTRA_TARGETS	= EBOOT.PBP
PSP_EBOOT_TITLE= Parking

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak 
 
#INCDIR		=
#CFLAGS		= -G0 -Wall -O2
#CXXFLAGS	= $(CFLAGS) -fno-exceptions -fno-rtti
#ASFLAGS		= $(CFLAGS)
 
#LIBDIR		=
#LDFLAGS		=
#LIBS		= -lm
#LIBS		=
 

 
#EXTRA_TARGETS	= EBOOT.PBP
#PSP_EBOOT_TITLE= Hello World
 
#PSPSDK	= $(shell psp-config --pspsdk-path)
#include $(PSPSDK)/lib/build.mak
