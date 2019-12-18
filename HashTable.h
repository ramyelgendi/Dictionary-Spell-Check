#include <string>
#include <iostream>
using namespace std;

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

template <class keyType, class dataType>
class hashTable
{
public:
    
    // Member Functions
    hashTable(int nelements = 11);        // Constructor
    ~hashTable();                        // Destructor
    
    // Functions Prototype Definitions

    void makeTableEmpty(const keyType &);
    bool tableIsEmpty() const;
    bool tableIsFull() const;
    bool insert(const dataType &);
    bool search(const dataType &);
    void retrieve( keyType &,dataType &);
    void update(const keyType &, dataType &);
    void traverse();
    void Suggestions(const dataType &);
    int Occupancy();
    int HammingDistance(const dataType &,const dataType &);

private:
    
    // Slot Class
    class slot
    {
    public:
        keyType key;         // key
        dataType data;        // Data
        slot *next;
    };
    
    slot *T;                            // Pointer to Storage Array
    long h;                                // Index to a slot
    int MaxSize, csize;                    // Maximum and Current Sizes
    keyType Empty;                        // empty symbol
    
    // Private Member function
    long hash(const dataType d, keyType & k) const;
};
#endif // HASH_TABLE_H

