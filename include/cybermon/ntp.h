
////////////////////////////////////////////////////////////////////////////
//
// NTP processing
//
////////////////////////////////////////////////////////////////////////////

#ifndef CYBERMON_NTP_H
#define CYBERMON_NTP_H

#include <stdint.h>

#include <set>

#include "context.h"
#include "manager.h"
#include "serial.h"
#include "protocol.h"
#include "ntp_protocol.h"

namespace cybermon {

    // A NTP context.
    class ntp_context : public context {
      public:
	
	// Constructor.
        ntp_context(manager& m) : context(m) {
	}

	// Constructor, describing flow address and parent pointer.
        ntp_context(manager& m, const flow_address& a, context_ptr p) : 
	context(m) { 
	    addr = a; parent = p; 
	}

	// Type is "ntp".
	virtual std::string get_type() { return "ntp"; }

	typedef boost::shared_ptr<ntp_context> ptr;

	static context_ptr create(manager& m, const flow_address& f, 
				  context_ptr par) {
	    context_ptr cp = context_ptr(new ntp_context(m, f, par));
	    return cp;
	}

	// Given a flow address, returns the child context.
	static ptr get_or_create(context_ptr base, const flow_address& f) {
	    context_ptr cp = context::get_or_create(base, f, 
						    ntp_context::create);
	    ptr sp = boost::dynamic_pointer_cast<ntp_context>(cp);
	    return sp;
	}

    };

    class ntp {

      public:
      
    // NTP ident function.
	static bool ident(uint16_t source_port, uint16_t destination_port);

	// NTP processing function.
	static void process(manager&, context_ptr c, pdu_iter s, pdu_iter e);

    };

};

#endif

