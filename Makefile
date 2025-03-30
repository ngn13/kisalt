CROW_URL     = https://github.com/CrowCpp/Crow/releases/download/v1.2.1.2/Crow-1.2.1-Linux.tar.gz
CROW_HASH    = 242d72a809f48bb3169c1361798e81e3f553117cced107d4a309748672cebf23
CROW_ARCHIVE = $(shell echo "$(CROW_URL)" | cut -d/ -f 9)
CROW_DIR     = $(shell echo "$(CROW_ARCHIVE)" | sed 's/.tar.gz//g')

SRCS = $(wildcard src/*.cpp)
HDRS = $(wildcard inc/*.hpp)
CXX  = g++

CXXFLAGS  = -O3 # optimization
CXXFLAGS += -fstack-protector-strong -fcf-protection=full -fstack-clash-protection # memory protections
INCLUDE   = -I./inc
LIBS      = -lcrypto -ljsoncpp

all: inc/crow.h kisalt

kisalt: $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $(SRCS) $(LIBS)

inc/crow.h:
	wget -q --show-progress $(CROW_URL) -O "$(CROW_ARCHIVE)"
	echo "$(CROW_HASH) $(CROW_ARCHIVE)" | sha256sum -c
	tar -xf "$(CROW_ARCHIVE)" "$(CROW_DIR)/include"
	mv "$(CROW_DIR)/include/"* inc
	rm -r "$(CROW_ARCHIVE)" "$(CROW_DIR)"

format:
	clang-format -i -style=file $(SRCS)
	clang-format -i -style=file $(HDRS)

clean:
	rm -fr inc/crow.h inc/crow
	rm -f kisalt

.PHONY: format
