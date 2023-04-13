CC = clang
LLC = llc-10
TC = tc

TARGET = licfwd
CFLAGS = -O2 -target bpf -emit-llvm -I/usr/include/x86_64-linux-gnu
LDFLAGS = -march=bpf -filetype=obj

all: $(TARGET).o

$(TARGET).bc: $(TARGET).c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).o: $(TARGET).bc
	$(LLC) $(LDFLAGS) -o $@ $<

load: $(TARGET).o
	$(TC) qdisc add dev eth0 clsact
	$(TC) filter add dev eth0 ingress bpf da obj $(TARGET).o sec classifier

unload:
	$(TC) qdisc del dev eth0 clsact

clean:
	rm -f $(TARGET).o $(TARGET).bc

.PHONY: all load unload clean
