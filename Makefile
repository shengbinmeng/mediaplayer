#
# source files
#
SRCS := audio_decoder.cpp video_decoder.cpp decoder.cpp framequeue.cpp \
		packetqueue.cpp thread.cpp mediaplayer.cpp mp_listener.cpp play.cpp

OBJS := $(SRCS:%.cpp=%.o)

play : $(OBJS)
	g++ -g -O0 -I/usr/local/include/ -L/usr/local/lib/ -lavcodec -lavformat -lswresample -lavutil -o $@ $^

.PHONY: clean
clean:
	rm -f play *.o