# analyzer
---
This is **analyzer**. A interactive data flow framework (intraprocedural and interprocedural) for LLVM.  
This README describes how to build the project. For the documentation you need to generate the docs by yourselves. Instructions for generating the docs are also given below.  

###  Dependencies  

The following components are required to be installed on your system already:
(versions written in the brackets are being used in development)  
- cmake (>=3.15.0)
- GNU Make (>=4.1)
- LLVM (>=9.0.0)
- clang (>=9.0.0)
- doxygen (>=1.8.16) ( to generate documents )

Install cmake, GNU Make and doxygen using APT package handling utility.
### Getting the source code the building analyser

checkout analyser:  
```shell
git clone https://github.com/s-nil/analyzer.git
cd analyzer
```
As analyzer requires llvm and clang, use ```install.sh``` to build llvm and clang:  
```shell
bash install.sh
```
This installer downloads llvm and clang source codes in the home directory of the user and builds them at the same place. After the completion of the building process add ```$HOME/llvm-9.0.0/build/bin``` in your PATH environment variable.  

Alternatively, pre-built binaries are also available for llvm and clang:
```shell
wget http://releases.llvm.org/9.0.0/clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz
tar xvf clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz 
cd clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04/
mv clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04/ llvm-9.0.0/
```
Don't forget to add ```$HOME/llvm-9.0.0/build/bin``` in your PATH environment variable.  

Now, build analyzer:
```shell
mkdir build
cd build
cmake ..
make
```
The library has been built now. But to use this library you need to write a pass for a perticular data flow analysis. 

### Usage
Example is to check whether or not local variables are initialized or not.

- Create a class inheriting BackwardFlowAnalysis or ForwardFlowAnalysis
	example:
```cpp
class InitAnalysis : public ForwardFlowAnalysis<N,A>
```
where,
N is Node type and A is Abstratct Type.
- Create a parameterized constructor with cfg of the method. Call constructor of parent class with the cfg. Specify what are the data flow values while creating an object of ArrayPackedSet or ArraySparseSet and after that call DoAnalysis().
	example:
```cpp
InitAnalysis(CFG g){
	ForwardFlowAnalysis(g);
	FlowSet<local> *fs= new ArrayPackedSet<local>;
	allLocals = fs;
	DoAnalysis();
}
```
- Override ```EntryInitialFlow()``` and ```NewInitialFlow()``` and return the appropriate object.
	example:
```cpp
FlowSet<local> EntryInitialFlow(){
	return new ArrayPackedSet<local>();
}

FlowSet<local> NewInitialFlow(){
	FlowSet<local> *ret = new ArrayPackedSet<local>();
	ret->Copy(allLocals);
	return ret;
}

```
- Override ```Merge()```,```Copy()``` and ```FlowThrough()```.
	example:
```cpp
void Merge(FlowSet<local> in1, FlowSet<local> in2, FlowSet<local> out){
	out.Intersection(in1,in2);
}

void Copy(FlowSet<local> src, FlowSet<local> dest){
	dest.Copy(src);
}

void Flowthrough(FlowSet<local> in, BasicBlock bb, FlowSet<local> out){
	for(Instruction i : bb){
		// 'i.typeof' and 'i.pointer' are not syntactically acurate for now
		if(i.typeof == store & i.pointer is in allLocals){
			out.add(i.pointer);
		}
	}
}
```