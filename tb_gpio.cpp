#define SC_INCLUDE_DYNAMIC_PROCESSES
#define final_size 50
#include "systemc"
using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

SC_MODULE(Initiator)
{
  //attributs
  tlm_utils::simple_initiator_socket<Initiator> socket;

SC_CTOR(Initiator) : socket("socket")
{
  SC_THREAD(thread_process);
}

void thread_process()
{
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(10, SC_NS);

  for (int i = 32; i < 96; i += 4)
  {
    trans->set_command( cmd );
    trans->set_address( i );
    trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
    trans->set_data_length( 4 );
    trans->set_streaming_width( 4 );
    trans->set_byte_enable_ptr( 0 );
    trans->set_dmi_allowed( false );
    trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

    socket->b_transport( *trans, delay );

  }
}
