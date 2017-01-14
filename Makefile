#
# Configure
#

FFMPEG_INCLUDE_DIR := /usr/local/include
FFMPEG_LIB_DIR := /usr/local/lib

#
# Source files
#

CORE_SRCS := AudioDecoder.cpp VideoDecoder.cpp Decoder.cpp Queue.cpp FrameQueue.cpp \
		PacketQueue.cpp MediaPlayer.cpp PlayerListener.cpp
		
DEMO_SRCS := main.cpp

#
# Targets
#

play: $(CORE_SRCS) $(DEMO_SRCS)
	g++ -g -O2 -I${FFMPEG_INCLUDE_DIR} -L${FFMPEG_LIB_DIR} -o $@ $^ -lavformat -lavcodec -lswresample -lavutil -pthread

.PHONY: clean
clean:
	rm -f play *.o
