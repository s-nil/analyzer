/**
 * @file BoundedFlowSet.h
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-01-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _A_BOUNDED_FLOW_SET_H_
#define _A_BOUNDED_FLOW_SET_H_

#include "FlowSet.h"

namespace A
{
    /**
     * @brief 
     * 
     * @tparam T 
     */
    template<typename T>
    class BoundedFlowSet : public FlowSet<T>
    {
	public:
	    virtual void Complement() = 0;
	    virtual void Complement(FlowSet<T>* dest) = 0;
	    virtual FlowSet<T>* TopSet() = 0;
        ~BoundedFlowSet(){}
    };
}
#endif