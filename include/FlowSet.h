#ifndef _A_FLOW_SET_H_
#define _A_FLOW_SET_H_

#include "IterableList.h"

namespace A{

template<typename T>
class FlowSet : public IterableList<T>
{
public:
    FlowSet(){

    }

    T display();

private:

};

}   // end namespace

#endif  //  end _A_FLOW_SET_H_