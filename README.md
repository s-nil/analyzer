
# analyzer
---
This is **analyzer**. An easy to implement intraprocedural data flow framework with an LLVM backend.
This README describes how to build the project. For the documentation you need to generate the docs by yourselves. Instructions for generating the docs are also given below.  

###  Dependencies  
---
The following components are required to be installed on your system already:
(versions written in the brackets are being used in development)  

- cmake (3.16.3)
- GNU Make (4.2.1)
- LLVM (9.0.0)
- clang (9.0.0)
- doxygen (1.8.17) ( to generate documents )

You can install cmake, GNU Make and doxygen using APT package handling utility.

For llvm and clang use automatic installation script at [here](https://apt.llvm.org/).

### Getting the source code
---
checkout analyser:  
```shell
git clone https://github.com/s-nil/analyzer.git
cd analyzer
```

To build LLVM and Clang from source, use :
```shell
bash install.sh
```
This installer downloads llvm and clang source codes in the home directory of the user and builds them at the same place. After the completion of the building process add ```$HOME/llvm-9.0.0/build/bin``` in your PATH environment variable.  

The library has only template files so there is no need to build the library. But to use this library you need to write an analysis and build that analysis. Follow the below example for creating an analysis and after that create a directory build ```mkdir build``` and do ```cmake ..; make``` for building the analysis. Add a option -DT=OFF if you want to see the result in an html file with a CFG: 

### Usage
---
Example is showing how to do liveness analysis. It can be found in passes/liveness_analysis.

- Create a directory for your analysis in passes. Copy ```CMakeLists.txt``` from any other example analysis provided and change it as described. 

* For the library functions include ```framework.h```. For LLVM include the files accordingly.

* According to your analysis's direction either backwork or forward, use

  ```cpp
  BACKWARDANALYSIS(analysis_name,storage_class_name,property_class_name){
      
  }
  ```

  or,

  ```cpp
  FORWARDANALYSIS(analysis_name,storage_class_name,property_class_name){
      
  }
  ```

  Replace ```analysis_name``` with any name you want to give to your analysis, ```storage_class_name``` with ```ArrayPackedSet``` or ```ArraySparseSet``` and property_class_name with a user defined class. 
  
  - a property_class is a user defined class to extract the properties from the LLVM IR. In the example given in ```passes/liveness_analysis```, ```Variable``` is the property_class. Because the objects of property_class are being stored in ```map``` or ```set```, the implementation should have an overloaded < operator for the comparison of keys. It'll be more useful if more operators such as ```==```,```!=```, and ```<<``` are also overloaded.
  
* Add at least three data members.

  ```cpp
  // define a property class here
  
  BACKWARDANALYSIS(analysis_name,storage_class_name,property_class_name){
  	static char ID;		//	used by LLVM internals
  	string funcName;	//	store function name for analysis
  	storage_class_name<property_class_name> *domain;	//	store properties
  }
  ```
- Add a constructor.

  ```cpp
  // define a property class here
  
  BACKWARDANALYSIS(analysis_name,storage_class_name,property_class_name){
  	static char ID;		//	used by LLVM internals
  	string funcName;	//	store function name for analysis
  	storage_class_name<property_class_name> *domain;	//	store properties
      
      analysis_name(string f): funcName(f),FunctionPass(ID){}	//	constructor
  }
  ```

- User also need to provide a definition for extracting the properties for the IR.  Analysis may need to iterate over all the instruction. Place your definition in the following, 

  ```cpp
  EXTRACT(property_class_name){
      .
      .
      .
  }
  ```

  also assign ```elements``` to an empty vector. When the analysis finds a property, create an object of your property class and push-back this object in ```elements```.

- Now a ```RUN(){...}``` function is added. In this function necessary things that need to be done are setting up function for analysis, assign an object to domain, and start analysis. 
	example:
```cpp
// define a property class here

EXTRACT(property_class_name){
    .
    .
    .
}
BACKWARDANALYSIS(analysis_name,storage_class_name,property_class_name){
	static char ID;		//	used by LLVM internals
	string funcName;	//	store function name for analysis
	storage_class_name<property_class_name> *domain;	//	store properties
    
    analysis_name(string f): funcName(f),FunctionPass(ID){}	//	constructor
    
    RUN(){	//	run the analysis
        SETUP_FUNCTION();	//	function setup call
		domain = new ArrayPackedSet<Variable>(&F);	//	extracting properties and assign
        DoAnalysis();	//	start the analysis
        return false;
    }
}
```
- To provide initial value and entry value, use ```AP_INITIALVALUE()```and ```AP_ENTRYVALUE()``` when using ```ArrayPackedSet```, and ```AS_INTIALVALUE()``` and ```AS_ENTRYVALUE()``` when using ```ArraySparseSet```. In these functions give your definitions.
	example:
```cpp
// define a property class here

EXTRACT(property_class_name){	//	definition for extracting properties
    .
    .
    .
}
BACKWARDANALYSIS(analysis_name,storage_class_name,property_class_name){
	static char ID;		//	used by LLVM internals
	string funcName;	//	store function name for analysis
	storage_class_name<property_class_name> *domain;	//	store properties
    
    analysis_name(string f): funcName(f),FunctionPass(ID){}	//	constructor
    
    RUN(){	//	run the analysis
        SETUP_FUNCTION();	//	function setup call
		domain = new ArrayPackedSet<Variable>(&F);	//	extracting properties and assign
        DoAnalysis();	//	start the analysis
        return false;
    }
    AP_INITIALVALUE(){  return domain->EmptySet();}	//	setting initial value to emptyset
    AP_ENTRYVALUE(){    return domain->EmptySet();}	//	setting entry value to emptyset
}
```
- To provide definitions for meet, copy, and flow function, use ```AP_MERGE(property_class_name)```, ```AP_COPY(property_class_name)```, ```AP_FLOWTH(property_class_name)``` when using ```ArrayPackedSet```, and ```AS_MERGE(property_class_name)```, ```AS_COPY(property_class_name)```, ```AS_FLOWTH(property_class_name)``` when using ```ArraySparseSet```.
	    example:
```cpp
// define a property class here

EXTRACT(property_class_name){	//	definition for extracting properties
    .
    .
    .
}
BACKWARDANALYSIS(analysis_name,storage_class_name,property_class_name){
	static char ID;		//	used by LLVM internals
	string funcName;	//	store function name for analysis
	storage_class_name<property_class_name> *domain;	//	store properties
    
    analysis_name(string f): funcName(f),FunctionPass(ID){}	//	constructor
    
    RUN(){	//	run the analysis
        SETUP_FUNCTION();	//	function setup call
		domain = new storage_class_name<property_class_name>(&F);	//	extracting properties and assign
        DoAnalysis();	//	start the analysis
        return false;
    }
    AP_INITIALVALUE(){  return domain->EmptySet();}	//	setting initial value to emptyset
    AP_ENTRYVALUE(){    return domain->EmptySet();}	//	setting entry value to emptyset 
    AP_MERGE(property_class_name){ in1->Union(in2,out);}		//	setting meet operator to union
    AP_COPY(property_class_name){  in1->Copy(in2);}	//	providing copy definition
	AP_FLOWTH(property_class_name){			//	definition for flow function
    	// define kill
    	// define gen

    	storage_class_name<property_class_name>* tmp = domain->EmptySet();
    	in->Difference(kill,tmp);
    	tmp->Union(gen,out);
	}
};

```

It turns out that, user has three main things to define.

 -		-	a property class
      	-	a function in ```EXTRACT(){...}``` for finding the properties
      	-	and a flow function in ```*_FLOWTH(){ ... }```
 -	At last add ```SETUP(analysis_name)``` at the end.

### Documentation

In docs directory, run following command to create documentation. Open html/index.html in a browser.
```shell
doxygen Doxyfile
```
