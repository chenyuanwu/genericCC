#ifndef GENERICCC_TCP_HEADER_HH
#define GENERICCC_TCP_HEADER_HH
struct TCPHeader{
	int seq_num;
	int flow_id;
	int src_id;
	double sender_timestamp;
	double receiver_timestamp;
};

#endif //GENERICCC_TCP_HEADER_HH