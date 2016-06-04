EXENAME = mp1

OBJS = main_2.o rgbapixel.o png.o 

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -w
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main_2.cpp png.h
	$(CXX) $(CXXFLAGS) main_2.cpp
	
png.o : png.cpp png.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

clean : 
	-rm -f *.o $(EXENAME) out.png

