#include "ArraySparseSet.h"
// #include <type_traits>

/**
 * @brief Construct a new A:: Array Sparse Set object
 * 
 * @param ref 
 */
template<typename T>
A::ArraySparseSet<T>::ArraySparseSet(const A::ArraySparseSet<T>* ref){
    this->elements = ref->elements;
}

/**
 * @brief 
 * 
 * @tparam T 
 * @return A::FlowSet<T>* 
 */
template<typename T>
A::FlowSet<T>* A::ArraySparseSet<T>::Clone(){
    return new A::ArraySparseSet<T>(this);
}

/**
 * @brief 
 * 
 * @tparam T 
 * @return A::FlowSet<T>* 
 */
template<typename T>
A::FlowSet<T>* A::ArraySparseSet<T>::EmptySet(){
    return new A::ArraySparseSet<T>();
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param dest 
 */
template<typename T>
void A::ArraySparseSet<T>::Copy(A::FlowSet<T>* dest){
    if(dest == this){
        return;
    }else{
        if(SameType(dest)){
            A::ArraySparseSet<T> *tmp = dynamic_cast<A::ArraySparseSet<T>*>(dest);
            tmp->elements = this->elements;
        }else
        {
            A::AbstractFlowSet<T>::Copy(dest);
        }        
    }
}

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
void A::ArraySparseSet<T>::Clear(){
    // if(is_pointer<T>::v){
    //     for (int i = 0; i < elements.size(); ++i){
    //         delete elements[i];
    //     }        
    // }
    this->elements.clear();
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 */
template<typename T>
void A::ArraySparseSet<T>::Union(A::FlowSet<T>* other){
    if(this == other){
        return;
    }else{
        if(SameType(other))
            Union(other,this);
        else
            A::AbstractFlowSet<T>::Union(other);
    }    
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 * @param dest 
 */
template<typename T>
void A::ArraySparseSet<T>::Union(A::FlowSet<T>* otherFlow, A::FlowSet<T>* destFlow){
    if(SameType(otherFlow) && SameType(destFlow)){
        A::ArraySparseSet<T>* other = dynamic_cast<A::ArraySparseSet<T>*>(otherFlow);
        A::ArraySparseSet<T>* dest = dynamic_cast<A::ArraySparseSet<T>*>(destFlow);
        
        if(this == other || Equals(other)){
            Copy(dest);
            return;
        }

        if(other != dest){
            dest->elements = elements;
            for (int i = 0; i < other->elements.size(); ++i){
                dest->Add(other->elements[i]);
            }        
        }else{
            for (int i = 0; i < elements.size(); ++i){
                dest->Add(elements[i]);
            }
        }
    }else{
        this->A::AbstractFlowSet<T>::Union(otherFlow,destFlow);
    }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 */
template<typename T>
void A::ArraySparseSet<T>::Intersection(A::FlowSet<T>* other){
    if(this == other){
        return;
    }else{
        if(SameType(other))
            Intersection(other,this);
        else
            A::AbstractFlowSet<T>::Intersection(other);
    }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 * @param dest 
 */
template<typename T>
void A::ArraySparseSet<T>::Intersection(A::FlowSet<T>* otherFlow, A::FlowSet<T>* destFlow){
    if(SameType(otherFlow) && SameType(destFlow)){
        A::ArraySparseSet<T>* other = dynamic_cast<A::ArraySparseSet<T>*>(otherFlow);
        A::ArraySparseSet<T>* dest = dynamic_cast<A::ArraySparseSet<T>*>(destFlow);
        
        if(this == other || Equals(other)){
            dest->Clear();
            return;
        }

        if(other != dest){
            dest->elements = elements;
            for (int i = 0; i < dest->elements.size(); ){
                if(!other->Contains(dest->elements[i])){
                    dest->Remove(i);
                }else{
                    ++i;
                }            
            }
        }else{
            for (int i = 0; i < dest->elements.size(); ){
                if(!Contains(dest->elements[i])){
                    dest->Remove(i);
                }else{
                    ++i;
                }            
            }
        }
        
    }else{
        A::AbstractFlowSet<T>::Intersection(otherFlow,destFlow);
    }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 */
template<typename T>
void A::ArraySparseSet<T>::Difference(A::FlowSet<T>* other){
    if(this == other){
        return;
    }else{
        if(SameType(other))
            Difference(other,this);
        else
            A::AbstractFlowSet<T>::Difference(other);
    }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 * @param dest 
 */
template<typename T>
void A::ArraySparseSet<T>::Difference(A::FlowSet<T>* otherFlow, A::FlowSet<T>* destFlow){
    if(SameType(otherFlow) && SameType(destFlow)){
        A::ArraySparseSet<T>* other = dynamic_cast<A::ArraySparseSet<T>*>(otherFlow);
        A::ArraySparseSet<T>* dest = dynamic_cast<A::ArraySparseSet<T>*>(destFlow);
        
        if(this == other || Equals(other)){
            dest->Clear();
            return;
        }

        if(other != dest){
            dest->elements = elements;
            for (int i = 0; i < dest->elements.size();){
                if(other->Contains(dest->elements[i])){
                    dest->Remove(i);
                }else{
                    ++i;
                }           
            }
        }else{
            A::ArraySparseSet<T> tmp;
            Copy(&tmp);
            // tmp.elements = dest->elements;
            for (int i = 0; i < dest->elements.size();){
                if(tmp.Contains(dest->elements[i])){
                    tmp.Remove(i);
                }else{
                    ++i;
                }           
            }
            tmp.Copy(dest);
        }
    }else{
        A::AbstractFlowSet<T>::Difference(otherFlow,destFlow);
    }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @return true 
 * @return false 
 */
template<typename T>
bool A::ArraySparseSet<T>::IsEmpty(){
    return elements.empty();
}

/**
 * @brief 
 * 
 * @tparam T 
 * @return int 
 */
template<typename T>
int A::ArraySparseSet<T>::Size(){
    return elements.size();
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param obj 
 */
template<typename T>
void A::ArraySparseSet<T>::Add(T obj){
    if(!Contains(obj)){
        elements.push_back(obj);
    }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param obj 
 */
template<typename T>
void A::ArraySparseSet<T>::Remove(T obj){
    for (int i = 0; i < elements.size(); ++i){
        if(elements[i] == obj){
            Remove(i);
            break;
        }
    }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param idx 
 */
template<typename T>
void A::ArraySparseSet<T>::Remove(int idx){
    if(idx < elements.size()-1)
        elements[idx] = elements[elements.size()-1];
    elements.pop_back();
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param obj 
 * @return true 
 * @return false 
 */
template<typename T>
bool A::ArraySparseSet<T>::Contains(T obj){
    for (int i = 0; i < elements.size(); ++i){
        if(*elements[i] == *obj)  return true;
    }
    return false;    
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 * @return true if contents are same
 * @return false 
 */
template<typename T>
bool A::ArraySparseSet<T>::Equals(A::FlowSet<T>* otherFlow){
    if(SameType(otherFlow)){
        A::ArraySparseSet<T> *flow = dynamic_cast<A::ArraySparseSet<T>*>(otherFlow);
        return elements == flow->elements;
    }else{
        return A::AbstractFlowSet<T>::Equals(otherFlow);
    }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 * @return true 
 * @return false 
 */
template<typename T>
bool A::ArraySparseSet<T>::IsSubSet(A::FlowSet<T>* otherFlow){
    if(SameType(otherFlow)){
        A::ArraySparseSet<T>* other = dynamic_cast<A::ArraySparseSet<T>*>(otherFlow);
        for(auto i : other->elements){
            if(!this->Contains(i)){
                return false;
            }
        }
        return true;
    }else{
        return A::AbstractFlowSet<T>::IsSubSet(otherFlow);
    }
    
}

/**
 * @brief 
 * 
 * @tparam T 
 * @return std::list<T> 
 */
template<typename T>
std::list<T> A::ArraySparseSet<T>::ToList(){
    std::list<T> objects;
    for (int i = 0; i < elements.size(); ++i){
        objects.push_back(elements[i]);
    }
    return objects;    
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param o 
 * @return true 
 * @return false 
 */
template<typename T>
bool A::ArraySparseSet<T>::SameType(A::FlowSet<T>* o){
    if(dynamic_cast<A::ArraySparseSet<T>*>(o) != nullptr)
        return true;
    return false;
}

// template<typename T>
// void A::ArraySparseSet<T>::Add(T obj, A::FlowSet<T>* dest){
//   auto tmp = this->Clone();
//   tmp->Add(obj);
//   tmp->Copy(dest);
// }

// template<typename T>
// void A::ArraySparseSet<T>::Remove(T obj, A::FlowSet<T>* dest){
//   auto tmp = this->Clone();
//   tmp->Remove(obj);
//   tmp->Copy(dest);
// }
template class A::ArraySparseSet<char*>;