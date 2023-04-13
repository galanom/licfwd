CC = clang
LLC = llc
TC = tc

IFACE = wlan0
TARGET = licfwd
CFLAGS = -O2 -target bpf -emit-llvm -I/usr/include/x86_64-linux-gnu
LDFLAGS = -march=bpf -filetype=obj

all: $(TARGET).o

$(TARGET).bc: $(TARGET).c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).o: $(TARGET).bc
	$(LLC) $(LDFLAGS) -o $@ $<

load: $(TARGET).o
	sudo $(TC) qdisc add dev $(IFACE) clsact
	sudo $(TC) filter add dev $(IFACE) ingress bpf da obj $(TARGET).o sec classifier

unload:
	sudo $(TC) qdisc del dev $(IFACE) clsact

clean:
	rm -f $(TARGET).o $(TARGET).bc

.PHONY: all load unload clean
