CXX = g++
CXXFLAGS = -Wall -g
final: osfinal.o delete.o copy.o snapshot.o search.o
	$(CXX) $(CXXFLAGS) osfinal.o delete.o copy.o snapshot.o search.o -o final 
osfinal.o: osfinal.cpp
	$(CXX) $(CXXFLAGS) -c osfinal.cpp 
delete.o: delete.cpp
	$(CXX) $(CXXFLAGS) -c delete.cpp
copy.o: copy.cpp
	$(CXX) $(CXXFLAGS) -c copy.cpp
snapshot.o: snapshot.cpp
	$(CXX) $(CXXFLAGS) -c snapshot.cpp
search.o: search.cpp
	$(CXX) $(CXXFLAGS) -c search.cpp