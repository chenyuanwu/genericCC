#ifndef GENERICCC_COPA_SENDER_H
#define GENERICCC_COPA_SENDER_H

#include <string.h>
#include <iostream>
#include <boost/random/uniform_int_distribution.hpp>
#include "random.hh"
#include "remycc.hh"
#include "ctcp.hh"
#include "markoviancc.hh"


using namespace std;

MarkovianCC parse_copa_config(string delta_conf) {
    MarkovianCC congctrl(1.0);
    congctrl.interpret_config_str(delta_conf);
    return congctrl;
}

class COPASender {
private:
    CTCP< MarkovianCC > connection;
    int src_id;
public:
    COPASender(string delta_config, string serverip, int serverport, int sourceport)
      : connection(parse_copa_config(delta_config), serverip, serverport, sourceport, 1), src_id()
    {
        connection.congctrl_init();

        PRNG prng(global_PRNG());
        src_id = boost::random::uniform_int_distribution<>()(prng);
        cout<<"Assigning Source ID: "<<src_id<<endl;
    }

    void send(const char* data, int size, int flow_id) {
        connection.send_data(data, size, flow_id, src_id);
    }
};



#endif //GENERICCC_COPA_SENDER_H
