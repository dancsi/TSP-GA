CPP_FILES := $(wildcard src/*.cpp)
C_FILES := $(wildcard src/ga/*.C)
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,$(CPP_FILES)) $(patsubst src/ga/%.C,obj/%.o,$(C_FILES))
LD_FLAGS := -lmingw32 -lsdlmain -lsdl.dll -lopengl32
CC_FLAGS := -O2

tsp.exe: obj
	g++ $(CC_FLAGS) $(OBJ_FILES) $(LD_FLAGS) -o $@

obj: 
	g++ -c $(CC_FLAGS) $(CPP_FILES) $(C_FILES) 
	rm -rf obj
	mkdir obj
	mv *.o obj
clean:
	rm -rf obj
	