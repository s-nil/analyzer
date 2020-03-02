/**
 * @file AbstractFlowSet.cpp
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "AbstractFlowSet.h"
#include "ArrayPackedSet.h"
#include "ArraySparseSet.h"

/**
 * @brief
 * @tparam T 
 * @return A::FlowSet<T>* 
 */
template<typename T>
A::FlowSet<T>* A::AbstractFlowSet<T>::Clone(){
  /// According to the type of the current object, calls the corresponding Clone()
  if(dynamic_cast<A::ArrayPackedSet<T>*>(this)){
    dynamic_cast<A::ArrayPackedSet<T>*>(this)->Clone();
  }
  if(dynamic_cast<A::ArraySparseSet<T>*>(this)){
    dynamic_cast<A::ArraySparseSet<T>*>(this)->Clone();
  }
}

/**
 * @brief  
 * @tparam T 
 * @return A::FlowSet<T>* 
 */
template<typename T>
A::FlowSet<T>* A::AbstractFlowSet<T>::EmptySet(){
  A::FlowSet<T>* tmp = this->Clone();
  tmp->Clear();
  return tmp;
}

 /**
  * @brief 
  * @tparam T 
  * @param dest 
  */
template<typename T>
void A::AbstractFlowSet<T>::Copy(A::FlowSet<T>* dest){
  if(this == dest){
    return;
  }else{
    /// clear the destination and add each element of this to dest one by one
    dest->Clear();
    if(dynamic_cast<A::ArrayPackedSet<T>*>(this)){
      for(auto d : *dynamic_cast<A::ArrayPackedSet<T>*>(this)){
        dest->Add(d);
      }
    }
    if(dynamic_cast<A::ArraySparseSet<T>*>(this)){
      for(auto d : *dynamic_cast<A::ArraySparseSet<T>*>(this)){
        dest->Add(d);
      }
    }
  }
}

/**
 * @brief 
 * @tparam T 
 */
template<typename T>
void A::AbstractFlowSet<T>::Clear(){
  /// According to the type of the current object, calls the corresponding Clear()
  if(dynamic_cast<A::ArrayPackedSet<T>*>(this)){
    dynamic_cast<A::ArrayPackedSet<T>*>(this)->Clear();
  }
  if(dynamic_cast<A::ArraySparseSet<T>*>(this)){
    dynamic_cast<A::ArraySparseSet<T>*>(this)->Clear();
  }  
}

/**
 * @brief 
 * @tparam T 
 * @param other 
 */
template<typename T>
void A::AbstractFlowSet<T>::Union(A::FlowSet<T>* other){
  if(this == other){
    return;
  }
  /// add each element of other to this one by one
  if(dynamic_cast<A::ArrayPackedSet<T>*>(other)){
    for(auto d : *dynamic_cast<A::ArrayPackedSet<T>*>(other)){
      this->Add(d);
    }
  }
  if(dynamic_cast<A::ArraySparseSet<T>*>(other)){
    for(auto d : *dynamic_cast<A::ArraySparseSet<T>*>(other)){
      this->Add(d);
    }
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
void A::AbstractFlowSet<T>::Union(A::FlowSet<T>* other, A::FlowSet<T>* dest){
  /// using Union(FlowSet) with a temporary
  if(dynamic_cast<A::ArrayPackedSet<T>*>(this)){
    auto tmp = this->Clone();
    tmp->Union(other);
    tmp->Copy(dest);
  }
  if(dynamic_cast<A::ArraySparseSet<T>*>(this)){
    auto tmp = this->Clone();
    tmp->Union(other);
    tmp->Copy(dest);
  }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 */
template<typename T>
void A::AbstractFlowSet<T>::Intersection(A::FlowSet<T>* other){
  if(this == other){
    return;
  }
  /// get an empty object of this
  /// put every element of other which is in this also in tmp
  auto tmp = this->EmptySet();
  if(dynamic_cast<A::ArrayPackedSet<T>*>(other)){
    for(auto d : *dynamic_cast<A::ArrayPackedSet<T>*>(other)){
      if(dynamic_cast<A::ArraySparseSet<T>*>(this)->Contains(d)){
        tmp->Add(d);
      }
    }
  }
  if(dynamic_cast<A::ArraySparseSet<T>*>(other)){
    for(auto d : *dynamic_cast<A::ArraySparseSet<T>*>(other)){
      if(dynamic_cast<A::ArrayPackedSet<T>*>(this)->Contains(d)){
        tmp->Add(d);
      }
    }
  }
  /// copy tmp in this
  tmp->Copy(this);
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 * @param dest 
 */
template<typename T>
void A::AbstractFlowSet<T>::Intersection(A::FlowSet<T>* other, A::FlowSet<T>* dest){
  /// using Intersection(FlowSet) with a temporary
  if(dynamic_cast<A::ArrayPackedSet<T>*>(this)){
    auto tmp = this->Clone();
    tmp->Intersection(other);
    tmp->Copy(dest);
  }
  if(dynamic_cast<A::ArraySparseSet<T>*>(this)){
    auto tmp = this->Clone();
    tmp->Intersection(other);
    tmp->Copy(dest);
  }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 */
template<typename T>
void A::AbstractFlowSet<T>::Difference(A::FlowSet<T>* other){
  if(this == other){
    return;
  }
  /// get an clone object of this
  /// remove every element of other from tmp
  auto tmp = this->Clone();
  if(dynamic_cast<A::ArrayPackedSet<T>*>(other)){
    for(auto d : *dynamic_cast<A::ArrayPackedSet<T>*>(other)){
      tmp->Remove(d);
    }
  }
  if(dynamic_cast<A::ArraySparseSet<T>*>(other)){
    for(auto d : *dynamic_cast<A::ArraySparseSet<T>*>(other)){
      tmp->Remove(d);
    }
  }
  /// copy tmp to this
  tmp->Copy(this);
}

/**
 * @brief 
 * @tparam T 
 * @param other 
 * @param dest 
 */
template<typename T>
void A::AbstractFlowSet<T>::Difference(A::FlowSet<T>* other, A::FlowSet<T>* dest){
  /// using Difference(FlowSet) with a temporary
  if(dynamic_cast<A::ArrayPackedSet<T>*>(this)){
    auto tmp = this->Clone();
    tmp->Difference(other);
    tmp->Copy(dest);
  }
  if(dynamic_cast<A::ArraySparseSet<T>*>(this)){
    auto tmp = this->Clone();
    tmp->Difference(other);
    tmp->Copy(dest);
  }
}

/**
 * @brief 
 * @tparam T 
 * @return true 
 * @return false 
 */
template<typename T>
bool A::AbstractFlowSet<T>::IsEmpty(){
  /// According to the type of the current object, calls the corresponding IsEmpty()
  if(dynamic_cast<A::ArrayPackedSet<T>*>(this)){
    dynamic_cast<A::ArrayPackedSet<T>*>(this)->IsEmpty();
  }
  if(dynamic_cast<A::ArraySparseSet<T>*>(this)){
    dynamic_cast<A::ArraySparseSet<T>*>(this)->IsEmpty();
  }
}

/**
 * @brief 
 * @tparam T 
 * @return int 
 */
template<typename T>
int A::AbstractFlowSet<T>::Size(){
  /// According to the type of the current object, calls the corresponding Size()
  if(dynamic_cast<A::ArrayPackedSet<T>*>(this)){
    dynamic_cast<A::ArrayPackedSet<T>*>(this)->Size();
  }
  if(dynamic_cast<A::ArraySparseSet<T>*>(this)){
    dynamic_cast<A::ArraySparseSet<T>*>(this)->Size();
  }
}

/**
 * @brief 
 * @tparam T 
 * @param obj 
 */
template<typename T>
void A::AbstractFlowSet<T>::Add(T obj){
  /// According to the type of the current object, calls the corresponding Add()
  if(dynamic_cast<A::ArrayPackedSet<T>*>(this)){
    dynamic_cast<A::ArrayPackedSet<T>*>(this)->Add(obj);
  }
  if(dynamic_cast<A::ArraySparseSet<T>*>(this)){
    dynamic_cast<A::ArraySparseSet<T>*>(this)->Add(obj);
  }
}

/**
 * @brief 
 * @tparam T 
 * @param obj 
 * @param dest 
 */
template<typename T>
void A::AbstractFlowSet<T>::Add(T obj, A::FlowSet<T>* dest){
  auto tmp = this->Clone();
  tmp->Add(obj);
  /// copy tmp to dest
  tmp->Copy(dest);
}

/**
 * @brief 
 * @tparam T 
 * @param obj 
 */
template<typename T>
void A::AbstractFlowSet<T>::Remove(T obj){
  /// According to the type of the current object, calls the corresponding Remove()
  if(dynamic_cast<A::ArrayPackedSet<T>*>(this)){
    dynamic_cast<A::ArrayPackedSet<T>*>(this)->Remove(obj);
  }
  if(dynamic_cast<A::ArraySparseSet<T>*>(this)){
    dynamic_cast<A::ArraySparseSet<T>*>(this)->Remove(obj);
  }
}

/**
 * @brief 
 * @tparam T 
 * @param obj 
 * @param dest 
 */
template<typename T>
void A::AbstractFlowSet<T>::Remove(T obj, A::FlowSet<T>* dest){
  auto tmp = this->Clone();
  tmp->Remove(obj);
  /// copy tmp to dest
  tmp->Copy(dest);
}

/**
 * @brief 
 * @tparam T 
 * @param obj 
 * @return true 
 * @return false 
 */
template<typename T>
bool A::AbstractFlowSet<T>::Contains(T obj){
  /// According to the type of the current object, calls the corresponding Contains()
  if(dynamic_cast<A::ArrayPackedSet<T>*>(this)){
    dynamic_cast<A::ArrayPackedSet<T>*>(this)->Contains(obj);
  }
  if(dynamic_cast<A::ArraySparseSet<T>*>(this)){
    dynamic_cast<A::ArraySparseSet<T>*>(this)->Contains(obj);
  }
}

/**
 * @brief 
 * @tparam T 
 * @param other 
 * @return true 
 * @return false 
 */
template<typename T>
bool A::AbstractFlowSet<T>::Equals(A::FlowSet<T>* other){
  if(this->Size() != other->Size())
    return  false;
  
  if(this->Size() == 0 && other->Size() == 0)
    return  true;

  /// when size is same

  if(dynamic_cast<A::ArrayPackedSet<T>*>(this)){
    /// if any element of this is not in other, return false
    for(auto d : *dynamic_cast<A::ArrayPackedSet<T>*>(this)){
      if(!other->Contains(d)) return false;
    }
    return true;
  }

  if(dynamic_cast<A::ArraySparseSet<T>*>(this)){
    /// if any element of this is not in other, return false
    for(auto d : *dynamic_cast<A::ArraySparseSet<T>*>(this)){
      if(!other->Contains(d)) return false;
    }
    return true;
  }
}

/**
 * @brief 
 * @tparam T 
 * @param other 
 * @return true 
 * @return false 
 */
template<typename T>
bool A::AbstractFlowSet<T>::IsSubSet(A::FlowSet<T>* other){
  if(this->Size() == 0 && other->Size() == 0)
    return  true;

  if(dynamic_cast<A::ArrayPackedSet<T>*>(other)){
    /// if any element of other is not in this, return false
    for(auto d : *dynamic_cast<A::ArrayPackedSet<T>*>(other)){
      if(!this->Contains(d)) return false;
    }
    return true;
  }

  if(dynamic_cast<A::ArraySparseSet<T>*>(other)){
    for(auto d : *dynamic_cast<A::ArraySparseSet<T>*>(other)){
      /// if any element of other is not in this, return false
      if(!this->Contains(d)) return false;
    }
    return true;
  }
}

template class A::AbstractFlowSet<A::Variable>;
