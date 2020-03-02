/**
 * @file BoundedFlowSet.h
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _A_BOUNDED_FLOW_SET_H_
#define _A_BOUNDED_FLOW_SET_H_

#include "FlowSet.h"

namespace A{
    /**
     * @brief 
     *  An abstract class, basically an interface providing function declarations for the derived classes
     *  These functions are used when the latice used in the analysis is bounded latice.
     * @tparam T 
     *  Type of the dataflow value
     */
    template<typename T>
    class BoundedFlowSet{
	public:
        /// complements current object 
	    virtual void Complement() = 0;
        /// complements current object, puts result in dest
	    virtual void Complement(FlowSet<T>* dest) = 0;
        /// returns the Top element of the latice
	    virtual FlowSet<T>* TopSet() = 0;
        ~BoundedFlowSet(){}
    };
}
#endif