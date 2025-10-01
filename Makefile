PLATFORM ?= linux_x86_64

CACHE = .cache
RELEASE = $(CACHE)/release
TARGET = why2


all: build


-include config/$(PLATFORM).mk


build: env $(RELEASE)/$(TARGET)


exec: build
	$(RELEASE)/$(TARGET)


.PHONY: env clean


env:
	mkdir -pv $(CACHE)
	mkdir -pv $(RELEASE)


clean:
	rm -rv $(CACHE)












