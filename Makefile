#
# Configure
#

FFMPEG_INCLUDE_DIR := /usr/local/Cellar/ffmpeg/3.1.3/include
FFMPEG_LIB_DIR := /usr/local/Cellar/ffmpeg/3.1.3/lib

#
# Source files
#
SRCS := audio_decoder.cpp video_decoder.cpp decoder.cpp framequeue.cpp \
		packetqueue.cpp thread.cpp mediaplayer.cpp mp_listener.cpp main.cpp

play : $(SRCS)
	g++ -g -O2 -I${FFMPEG_INCLUDE_DIR} -L${FFMPEG_LIB_DIR} -lavcodec -lavformat -lswresample -lavutil -o $@ $^

.PHONY: clean
clean:
	rm -f play *.o