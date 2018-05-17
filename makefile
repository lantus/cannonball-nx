 

ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitpro")
endif

TOPDIR ?= $(CURDIR)
 
include $(DEVKITPRO)/libnx/switch_rules

export BUILD_EXEFS_SRC := build/exefs

APP_TITLE := Cannonball
APP_DESCRIPTION := Cannonball
APP_AUTHOR := MVG
APP_VERSION := 1.0.0

WINDRES   = windres.exe
OBJ       = obj/main.o obj/romloader.o obj/roms.o obj/trackloader.o obj/utils.o obj/video.o obj/audio.o obj/input.o obj/renderbase.o obj/rendersurface.o obj/timer.o obj/oanimseq.o obj/oattractai.o obj/obonus.o obj/ocrash.o obj/oferrari.o obj/ohiscore.o obj/ohud.o obj/oinitengine.o obj/oinputs.o obj/olevelobjs.o obj/ologo.o obj/omap.o obj/omusic.o obj/ooutputs.o obj/opalette.o obj/oroad.o obj/osmoke.o obj/osprite.o obj/osprites.o obj/ostats.o obj/otiles.o obj/otraffic.o obj/outils.o obj/outrun.o obj/osound.o obj/osoundint.o obj/segapcm.o obj/soundchip.o obj/ym2151.o obj/hwroad.o obj/hwsprites.o obj/hwtiles.o obj/cabdiag.o obj/config.o obj/menu.o obj/ttrial.o obj/asyncserial.o obj/interface.o obj/ffeedback.o
LINKOBJ   = obj/main.o obj/romloader.o obj/roms.o obj/trackloader.o obj/utils.o obj/video.o obj/audio.o obj/input.o obj/renderbase.o obj/rendersurface.o obj/timer.o obj/oanimseq.o obj/oattractai.o obj/obonus.o obj/ocrash.o obj/oferrari.o obj/ohiscore.o obj/ohud.o obj/oinitengine.o obj/oinputs.o obj/olevelobjs.o obj/ologo.o obj/omap.o obj/omusic.o obj/ooutputs.o obj/opalette.o obj/oroad.o obj/osmoke.o obj/osprite.o obj/osprites.o obj/ostats.o obj/otiles.o obj/otraffic.o obj/outils.o obj/outrun.o obj/osound.o obj/osoundint.o obj/segapcm.o obj/soundchip.o obj/ym2151.o obj/hwroad.o obj/hwsprites.o obj/hwtiles.o obj/cabdiag.o obj/config.o obj/menu.o obj/ttrial.o obj/asyncserial.o obj/interface.o obj/ffeedback.o
LIBS      = -specs=$(DEVKITPRO)/libnx/switch.specs -g -march=armv8-a -mtune=cortex-a57 -mtp=soft -fPIE -L$(DEVKITPRO)/libnx/lib -L$(DEVKITPRO)/portlibs/switch/lib -lSDL2 -lnx
INCS      = -I$(DEVKITPRO)/portlibs/switch/include/SDL2 -I"src/main"  
CXXINCS   = -I$(DEVKITPRO)/portlibs/switch/include/SDL2 -I"src/main"
RCINCS    = --include-dir "C:/DEVELO~1/AMIDEV~1/include"
BIN       = release/cannonball.elf
BUILD	  =	build
BINDIR	  = release
DEFINES   =  -DSWITCH -DSDL2
CXXFLAGS  = $(CXXINCS) $(DEFINES) -march=armv8-a -mtune=cortex-a57 -mtp=soft -fPIE -O2
CFLAGS    = $(INCS) $(DEFINES)   --march=armv8-a -mtune=cortex-a57 -mtp=soft -fPIE -O2
GPROF     = gprof.exe
RM        = rm -f
LINK      = aarch64-none-elf-g++ 
CPP		  = aarch64-none-elf-g++
OUTPUT    = cannonball

.PHONY: all all-before all-after clean clean-custom
all: all-before $(BIN) all-after

clean: clean-custom
	$(RM) $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(LINK) $(LINKOBJ) -o "release\cannonball.elf" $(LIBS)

obj/main.o: $(GLOBALDEPS) src/main/main.cpp src/main/stdint.hpp src/main/sdl2/timer.hpp src/main/sdl2/input.hpp src/main/sdl/timer.hpp src/main/sdl/input.hpp src/main/video.hpp src/main/stdint.hpp src/main/globals.hpp src/main/stdint.hpp src/main/roms.hpp src/main/romloader.hpp src/main/hwvideo/hwtiles.hpp src/main/hwvideo/hwsprites.hpp src/main/hwvideo/hwroad.hpp src/main/romloader.hpp src/main/trackloader.hpp src/main/globals.hpp src/main/main.hpp src/main/globals.hpp src/main/sdl2/audio.hpp src/main/sdl/audio.hpp src/main/setup.hpp src/main/frontend/config.hpp src/main/frontend/menu.hpp src/main/cannonboard/interface.hpp src/main/engine/oinputs.hpp src/main/engine/outrun.hpp src/main/engine/oaddresses.hpp src/main/engine/osprites.hpp src/main/engine/oentry.hpp src/main/engine/osprite.hpp src/main/engine/outrun.hpp src/main/engine/ooutputs.hpp src/main/directx/ffeedback.hpp src/main/engine/audio/osoundint.hpp src/main/engine/audio/osound.hpp
	$(CPP) -c src/main/main.cpp -o obj/main.o $(CXXFLAGS)

obj/romloader.o: $(GLOBALDEPS) src/main/romloader.cpp src/main/stdint.hpp src/main/romloader.hpp
	$(CPP) -c src/main/romloader.cpp -o obj/romloader.o $(CXXFLAGS)

obj/roms.o: $(GLOBALDEPS) src/main/roms.cpp src/main/stdint.hpp src/main/roms.hpp src/main/romloader.hpp
	$(CPP) -c src/main/roms.cpp -o obj/roms.o $(CXXFLAGS)

obj/trackloader.o: $(GLOBALDEPS) src/main/trackloader.cpp src/main/trackloader.hpp src/main/globals.hpp src/main/stdint.hpp src/main/roms.hpp src/main/romloader.hpp src/main/engine/outrun.hpp src/main/engine/oaddresses.hpp src/main/engine/osprites.hpp src/main/engine/oentry.hpp src/main/engine/osprite.hpp src/main/engine/outrun.hpp src/main/engine/oaddresses.hpp
	$(CPP) -c src/main/trackloader.cpp -o obj/trackloader.o $(CXXFLAGS)

obj/utils.o: $(GLOBALDEPS) src/main/utils.cpp src/main/utils.hpp src/main/stdint.hpp
	$(CPP) -c src/main/utils.cpp -o obj/utils.o $(CXXFLAGS)

obj/video.o: $(GLOBALDEPS) src/main/video.cpp src/main/video.hpp src/main/stdint.hpp src/main/globals.hpp src/main/stdint.hpp src/main/roms.hpp src/main/romloader.hpp src/main/hwvideo/hwtiles.hpp src/main/hwvideo/hwsprites.hpp src/main/hwvideo/hwroad.hpp src/main/setup.hpp src/main/globals.hpp src/main/frontend/config.hpp src/main/engine/oinitengine.hpp src/main/engine/outrun.hpp src/main/engine/oaddresses.hpp src/main/engine/osprites.hpp src/main/engine/oentry.hpp src/main/engine/osprite.hpp src/main/engine/outrun.hpp src/main/sdl2/rendergl.hpp src/main/sdl2/renderbase.hpp src/main/stdint.hpp src/main/globals.hpp src/main/setup.hpp src/main/sdl/rendergl.hpp src/main/sdl/renderbase.hpp src/main/stdint.hpp src/main/globals.hpp src/main/setup.hpp src/main/sdl2/rendergles.hpp src/main/sdl2/renderbase.hpp src/main/sdl2/rendersurface.hpp src/main/sdl2/renderbase.hpp src/main/sdl/rendersw.hpp src/main/sdl/renderbase.hpp
	$(CPP) -c src/main/video.cpp -o obj/video.o $(CXXFLAGS)

obj/audio.o: $(GLOBALDEPS) src/main/sdl/audio.cpp
	$(CPP) -c src/main/sdl/audio.cpp -o obj/audio.o $(CXXFLAGS)

obj/input.o: $(GLOBALDEPS) src/main/sdl2/input.cpp
	$(CPP) -c src/main/sdl2/input.cpp -o obj/input.o $(CXXFLAGS)

obj/renderbase.o: $(GLOBALDEPS) src/main/sdl2/renderbase.cpp src/main/sdl2/renderbase.hpp src/main/stdint.hpp src/main/globals.hpp src/main/stdint.hpp src/main/setup.hpp
	$(CPP) -c src/main/sdl2/renderbase.cpp -o obj/renderbase.o $(CXXFLAGS)

obj/rendersurface.o: $(GLOBALDEPS) src/main/sdl2/rendersurface.cpp 
	$(CPP) -c src/main/sdl2/rendersurface.cpp  -o obj/rendersurface.o $(CXXFLAGS)

obj/timer.o: $(GLOBALDEPS) src/main/sdl2/timer.cpp
	$(CPP) -c src/main/sdl/timer.cpp -o obj/timer.o $(CXXFLAGS)

obj/oanimseq.o: $(GLOBALDEPS) src/main/engine/oanimseq.cpp
	$(CPP) -c src/main/engine/oanimseq.cpp -o obj/oanimseq.o $(CXXFLAGS)

obj/oattractai.o: $(GLOBALDEPS) src/main/engine/oattractai.cpp
	$(CPP) -c src/main/engine/oattractai.cpp -o obj/oattractai.o $(CXXFLAGS)

obj/obonus.o: $(GLOBALDEPS) src/main/engine/obonus.cpp
	$(CPP) -c src/main/engine/obonus.cpp -o obj/obonus.o $(CXXFLAGS)

obj/ocrash.o: $(GLOBALDEPS) src/main/engine/ocrash.cpp
	$(CPP) -c src/main/engine/ocrash.cpp -o obj/ocrash.o $(CXXFLAGS)

obj/oferrari.o: $(GLOBALDEPS) src/main/engine/oferrari.cpp
	$(CPP) -c src/main/engine/oferrari.cpp -o obj/oferrari.o $(CXXFLAGS)

obj/ohiscore.o: $(GLOBALDEPS) src/main/engine/ohiscore.cpp
	$(CPP) -c src/main/engine/ohiscore.cpp -o obj/ohiscore.o $(CXXFLAGS)

obj/ohud.o: $(GLOBALDEPS) src/main/engine/ohud.cpp src/main/utils.hpp src/main/stdint.hpp
	$(CPP) -c src/main/engine/ohud.cpp -o obj/ohud.o $(CXXFLAGS)

obj/oinitengine.o: $(GLOBALDEPS) src/main/engine/oinitengine.cpp
	$(CPP) -c src/main/engine/oinitengine.cpp -o obj/oinitengine.o $(CXXFLAGS)

obj/oinputs.o: $(GLOBALDEPS) src/main/engine/oinputs.cpp
	$(CPP) -c src/main/engine/oinputs.cpp -o obj/oinputs.o $(CXXFLAGS)

obj/olevelobjs.o: $(GLOBALDEPS) src/main/engine/olevelobjs.cpp src/main/trackloader.hpp src/main/globals.hpp src/main/stdint.hpp
	$(CPP) -c src/main/engine/olevelobjs.cpp -o obj/olevelobjs.o $(CXXFLAGS)

obj/ologo.o: $(GLOBALDEPS) src/main/engine/ologo.cpp
	$(CPP) -c src/main/engine/ologo.cpp -o obj/ologo.o $(CXXFLAGS)

obj/omap.o: $(GLOBALDEPS) src/main/engine/omap.cpp
	$(CPP) -c src/main/engine/omap.cpp -o obj/omap.o $(CXXFLAGS)

obj/omusic.o: $(GLOBALDEPS) src/main/engine/omusic.cpp
	$(CPP) -c src/main/engine/omusic.cpp -o obj/omusic.o $(CXXFLAGS)

obj/ooutputs.o: $(GLOBALDEPS) src/main/engine/ooutputs.cpp
	$(CPP) -c src/main/engine/ooutputs.cpp -o obj/ooutputs.o $(CXXFLAGS)

obj/opalette.o: $(GLOBALDEPS) src/main/engine/opalette.cpp src/main/trackloader.hpp src/main/globals.hpp src/main/stdint.hpp
	$(CPP) -c src/main/engine/opalette.cpp -o obj/opalette.o $(CXXFLAGS)

obj/oroad.o: $(GLOBALDEPS) src/main/engine/oroad.cpp
	$(CPP) -c src/main/engine/oroad.cpp -o obj/oroad.o $(CXXFLAGS)

obj/osmoke.o: $(GLOBALDEPS) src/main/engine/osmoke.cpp
	$(CPP) -c src/main/engine/osmoke.cpp -o obj/osmoke.o $(CXXFLAGS)

obj/osprite.o: $(GLOBALDEPS) src/main/engine/osprite.cpp
	$(CPP) -c src/main/engine/osprite.cpp -o obj/osprite.o $(CXXFLAGS)

obj/osprites.o: $(GLOBALDEPS) src/main/engine/osprites.cpp src/main/trackloader.hpp src/main/globals.hpp src/main/stdint.hpp
	$(CPP) -c src/main/engine/osprites.cpp -o obj/osprites.o $(CXXFLAGS)

obj/ostats.o: $(GLOBALDEPS) src/main/engine/ostats.cpp
	$(CPP) -c src/main/engine/ostats.cpp -o obj/ostats.o $(CXXFLAGS)

obj/otiles.o: $(GLOBALDEPS) src/main/engine/otiles.cpp src/main/trackloader.hpp src/main/globals.hpp src/main/stdint.hpp
	$(CPP) -c src/main/engine/otiles.cpp -o obj/otiles.o $(CXXFLAGS)

obj/otraffic.o: $(GLOBALDEPS) src/main/engine/otraffic.cpp
	$(CPP) -c src/main/engine/otraffic.cpp -o obj/otraffic.o $(CXXFLAGS)

obj/outils.o: $(GLOBALDEPS) src/main/engine/outils.cpp
	$(CPP) -c src/main/engine/outils.cpp -o obj/outils.o $(CXXFLAGS)

obj/outrun.o: $(GLOBALDEPS) src/main/engine/outrun.cpp src/main/utils.hpp src/main/stdint.hpp
	$(CPP) -c src/main/engine/outrun.cpp -o obj/outrun.o $(CXXFLAGS)

obj/osound.o: $(GLOBALDEPS) src/main/engine/audio/osound.cpp
	$(CPP) -c src/main/engine/audio/osound.cpp -o obj/osound.o $(CXXFLAGS)

obj/osoundint.o: $(GLOBALDEPS) src/main/engine/audio/osoundint.cpp
	$(CPP) -c src/main/engine/audio/osoundint.cpp -o obj/osoundint.o $(CXXFLAGS)

obj/segapcm.o: $(GLOBALDEPS) src/main/hwaudio/segapcm.cpp
	$(CPP) -c src/main/hwaudio/segapcm.cpp -o obj/segapcm.o $(CXXFLAGS)

obj/soundchip.o: $(GLOBALDEPS) src/main/hwaudio/soundchip.cpp
	$(CPP) -c src/main/hwaudio/soundchip.cpp -o obj/soundchip.o $(CXXFLAGS)

obj/ym2151.o: $(GLOBALDEPS) src/main/hwaudio/ym2151.cpp
	$(CPP) -c src/main/hwaudio/ym2151.cpp -o obj/ym2151.o $(CXXFLAGS)

obj/hwroad.o: $(GLOBALDEPS) src/main/hwvideo/hwroad.cpp
	$(CPP) -c src/main/hwvideo/hwroad.cpp -o obj/hwroad.o $(CXXFLAGS)

obj/hwsprites.o: $(GLOBALDEPS) src/main/hwvideo/hwsprites.cpp
	$(CPP) -c src/main/hwvideo/hwsprites.cpp -o obj/hwsprites.o $(CXXFLAGS)

obj/hwtiles.o: $(GLOBALDEPS) src/main/hwvideo/hwtiles.cpp
	$(CPP) -c src/main/hwvideo/hwtiles.cpp -o obj/hwtiles.o $(CXXFLAGS)

obj/cabdiag.o: $(GLOBALDEPS) src/main/frontend/cabdiag.cpp src/main/frontend/cabdiag.hpp src/main/stdint.hpp src/main/video.hpp src/main/stdint.hpp src/main/globals.hpp src/main/stdint.hpp src/main/roms.hpp src/main/romloader.hpp src/main/hwvideo/hwtiles.hpp src/main/hwvideo/hwsprites.hpp src/main/hwvideo/hwroad.hpp src/main/cannonboard/interface.hpp src/main/engine/ooutputs.hpp src/main/engine/ohud.hpp src/main/engine/outrun.hpp src/main/engine/oaddresses.hpp src/main/engine/osprites.hpp src/main/engine/oentry.hpp src/main/engine/osprite.hpp src/main/engine/outrun.hpp src/main/engine/oroad.hpp src/main/engine/otiles.hpp src/main/engine/outrun.hpp
	$(CPP) -c src/main/frontend/cabdiag.cpp -o obj/cabdiag.o $(CXXFLAGS)

obj/config.o: $(GLOBALDEPS) src/main/frontend/config.cpp src/main/frontend/config.hpp src/main/utils.hpp src/main/stdint.hpp
	$(CPP) -c src/main/frontend/config.cpp -o obj/config.o $(CXXFLAGS)

obj/menu.o: $(GLOBALDEPS) src/main/frontend/menu.cpp src/main/frontend/menu.hpp src/main/utils.hpp src/main/stdint.hpp src/main/cannonboard/interface.hpp
	$(CPP) -c src/main/frontend/menu.cpp -o obj/menu.o $(CXXFLAGS)

obj/ttrial.o: $(GLOBALDEPS) src/main/frontend/ttrial.cpp
	$(CPP) -c src/main/frontend/ttrial.cpp -o obj/ttrial.o $(CXXFLAGS)

obj/asyncserial.o: $(GLOBALDEPS) src/main/cannonboard/asyncserial.cpp src/main/cannonboard/asyncserial.hpp
	$(CPP) -c src/main/cannonboard/asyncserial.cpp -o obj/asyncserial.o $(CXXFLAGS)

obj/interface.o: $(GLOBALDEPS) src/main/cannonboard/interface.cpp src/main/cannonboard/interface.hpp src/main/cannonboard/asyncserial.hpp
	$(CPP) -c src/main/cannonboard/interface.cpp -o obj/interface.o $(CXXFLAGS)

obj/ffeedback.o: $(GLOBALDEPS) src/main/directx/ffeedback.cpp src/main/directx/ffeedback.hpp
	$(CPP) -c src/main/directx/ffeedback.cpp -o obj/ffeedback.o $(CXXFLAGS)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
all	:	$(BINDIR)/$(OUTPUT).pfs0 $(BINDIR)/$(OUTPUT).nro

$(BINDIR)/$(OUTPUT).pfs0	:	$(BINDIR)/$(OUTPUT).nso

$(BINDIR)/$(OUTPUT).nso	:	$(BINDIR)/$(OUTPUT).elf

ifeq ($(strip $(NO_NACP)),)
$(BINDIR)/$(OUTPUT).nro	:	$(BINDIR)/$(OUTPUT).elf $(BINDIR)/$(OUTPUT).nacp
else
$(BINDIR)/$(OUTPUT).nro	:	$(BINDIR)/$(OUTPUT).elf
endif

$(BINDIR)/$(OUTPUT).elf	:	$(OFILES)

$(OFILES_SRC)	: $(HFILES_BIN)
	
# end of Makefile ...