GXX = g++
TARGET = cv_output
LIBS = `pkg-config --libs opencv`
HEDS = `pkg-config --cflags opencv`
OBJS := $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)	
	$(GXX) -o $@ $< $(LIBS)
	@echo -e '\e[1;32mOutput file : \e[m'$(TARGET)

.cpp.o:
	@echo -e '\e[1;32mSource file : \e[m'$(SRCS)
	$(GXX) -c $< $(HEDS)

clean:
	@echo -e '\e[1;32mClean \e[m'
	rm -f $(TARGET) *.o
	rm -f $(TARGET) *.cpp~
