#ifndef GENERICCC_REMY_SENDER_HH
#define GENERICCC_REMY_SENDER_HH
#include <chrono>
#include <fcntl.h>

#include <string.h>
#include <iostream>
#include <boost/random/uniform_int_distribution.hpp>
#include "random.hh"
#include "remycc.hh"
#include "ctcp.hh"


//RemyCC parse_remy_config(string filename) {
//    WhiskerTree whiskers;
//    int fd = open( filename.c_str(), O_RDONLY );
//    if ( fd < 0 ) {
//        fprintf( stderr, "Error in open %s.\n", filename.c_str() );
//        perror( "open" );
//        exit( 1 );
//    }
//
//    RemyBuffers::WhiskerTree tree;
//    if ( !tree.ParseFromFileDescriptor( fd ) ) {
//        fprintf( stderr, "Could not parse %s.\n", filename.c_str() );
//        exit( 1 );
//    }
//
//    whiskers = WhiskerTree( tree );
//
//    if ( close( fd ) < 0 ) {
//        fprintf( stderr, "Error in close %s.\n", filename.c_str() );
//        perror( "close" );
//        exit( 1 );
//    }
//    RemyCC congctrl( whiskers );
//    return congctrl;
//}

class REMYSender {
private:
    WhiskerTree whiskers;
    CTCP< RemyCC > connection;
    int src_id;
public:
    REMYSender(string serverip, int serverport, int sourceport)
            : whiskers(), connection(whiskers, serverip, serverport, sourceport, 1), src_id()
    {
        std::string filename = "RemyCC-2014-100x.dna";
        int fd = open( filename.c_str(), O_RDONLY );
        if ( fd < 0 ) {
            perror( "open" );
            exit( 1 );
        }

        RemyBuffers::WhiskerTree tree;
        if ( !tree.ParseFromFileDescriptor( fd ) ) {
            fprintf( stderr, "Could not parse %s.\n", filename.c_str() );
            exit( 1 );
        }

        whiskers = WhiskerTree( tree );

        if ( close( fd ) < 0 ) {
            perror( "close" );
            exit( 1 );
        }

        RemyCC remycc( whiskers );
        connection.congctrl = remycc;
        connection.congctrl_init();

        PRNG prng(global_PRNG());
        src_id = boost::random::uniform_int_distribution<>()(prng);
        cout<<"Assigning Source ID: "<<src_id<<endl;
    }

    void send(const char* data, int size, int flow_id) {
        connection.send_data(data, size, flow_id, src_id);
    }
};

#endif //GENERICCC_REMY_SENDER_HH
