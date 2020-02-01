#include "ArrayPackedSet.h"

/**
 * @brief Construct a new A:: Array Packed Set< T>:: Array Packed Set object.
 *  Constructs a new BitVector, of the same size as mapper.
 *  mapper argument has the objects already.
 * @tparam T 
 *  Type of the object to be stored
 * @param mapper 
 *  Bidirectional map
 */
template<typename T>
A::ArrayPackedSet<T>::ArrayPackedSet(ObjectIntMapper<T> mapper) : A::ArrayPackedSet<T>::ArrayPackedSet(mapper, llvm::BitVector(mapper.Size()))
{}

/**
 * @brief Construct a new A:: Array Packed Set< T>:: Array Packed Set object.
 *  Creates new object using the arguments
 * @tparam T 
 * @param mapper 
 *  Bidirectional map
 * @param bits 
 */
template<typename T>
A::ArrayPackedSet<T>::ArrayPackedSet(ObjectIntMapper<T> mapper, llvm::BitVector bits){
    this->map = mapper;
    this->bits = bits;
}

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
void A::ArrayPackedSet<T>::Complement(){
    //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param dest 
 */
template<typename T>
void A::ArrayPackedSet<T>::Complement(A::FlowSet<T>* dest){
    //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @return A::FlowSet<T>* 
 */
template<typename T>
A::FlowSet<T>* A::ArrayPackedSet<T>::TopSet(){
    //TODO
}

/**
 * @brief 
 * returns a new but with same this' attributes
 * @tparam T 
 * @return A::FlowSet<T>* 
 */
template<typename T>
A::FlowSet<T>* A::ArrayPackedSet<T>::Clone(){
    return new ArrayPackedSet<T>(this->map,this->bits);
}

/**
 * @brief 
 * returns a new but with same this' map and bitset with all bits false
 * @tparam T 
 * @return A::FlowSet<T>* 
 */
template<typename T>
A::FlowSet<T>* A::ArrayPackedSet<T>::EmptySet(){
    return new ArrayPackedSet<T>(this->map);
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param dest 
 */
template<typename T>
void A::ArrayPackedSet<T>::Copy(A::FlowSet<T>* dest){
    if(dest == this){
        return;
    }
    if(SameType(dest)){
        A::ArrayPackedSet<T>* tmp = dynamic_cast<A::ArrayPackedSet<T>*>(dest);
        CopyBitSet(tmp);
    }else{
        A::AbstractBoundedFlowSet<T>::Copy(dest);
    }
}

/**
 * @brief 
 * reset all bits
 * @tparam T 
 */
template<typename T>
void A::ArrayPackedSet<T>::Clear(){
    bits.clear();
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 */
template<typename T>
void A::ArrayPackedSet<T>::Union(A::FlowSet<T>* other){
    if(this == other){
        return;
    }else{
        Union(other,this);
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
void A::ArrayPackedSet<T>::Union(A::FlowSet<T>* otherFlow, A::FlowSet<T>* destFlow){
    if(SameType(otherFlow) && SameType(destFlow)){
        A::ArrayPackedSet<T>* other = dynamic_cast<A::ArrayPackedSet<T>*>(otherFlow);
        A::ArrayPackedSet<T>* dest = dynamic_cast<A::ArrayPackedSet<T>*>(destFlow);
        llvm::BitVector tmp(this->bits);
        tmp |= other->bits;
        dest->bits = tmp;
    }else{
        A::AbstractBoundedFlowSet<T>::Union(otherFlow,destFlow);
    }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 */
template<typename T>
void A::ArrayPackedSet<T>::Intersection(A::FlowSet<T>* other){
    if(other == this){
        return;
    }else{
        Intersection(other,this);
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
void A::ArrayPackedSet<T>::Intersection(A::FlowSet<T>* otherFlow, A::FlowSet<T>* destFlow){
    if(SameType(otherFlow) && SameType(destFlow)){
        A::ArrayPackedSet<T>* other = dynamic_cast<A::ArrayPackedSet<T>*>(otherFlow);
        A::ArrayPackedSet<T>* dest  = dynamic_cast<A::ArrayPackedSet<T>*>(destFlow);
        llvm::BitVector tmp(this->bits);
        tmp &= other->bits;
        dest->bits = tmp;
    }else{
        A::AbstractBoundedFlowSet<T>::Intersection(otherFlow,destFlow);
    }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 */
template<typename T>
void A::ArrayPackedSet<T>::Difference(A::FlowSet<T>* other){
    if(other == this){
        bits.reset(dynamic_cast<A::ArrayPackedSet<T>*>(other)->bits);
    }else{
        Difference(other,this);
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
void A::ArrayPackedSet<T>::Difference(A::FlowSet<T>* otherFlow, A::FlowSet<T>* destFlow){
    if(SameType(otherFlow) && SameType(destFlow)){
        A::ArrayPackedSet<T>* other = dynamic_cast<A::ArrayPackedSet<T>*>(otherFlow);
        A::ArrayPackedSet<T>* dest  = dynamic_cast<A::ArrayPackedSet<T>*>(destFlow);
        llvm::BitVector tmp(this->bits);
        tmp.reset(other->bits);
        dest->bits = tmp;
    }else{
        A::AbstractBoundedFlowSet<T>::Difference(otherFlow,destFlow);
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
bool A::ArrayPackedSet<T>::IsEmpty(){
    return bits.empty();
}

/**
 * @brief 
 * 
 * @tparam T 
 * @return int 
 */
template<typename T>
int A::ArrayPackedSet<T>::Size(){
    return bits.size();
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param obj 
 */
template<typename T>
void A::ArrayPackedSet<T>::Add(T obj){
    bits.set(map.GetInt(obj));
}

// /**
//  * @brief 
//  * 
//  * @tparam T 
//  * @param obj 
//  * @param dest 
//  */
// template<typename T>
// void A::ArrayPackedSet<T>::Add(T obj, A::FlowSet<T>* dest){
//     //TODO
// }

/**
 * @brief 
 * 
 * @tparam T 
 * @param obj 
 */
template<typename T>
void A::ArrayPackedSet<T>::Remove(T obj){
    bits.reset(map.GetInt(obj));
}

// /**
//  * @brief 
//  * 
//  * @tparam T 
//  * @param obj 
//  * @param dest 
//  */
// template<typename T>
// void A::ArrayPackedSet<T>::Remove(T obj, A::FlowSet<T>* dest){
//     //TODO
// }

/**
 * @brief 
 * check if the object is in the map and if it is, it is set or not in the bitset
 * @tparam T 
 * @param obj 
 * @return true 
 * @return false 
 */
template<typename T>
bool A::ArrayPackedSet<T>::Contains(T obj){
    return map.Contains(obj) && bits.test(map.GetInt(obj));
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
bool A::ArrayPackedSet<T>::Equals(A::FlowSet<T>* other){
    if(SameType(other)){
        A::ArrayPackedSet<T>* other = dynamic_cast<A::ArrayPackedSet<T>*>(other);
        return bits == other->bits;
    }else{
        return A::AbstractBoundedFlowSet<T>::Equals(other);
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
bool A::ArrayPackedSet<T>::IsSubSet(A::FlowSet<T>* other){
    if(SameType(other)){
        llvm::BitVector tmp(this->bits);
        tmp |= dynamic_cast<A::ArrayPackedSet<T>*>(other)->bits;
        if(this->bits == tmp){
            return true;
        }
        return false;
    }else{
        return A::AbstractBoundedFlowSet<T>::IsSubSet(other);
    }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @return std::list<T> 
 */
template<typename T>
std::list<T> A::ArrayPackedSet<T>::ToList(){
    return ToList(bits,0);
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param bits 
 * @param base 
 * @return std::list<T> 
 */
template<typename T>
std::list<T> A::ArrayPackedSet<T>::ToList(llvm::BitVector bits, int base){
    if(bits.size() == 0){
        return std::list<T>();
    }else{
        std::list<T> objects;
        for (int i = base; i < bits.size(); ++i){
            if(bits.test(i)){
                objects.push_back(map.GetObject(i));
            }
        }
        return objects;
    }
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param low 
 * @param high 
 * @return std::list<T> 
 */
template<typename T>
std::list<T> A::ArrayPackedSet<T>::ToList(int low, int high){
    //TODO
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
bool A::ArrayPackedSet<T>::SameType(A::FlowSet<T>* o){
    if(dynamic_cast<A::ArrayPackedSet<T>*>(o) != nullptr)
        return true;
    return false;
}

/**
 * @brief 
 * when this and o are different and map of both is same, copy bitset from this to o
 * @tparam T 
 * @param o 
 * @return llvm::BitVector 
 */
template<typename T>
llvm::BitVector A::ArrayPackedSet<T>::CopyBitSet(A::ArrayPackedSet<T>* o){
    assert(this->map == o->map);
    if(o != this){
        o->bits.clear();
        o->bits |= bits;
    }
    return o->bits;
}

template class A::ArrayPackedSet<int>;