CXX = clang++
LD = ../../tools/bin/x86_64-elf-ld
OBJCOPY = ../../tools/bin/x86_64-w64-mingw32-objcopy
CXXFLAGS += -Os -Wall -std=c++1z -stdlib=libc++ -MD -fPIC -Wno-unused-parameter -g -Wno-unused-variable \
	-Wall -Wextra -Wpedantic -Werror -Weffc++ -Wno-unused-variable -Wno-unused-parameter -Wno-tautological-overlap-compare \
	-DHAVE_USE_MS_ABI \
	-ffreestanding -fno-exceptions -fno-rtti -fshort-wchar -nostdlib \
	-mno-sse -mno-sse2 -mno-sse3 -mno-sse4 -mno-avx -mno-red-zone
LDFLAGS += -nostdlib -Bsymbolic
TARGETFLAGS += -target x86_64-linux-elf

CRT0 = crt0.o
LDS = loader.lds
LIBRARIES =

SOURCES := $(shell find . -name "*.cpp" ! -wholename "./tests/*")
TESTSRC := $(shell find ./tests/ -name "*.cpp")
OBJECTS := $(SOURCES:.cpp=.o)
TESTOBJ := $(TESTSRC:.cpp=.o)

EXECUTABLE = BOOTX64.EFI
INTERMEDIATE = BOOTX64.ELF
#EXECUTABLE = rose-loader.efi

all: $(EXECUTABLE)

$(INTERMEDIATE): $(OBJECTS) $(CRT0)
	$(LD) $(LDFLAGS) -T $(LDS) $(CRT0) $(OBJECTS) -o $@ $(LIBRARIES)

$(EXECUTABLE): $(INTERMEDIATE)
	$(OBJCOPY) -j .text -j .sdata -j .data -j .dynamic -j .dynsym -j .rel -j .rela -j .reloc \
		--target=efi-app-x86_64 \
		$(INTERMEDIATE) $@

test: ./tests/test

./tests/test: $(TESTOBJ) $(LIBRARY)
	$(LD) $(CXXFLAGS) $(LDFLAGS) $(TESTOBJ) -o $@ $(LIBRARIES) -lboost_system -lboost_iostreams -lboost_program_options -ldl -pthread -L. -ldespayre

#install: $(LIBRARY) $(EXECUTABLE)
#	echo "TODO"
#	exit 1

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(TARGETFLAGS)

$(CRT0): crt0.asm
	yasm crt0.asm -f elf64 -o $(CRT0)

./tests/%.o: ./tests/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	@find . -name "*.o" -delete
	@find . -name "*.d" -delete
	@rm -f $(EXECUTABLE)
	@rm -f tests/test
	@rm -f $(CRT0)

.PHONY: clean test

-include $(SOURCES:.cpp=.d)
-include $(TESTSRC:.cpp=.d)

