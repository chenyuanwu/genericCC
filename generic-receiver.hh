#ifndef GENERICCC_GENERIC_RECEIVER_HH
#define GENERICCC_GENERIC_RECEIVER_HH

#include <cassert>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include "tcp-header.hh"
#include "udp-socket.hh"

#define BUFFSIZE 15000

using namespace std;

class Receiver {
private:
    UDPSocket sender_socket;
    chrono::high_resolution_clock::time_point start_time_point;
public:
    Receiver(int port) : sender_socket(), start_time_point(chrono::high_resolution_clock::now()) {
        sender_socket.bindsocket(port);
    }

    int recvfrom(char* databuf) {
        char buff[BUFFSIZE];
        sockaddr_in sender_addr;

        while (1) {
            int received __attribute((unused)) = -1;
            while (received == -1) {
                //socket_lock.lock();
                received = sender_socket.receivedata(buff, BUFFSIZE, -1, \
					sender_addr);
                //socket_lock.unlock();
                assert( received != -1 );
            }

            TCPHeader *header = (TCPHeader*)buff;
            header->receiver_timestamp = \
                chrono::duration_cast<chrono::duration<double>>(
                    chrono::high_resolution_clock::now() - start_time_point
                ).count()*1000; //in milliseconds

            //socket_lock.lock();
            sender_socket.senddata(buff, sizeof(TCPHeader), &sender_addr);
            //socket_lock.unlock();
            if (received - sizeof(TCPHeader) > 0) {
                memcpy(databuf, buff + sizeof(TCPHeader), received - sizeof(TCPHeader));
                return (received - sizeof(TCPHeader));
            }
        }
    }
};

#endif //GENERICCC_GENERIC_RECEIVER_HH
