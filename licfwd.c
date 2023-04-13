#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
/*
#include <bpf/bpf_endian.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <linux/tcp.h>
*/

SEC("classifier")

int patch_server_port(struct __sk_buff *skb) {
	// Initialize variables for payload modification
	unsigned int offset = 10;  // Set the specific offset
	unsigned short known_port = 34127;
	unsigned short new_port = 5903;
	void *data = (void *)(long)skb->data;
	void *data_end = (void *)(long)skb->data_end;
	int payload_size = skb->data_end - skb->data;
/*
	__u32 eth_proto = load_byte(skb, offsetof(struct ethhdr, h_proto));
	if (eth_proto != bpf_htons(ETH_P_IP)) {
		return -1;
	}

	__u32 ip_proto = load_byte(skb, ETH_HLEN + offsetof(struct iphdr, protocol));
	if (ip_proto != IPPROTO_TCP) {
		return -1;
	}
*/
	// Check if the packet has enough data
	if (data + offset + 2 > data_end) {
		return -1;
	}
/*
	ihl = load_byte(skb, ETH_HLEN + offsetof(struct iphdr, ihl)) & 0xF;
	tcphdr_off = ETH_HLEN + ihl * 4;


	__u16 src_port = load_half(skb, tcphdr_off + offsetof(struct tcphdr, source));
	__u16 dst_port = load_half(skb, tcphdr_off + offsetof(struct tcphdr, dest));
*/
	char fmt[] = "Caught packet with length %d, payload length %d\n";
	bpf_trace_printk(fmt, sizeof(fmt), skb->len, payload_size);
	/*
	// Get the port number at the specific offset
	unsigned short *port = data + offset;
	if (*port == bpf_htons(known_port)) {
	// Replace the port number
	 *port = bpf_htons(new_port);
	 }
	 */
	return 0;
}

char _license[] SEC("license") = "GPL";
