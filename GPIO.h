#define SC_INCLUDE_DYNAMIC_PROCESSES
#define final_size 50
#include "systemc"
using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

SC_MODULE(GPIO)
{
    
    // attributes
        // socket bus
  tlm_utils::simple_target_socket<GPIO> socket;
        // registre
    uint GPIOA[final_size];
    uint GPIOB[final_size];
    uint GPIOC[final_size];
    uint GPIOD[final_size];


    // functions
  void RW_register(tlm::tlm_generic_payload& trans, sc_time& delay )
  {
    // Recuperation des données (R/W, Addr, Data)
    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64    adr = trans.get_address();
  unsigned char*   ptr = trans.get_data_ptr();
      
      
      
      // variable temporaire:
      char c_GPIO;
      sc_dt::uint64 offset;
      
      
     // Determination du GPIO en fonction de l'adresse
      if (adr> 0x1400)
          c_GPIO = 'd';
      else if (adr> 0x1200)
          c_GPIO = 'c';
      else if (adr> 0x1000)
          c_GPIO = 'b';
      else
          c_GPIO = 'a';
      
      offset = adr << 8;

      if ( cmd == tlm::TLM_READ_COMMAND){
        if (c_GPIO == 'a'){
                trans.set_data_ptr((unsigned char*)&GPIOA[offset]);}
      
        else if (c_GPIO == 'b'){
                trans.set_data_ptr((unsigned char*)&GPIOB[offset]);}
    
        else if (c_GPIO == 'c'){
                trans.set_data_ptr((unsigned char*)&GPIOC[offset]);}
      
        else {
                trans.set_data_ptr((unsigned char*)&GPIOD[offset]);}
    
      }
      
    else if ( cmd == tlm::TLM_WRITE_COMMAND)
    {
        if (c_GPIO == 'a'){
                GPIOA[offset]= *ptr;}
        else if (c_GPIO == 'b'){
                GPIOB[offset]= *ptr;}
        
        else if (c_GPIO == 'c'){
                GPIOC[offset]= *ptr;}
        
        else{
                GPIOD[offset]= *ptr;}
        
    }
    
  }

  SC_CTOR(GPIO) : socket("socket")
  {
       socket.register_b_transport(this, &GPIO::RW_register);

  }
};

int sc_main(int argc, char* argv[])
{
    
    GPIO GPIO1("GPIO register");
    
    sc_start();  // run forever
    
    return 0;
    
}

