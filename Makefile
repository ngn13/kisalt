CROW_URL  = https://github.com/CrowCpp/Crow/releases/download/v1.1.0/crow_all.h
CROW_HASH = 9e710a3fa5170b736c500ad283d8ed5d178ee88cd530224efd02a348dd655ffb

SRCS = $(wildcard src/*.cpp) $(wildcard src/*.h)
CC   = g++

all: src/crow_all.h kisalt

kisalt: $(SRCS)
	$(CC) -o $@ $^ -lcrypto -ljsoncpp 

src/crow_all.h: 
	wget -q --show-progress $(CROW_URL) -O src/crow_all.h
	echo "$(CROW_HASH) $@" | sha256sum -c

