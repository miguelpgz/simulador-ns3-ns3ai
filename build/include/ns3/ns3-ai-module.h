#ifdef NS3_MODULE_COMPILATION 
    error "Do not include ns3 module aggregator headers from other modules these are meant only for end user scripts." 
#endif 
#ifndef NS3_MODULE_NS3_AI
    // Module headers: 
    #include <ns3/memory-pool.h>
    #include <ns3/train-var.h>
    #include <ns3/ns3-ai-rl.h>
    #include <ns3/ns3-ai-dl.h>
#endif 