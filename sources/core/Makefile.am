SUBSRC  =
SUBSRC += TArtemisObject.cc
SUBSRC += TDataObject.cc
SUBSRC += TCatParameterTable.cc
SUBSRC += TRunInfo.cc
SUBSRC += TCatHistManager.cc
SUBSRC += TCatPadManager.cc
SUBSRC += TConfigFile.cc
SUBSRC += TSharedMemory.cc
SUBSRC += TSemaphoreObject.cc
SUBSRC += TArtCanvas.cc
SUBSRC += TArtemisUtil.cc
SUBSRC += TAnalysisInfo.cc
SUBSRC += TMacroReplacer.cc

SUBOBJ = $(SUBSRC:.cc=.o)
SUBHDR = $(SUBSRC:.cc=.h)
# TCatTypes.h


DICTSRC = catcore_dict.cc
DICTOBJ = $(DICTSRC:.cc=.o)
DICTHDR = $(DICTSRC:.cc=.h)

OPTHDR = 
INCDIR = ../../include

AUTOMAKE_OPTIONS = foreign

MYINCLUDES = -I$(INCDIR) -I$(ROOTSYS)/include 
CXXFLAGS = -fPIC  -I$(INCDIR) $(shell root-config --cflags) -Wall -O2 -g
#CXXFLAGS += -pg
LDFLAGS = $(shell root-config --glibs)

CXXFLAGS += @YAML_CPP_INCLUDE@
LDFLAGS  += @YAML_CPP_LIB@

include_HEADERS = $(SUBHDR) $(SUBHDRF) $(OPTHDR)

lib_LTLIBRARIES = libcatcore.la
libcatcore_la_SOURCES = $(SUBSRC) $(DICTSRC)
libcatcore_la_DEPENDENCIES = .header
# libcatcore_la_LIBADD = $(SUBOBJ)
libcatcore_la_LDFLAGS = $(LDFLAGS)

$(DICTSRC): $(SUBHDR) catcore_linkdef.h
	@echo Making $(DICTSRC) ...
	rootcint -f $@ -c -p $(DEFAULT_INCLUDES) $(MYINCLUDES) $^

.header: $(include_HEADERS)
	@echo Installing header to $(INCDIR)
	@mkdir -p $(INCDIR)
	@cp -a $(include_HEADERS) $(INCDIR)
	@touch .header


.cc.o:

.f.o:

.c.o:

clean-local:
	rm -f *dict*

clean: clean-local
	rm -rf $(SUBOBJ) .libs *.lo .header
