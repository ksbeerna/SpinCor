# Root configuration
ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

# set the compiler options
CXX           = g++                     #use g++ as compiler
CXXFLAGS      = -g -O -Wall -fPIC       #set compiler options
                                        #-g compile with debug information
                                        #-O optimize
                                        #-Wall show warnings for everything
                                        #-fPIC compile source file as sharable object

# set the linker options
LD            = g++                     #use g++ for linking
LDFLAGS       = -O                      #-O optimize

CXXFLAGS      += $(ROOTCFLAGS)
CXX_FLAGS     += -O0 -g3 -fno-inline

DCACHELIBS = -lDCache -ldcap
ADDITIONALLIBS = -lFoam -lRooFitCore -lRooFit -lHtml -lGenVector -lboost_regex -lTMVA -lMinuit -lXMLIO -lMLP -lTreePlayer #-lCLHEP 

LIBS          = $(ROOTLIBS) $(SYSLIBS) $(ADDITIONALLIBS)

PROJECT = SpinCor
OBJ = $(PROJECT).o ConfigReader.o Collector.o PEBuilder.o

# compile all programs
all: $(PROJECT)

$(PROJECT): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) $(LIBS) -o $(PROJECT)

%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c $<

%.o: ConfigReader/%.cc ConfigReader/%.h
	$(CXX) $(CXXFLAGS) -c $<

#%.o: TreeProducer.cc TreeProducer.h
#	$(CXX) $(CXXFLAGS) -c $<

PHONY : clean

clean:
	@rm -rf *.o *~
