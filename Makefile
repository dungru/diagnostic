BIN_IMAGE = diag_engine
SO_IMAGE = diag_engine.so
SHELL := /bin/bash
TOPDIR = $(subst /Makefile,, $(abspath $(lastword $(MAKEFILE_LIST))))

#### REDIS ####
REDIS_VERSION = stable
REDIS_TAR = redis-$(REDIS_VERSION).tar.gz
REDIS_URL = https://download.redis.io/redis-stable.tar.gz 

###### C flags #####
CC = gcc
CFLAGS = -Wall -g
CFLAGS += -I./ \
          -I./redis/src/ \
          -I./redis/deps/hiredis

##### C Source #####
C_SOURCES = $(TOPDIR)/diag_engine.c
C_SOURCES += $(TOPDIR)/diag_regs.c

##### OBJECTS #####
OBJECTS += $(patsubst %.c, %.o, $(C_SOURCES))

# REDIS RULES

redis: redis-server redis-cli

redis-server:
	@echo "Downloading and building Redis $(REDIS_VERSION)"
	@mkdir -p redis
	@curl -sSL $(REDIS_URL) -o $(REDIS_TAR)
	@tar -xzf $(REDIS_TAR) -C redis --strip-components=1
	@cd redis && make
	@cp $(PWD)/redis/src/redis-server $(PWD)/redis-server

redis-cli: redis-server
	@cp $(PWD)/redis/src/redis-cli $(PWD)/redis-cli

# DIAG ENGINE RULE

all: $(SO_IMAGE) $(C_SOURCES)

deps := $(OBJECTS:%.o=%.o.d)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(SO_IMAGE): $(OBJECTS)
	$(CC) -fPIC -shared -o $@ $(CFLAGS) $(C_SOURCES)

# $(BIN_IMAGE): $(OBJECTS)
# 	$(CC) -Wall -g $(C_SOURCES) -o $@ $(CFLAGS)
.PHONY : clean
clean:
	rm -f $(BIN_IMAGE) $(SO_IMAGE)
	find . -name "*.o" -type f -delete
	find . -name "*.d" -type f -delete