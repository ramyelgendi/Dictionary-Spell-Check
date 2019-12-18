#include <iostream>
#include <cmath>
#include "HashTable.h"
#include <string>
using namespace std;

// Constructor with argument, size is nelements, default is 11
template <class keyType, class dataType>
hashTable<keyType, dataType>::hashTable(int nelements)
{
    MaxSize = nelements;
    T = new slot[MaxSize];
    h = -1;
    csize = 0;
}

// Destructor
template <class keyType, class dataType>
hashTable<keyType, dataType>::~hashTable()
{
    slot * cur;slot * temp;
    for (int i = 0; i<MaxSize; i++)
    {
        if (T[i].key != Empty)
        {
            cur = &T[i];
            while (cur->next !=NULL)
            {
                temp = cur;
                cur = cur->next;
                if( temp!= &T[i])
                    delete temp;
            }
        }
    }
    delete[] T;
}

// Empty all slots
template <class keyType, class dataType>
void hashTable<keyType, dataType>::makeTableEmpty(const keyType &k) {
    Empty = k;
    for (int i = 0; i < MaxSize; i++)
    {
        T[i].key = Empty;
        T[i].next = NULL;
    }
    h = -1;
    csize = 0;
}

// return True if table is empty
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::tableIsEmpty() const
{
    return (csize == 0);
}

// return True if table is full
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::tableIsFull() const
{
    return (csize == MaxSize);
}

// insert key and data at a hashed slot
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::insert(const dataType &d){
     keyType k = 0;
    if (!tableIsFull())
    {
        h = hash(d,k);
        if (T[h].key != Empty)
        {
            //Insert at end of linked list of T[h];
            slot *temp = new slot;
            slot *cur;
            temp->data = d;
            temp->key = k;
            temp->next = NULL;
            
            cur = &T[h];
            while(cur->next != NULL)
                cur = cur->next;
            
            cur->next = temp;
        }
        else
        {
            T[h].key = k;
            T[h].data = d;
        }
        csize++;
        return true;
    }
    else
        return false;
}
// Search the table for the slot that matches key.
// If found, return True, set current position to slot
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::search(const dataType &data){
    slot*cur;
    if (!tableIsEmpty()) {
        keyType k;
        h = hash(data,k);
        while(true){
            if (T[h].key == Empty)
                return false;
            else
            {
                cur = &T[h];
                while(cur != NULL)
                {
                    if (k == cur->key)
                        return true;
                    else
                        cur = cur->next;
                }
                return false;
            }
        }
    }
    else
        return false;
}
// Retrieve the data inside a given 'key'
template <class keyType, class dataType>
void hashTable<keyType, dataType>::retrieve(keyType &k,dataType &word){
    slot*cur;
    if (!tableIsEmpty()) {
        h = k % MaxSize;
        while(true){
            if (T[h].key == Empty)
                return;
            else
            {
                cur = &T[h];
                while(cur != NULL)
                {
                    if (k == cur->key)
                    {
                        word=cur->data;
                        return;
                    }
                    else
                        cur = cur->next;
                }
                return;
            }
        }
    }
    else
        return;
}
// Update the data inside a given 'key'
template <class keyType, class dataType>
void hashTable<keyType, dataType>::update(const keyType &k,dataType &data){
    slot*cur;
    if (!tableIsEmpty()) {
        h = hash(data,k);
        while(true){
            if (T[h].key == Empty)
                return;
            else
            {
                cur = &T[h];
                while(cur != NULL)
                {
                    if (k == cur->key)
                    {
                        cur->data=data;
                        return;
                    }
                    else
                        cur = cur->next;
                }
                return;
            }
        }
    }
    else
        return;
}
// Private Hashing Function
template <class keyType, class dataType>
long hashTable<keyType, dataType>::hash(const dataType d, keyType & k) const
{
    long temp = 0, n = d.length();
    for (int i = 0; i < n; i++)
        temp = temp + int(tolower(d[i])) * pow(26, i);
    k = temp;
    temp = temp % MaxSize;
    
    return temp;
}

// Amount of occupied slots
template <class keyType, class dataType>
int hashTable<keyType, dataType>::Occupancy()
{
    return csize;
}

// Pring the whole table
template <class keyType, class dataType>
void hashTable <keyType, dataType>::traverse() {
    slot * cur;
    for (int i = 0; i<MaxSize; i++)
    {
        if (T[i].key != Empty)
        {
            cout<<T[i].data<<"  ";
            cur = T[i].next;
            while (cur !=NULL)
            {
                cout<<cur->data<<"  ";
                cur = cur->next;
            }
            cout<<endl;
        }
    }
}

// Suggestions
template <class keyType, class dataType>
void hashTable <keyType, dataType>::Suggestions(const dataType &data) {
    slot * cur;
    int count=0;
    cout<<" - ( ";
    for (int i = 0; i<MaxSize; i++)
    {
        if(count < 5)
        {
            if (T[i].key != Empty)
            {
                if(T[i].data[0] == data[0])
                    if(HammingDistance(data,T[i].data) < 3)
                    {
                        cout<<T[i].data<<" ";
                        count++;
                    }
                
                cur = T[i].next;
                while (cur !=NULL)
                {
                    if(cur->data[0] == data[0])
                        if(HammingDistance(data,cur->data) < 3)
                        {
                            cout<<cur->data<<" ";
                            count++;
                        }
                    cur = cur->next;
                }
            }
        }
    }
    if(count == 0)
        cout<< "No Suggestions Found  ";
    cout<<") "<<" [Only "<<count<<" suggestion(s) were found!]\n";

}
// Distance
template <class keyType, class dataType>
int hashTable <keyType, dataType>::HammingDistance(const dataType &one,const dataType &two) {
    int count = 0;
    long max = (one.length()<two.length())?two.length():one.length();
    for (int i =0; i< max; i++)
    {
        if(one[i] != two[i])
            count++;
    }
    return count;
}
