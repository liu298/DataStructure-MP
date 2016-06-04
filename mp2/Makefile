EXENAME = testimage testscene

OBJS = testimage.o rgbapixel.o png.o image.o scene.o testscene.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -w
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : testimage testscene

#$(EXENAME) : $(OBJS)
#	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

testscene: testscene.o rgbapixel.o png.o image.o scene.o
	$(LD) testscene.o rgbapixel.o png.o image.o scene.o $(LDFLAGS) -o testscene

testimage: testimage.o rgbapixel.o png.o image.o
	$(LD)  testimage.o rgbapixel.o png.o image.o  $(LDFLAGS) -o testimage

testimage.o : testimage.cpp image.h
	$(CXX) $(CXXFLAGS) testimage.cpp

testscene.o : testscene.cpp image.h scene.h
	$(CXX) $(CXXFLAGS) testscene.cpp

image.o : image.cpp image.h
	$(CXX) $(CXXFLAGS) image.cpp

scene.o : scene.cpp scene.h image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) scene.cpp

png.o : png.cpp png.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

clean :
	-rm -f *.o $(EXENAME)
