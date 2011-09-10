CPP_FILES := $(wildcard src/*.cpp)
C_FILES := $(wildcard src/ga/*.C)
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,$(CPP_FILES)) $(patsubst src/ga/%.C,obj/%.o,$(C_FILES))
LD_FLAGS := -lopengl32 -lmingw32 -lsdlmain -lsdl.dll
CC_FLAGS := -O2

all: objs
	g++ $(CC_FLAGS) $(OBJ_FILES) $(LD_FLAGS) -o tsp.exe

benchmark: benchobj
	g++ $(CC_FLAGS) $(OBJ_FILES) $(LD_FLAGS) -o tsp_benchmark.exe
	
objs: 
	g++ -c $(CC_FLAGS) $(CPP_FILES) $(C_FILES) 
	rm -rf obj
	mkdir obj
	mv *.o obj
	
benchobj: 
	g++ -DBENCHMARK -c $(CC_FLAGS) $(CPP_FILES) $(C_FILES) 
	rm -rf obj
	mkdir obj
	mv *.o obj
	
clean:
	rm -rf obj