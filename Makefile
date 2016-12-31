#
# Configure
#

FFMPEG_INCLUDE_DIR := /usr/local/include
FFMPEG_LIB_DIR := /usr/local/lib

#
# Source files
#
SRCS := AudioDecoder.cpp VideoDecoder.cpp Decoder.cpp Queue.cpp FrameQueue.cpp \
		PacketQueue.cpp Thread.cpp MediaPlayer.cpp mp_listener.cpp main.cpp

play: $(SRCS)
	g++ -g -O2 -I${FFMPEG_INCLUDE_DIR} -L${FFMPEG_LIB_DIR} -o $@ $^ -lavformat -lavcodec -lswresample -lavutil -pthread

.PHONY: clean
clean:
	rm -f play *.o
