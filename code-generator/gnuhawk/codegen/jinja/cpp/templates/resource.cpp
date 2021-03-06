/*#
 * This file is protected by Copyright. Please refer to the COPYRIGHT file
 * distributed with this source distribution.
 * 
 * This file is part of GNUHAWK.
 * 
 * GNUHAWK is free software: you can redistribute it and/or modify is under the 
 * terms of the GNU General Public License as published by the Free Software 
 * Foundation, either version 3 of the License, or (at your option) any later 
 * version.
 * 
 * GNUHAWK is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more 
 * details.
 * 
 * You should have received a copy of the GNU General Public License along with 
 * this program.  If not, see http://www.gnu.org/licenses/.
 #*/
//% set className = component.userclass.name
//% set hasMultiOut = component.hasmultioutport 

${component.cppLicense}

#include "${component.userclass.header}"

//
//   This file contains the bindings to the hosted block
//

//
//    For GNU Radio blocks with getter and setter methods, the associated property can be bound
//    directly to the block's getter and/or setter.
//
//    void component_class_i::createBlock()
//    {
//        ...
//        this->registerGetter("property_x", &gnuradio_class::getter_for_x);
//        this->registerSetter("property_y", &gnuradio_class::setter_for_y);
//        this->registerGetterSetter("property_z", &gnuradio_class::getter_for_z,
//                                   &gnuradio_class::setter_for_z);
//        ...
//    }

//
//    To bind to a setter via the REDHAWK component class
//
//    void component_class_i::setterForPropertyX()
//    {
//       if ( validGRBlock() ) {
//           gr_sptr->set_property_x(this->property_x);
//        }
//    }
//
//    void component_class_i::createBlock()
//    {
//        ...
//        this->setPropertyChangeListener("property_x", this, &component_class_i::setterForPropertyX);
//        ...
//    }

//
//    To bind to a getter via the REDHAWK component class
//
//    double component_class_i::getterForPropertyX()
//    {
//       if ( validGRBlock() ) {
//         return this->gr_sptr->get_property_x();
//       }
//       return 0.0;
//    }
//    void component_class_i::createBlock()
//    {
//        ...
//        this->registerGetValue("property_x", this, &component_class_i::getterForPropertyX);
//        ...
//    }

/*#   These were include as comments in the orig jet based codegens
//
//    To redirect incoming messages to the handler
//    This assumes that an input (provides) port exists of type ExtendedEvent/MessageEvent
//    with the name simple_in. The name can be anything - it just needs to match the argument
//
//    void component_class_i::createBlock()
//    {
//        ...
//        gr_sptr->setInboundMessageDispatch(this->simple_in);
//        ...
//    }

//
//    To redirect outgoing messages to out a particular output message
//    This assumes that an output (uses) port exists of type ExtendedEvent/MessageEvent
//    with the name simple_out. The name can be anything - it just needs to match the argument
//
//    void component_class_i::createBlock()
//    {
//        ...
//        simple_sptr = gr_basic_block_sptr(new gr_basic_block());
//        simple_sptr->setMessageDispatch(this->simple_out);
//        gr_sptr->set_simple_ref(simple_sptr);
//        ...
//    }
//
//    private:
//        gr_basic_block_sptr simple_sptr;
//
#*/

${className}::${className}(const char *uuid, const char *label) :
${component.baseclass.name}(uuid, label)
{
/*{% if hasMultiOut %}*/
    setPropertyChangeListener("stream_id_map", this, &${className}::streamIDChanged);
/*{% endif %}*/
}

/*{% if hasMultiOut %}*/
void ${className}::streamIdChanged(const std::string& id) {
}
/*{% for port in component.port if port is uses %}*/
   RH_ProvidesPortMap::iterator in_port;
   in_port = inPorts.find("port.cppname");
   bulkio::InFloatPort *port = dynamic_cast<   bulkio::InFloatPort * >(in_port->second);
   BULKIO::StreamSRISequence_var sris = port->activeSRIs();
   if (sris->length() > 0 ) {
     BULKIO::StreamSRI sri = sris[sris->length()-1];
     setOutputStreamSRI(sri);
   }
/*{% endfor %}*/
}
/*{% endif %}*/

${className}::~${className}()
{
}


// createBlock
//
// Create the actual GNU Radio Block to that will perform the work method. The resulting
// block object is assigned to gr_stpr
//
// Add property change callbacks for getter/setter methods
//

void ${className}::createBlock()
{
    //
    // gr_sptr = xxx_make_xxx( args );
    //

#error Insert the assignment/constructor of the GNRadio Block pointer here, then delete this error preprocessor directive. It should be of the form "gr_sptr = xxx_make_xxx(args)"

    // 
    // Use setThrottle method to enable the throttling of consumption/production of data by the
    // service function. The affect of the throttle will try to pause the execution of the 
    // service function for a specified duration.  This duration is calculated using the getTargetDuration() method
    // and the actual processing time to perform the work method.
    //
    // This is turned ON by default for "output" only components
    //
    // setThrottle( bool onoff );

    // 
    // Use maintainTimeStamp to enable proper data flow of timestamp with input and output data. 
    // if turned on (true)
    //  The timestamp from the input source will be used and maintained based on the output rate and
    //  the number of samples produced
    // if turned off
    //   then the timestamp from the input source is passed through if available or the time of day
    // 
    // maintainTimestamp( bool onoff );

/*{% if component.hasbulkio %}*/
    setupIOMappings();
/*{% endif %}*/
}

/*{% if component.hasbulkiouses %}*/
//
// createOutputSRI
//
// For each output mapping defined, a call to createOutputSRI will be issued with the associated output index.
// This default SRI and StreamID will be saved to the mapping and pushed down stream via pushSRI.
//
// @param oidx : output stream index number to associate the returned SRI object with
// @param in_idx : input stream index number to associate the returned SRI object with
// @param ext : extension to append to incoming StreamID
// @return sri : default SRI object passed down stream over a RedHawk port
//      
BULKIO::StreamSRI ${className}::createOutputSRI( int32_t oidx, int32_t &in_idx, std::string &ext)
{
    //
    // oidx is the stream number that you are returning an SRI context for
    //
    in_idx = 0;
    BULKIO::StreamSRI sri = BULKIO::StreamSRI();
    sri.hversion = 1;
    sri.xstart = 0.0;
    sri.xdelta = 1;
    sri.xunits = BULKIO::UNITS_TIME;
    sri.subsize = 0;
    sri.ystart = 0.0;
    sri.ydelta = 0.0;
    sri.yunits = BULKIO::UNITS_NONE;
    sri.mode = 0;
    std::ostringstream t;
    t << naming_service_name.c_str() << "_" << oidx;
    std::string sid = t.str();
    sri.streamID = CORBA::string_dup(sid.c_str());
    std::ostringstream t1;
    t1 << "_" << oidx;
    ext = t1.str();

    // NOTE: For non 1 to 1 port mappings, user needs to specify in_idx

    return sri;
}
/*{% endif %}*/
