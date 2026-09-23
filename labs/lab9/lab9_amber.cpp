/*#include <iostream>
#include <array>

using namespace std;

template <size_t size>
class StructureOfArrays {
public:
    StructureOfArrays() {
        values = new double[size];
        payloads = new array<int*, size>();
    }
    void insertTriple(string key, double value, int payload){
        if (index==size) return;
        keys[index]=key; values[index]=value; (*payloads)[index]=new int(payload);
        index++;
    }
    string readTriple(int pos){
        if ((pos<0) || (pos>=index)) return "";
        return keys[pos]+", "+to_string(values[pos])+", "+to_string(*((*payloads)[pos]));    
    }
        
    ~StructureOfArrays();
    StructureOfArrays(StructureOfArrays& obj);     

private:    
    int index=0;    
         
    array<string,size> keys;
    double* values;
    array<int*,size> *payloads;
};

// Brief test
int main(){
    StructureOfArrays<5> soa;
    soa.insertTriple(string("a"),1.0,2);
    StructureOfArrays<5> soa2=soa;
    cout<<soa.readTriple(0)<<endl;
}
*/

// Destructor
template <size_t size>
StructureOfArrays<size>::~StructureOfArrays() {
    cout << "destructor called\n";

    // Deleting each allocated int* inside payloads var.
    for (int i = 0; i < index; i++) {
        delete (*payloads)[i];
    }

    // Deleting array of pointers
    delete payloads;

    // Deleting values array
    delete[] values;
}

// Copy constructor
template <size_t size>
StructureOfArrays<size>::StructureOfArrays(StructureOfArrays& obj) {
    cout << "copy constructor called\n";

    // Copying index and keys
    index = obj.index;
    keys = obj.keys;

    // Deep copy values array
    values = new double[size];
    for (int i = 0; i < index; i++) {
        values[i] = obj.values[i];
    }

    // Deep copy payloads array
    payloads = new array<int*, size>();
    for (int i = 0; i < index; i++) {
        (*payloads)[i] = new int(*((*obj.payloads)[i]));
    }
}
