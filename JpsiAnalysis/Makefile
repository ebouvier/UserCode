CXXFLAGS = -g -Wall -std=c++0x -fPIC -Wno-deprecated -I. -I`root-config --incdir` -I../External/ -I../External/include/ #-std=c++0x dire à g++ d'utiliser le c++11 au moment de la compilation
LDDIR = -L../External/lib 
LDFLAGS = -g -I. $(LDDIR)
LIBS = -lLHAPDF
CXX = c++
DEPS =  $(patsubst %.cc, %.d, $(wildcard *.cc)) 

all: run

run: MyAna.o runMyAna.o HiggsTriggerEfficiencyProvider.o PUReweighter.o  
	${CXX} ${LDFLAGS} $(LIBS) -o runMyAna $^ `root-config --libs`

runMyAna.o: runMyAna.cc
	${CXX} -c ${CXXFLAGS} `root-config --cflags` runMyAna.cc

MyAna.o: MyAna.cc 
	${CXX} -c ${CXXFLAGS} `root-config --cflags` MyAna.cc

HiggsTriggerEfficiencyProvider.o: HiggsTriggerEfficiencyProvider.cc 
	${CXX} -c ${CXXFLAGS} `root-config --cflags` HiggsTriggerEfficiencyProvider.cc

PUReweighter.o: PUReweighter.cc 
	${CXX} -c ${CXXFLAGS} `root-config --cflags` PUReweighter.cc

clean:
	rm -f MyAna.o runMyAna.o HiggsTriggerEfficiencyProvider.o PUReweighter.o runMyAna core *.d


# Make the dependencies 
# If one of the .h included in the different .cc is modified, it will be automatically recompiled
%.d: %.cc
	@echo "Generating dependencies for $<"
	@set -e; $(CXX) -M $(CXXFLAGS) $< \
	| sed 's%\($*\)\.o[ :]*%\1.o $@ : %g' > $@; \
	[ -s $@ ] || rm -f $@

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif
