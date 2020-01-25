/**
 * @file AbstractBoundedFlowSet.h
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-01-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _A_ABSTRACT_BOUNDED_FLOW_SET_H_
#define _A_ABSTRACT_BOUNDED_FLOW_SET_H_
#include "BoundedFlowSet.h"

namespace A
{
    /**
     * @brief 
     * 
     * @tparam T 
     */
    template<class T>
    class AbstractBoundedFlowSet : public BoundedFlowSet<T>
    {
    public:
        AbstractBoundedFlowSet(){}

        void Complement();
	    void Complement(FlowSet<T>* dest);
	    FlowSet<T>* TopSet();
    };
}

#endif