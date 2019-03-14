#include "lab2_drones_manager.hpp"
#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

// PURPOSE: Creates a new empty DronesManager
DronesManager::DronesManager() {
    first = NULL;   //Sets head as null
    last = NULL;    //Sets tail as null
    size = 0;       //Sets size as 0
}

// PURPOSE: Destroys this instance and frees up all dynamically allocated memory
DronesManager::~DronesManager() {
}



// PURPOSE: Returns the number of elements in the list
unsigned int DronesManager::get_size() const {
	return size;    //Return size of list
}

// PURPOSE: Checks if the list is empty; returns true if the list is empty, false otherwise
bool DronesManager::empty() const {
    if(size==0){
        return true;    //Returns true is list is empty
    }
    return false;
}

// PURPOSE: Returns the value at the given index in the list
DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
    if( size == 0)  //If list is empty, return DroneRecord(0)
        return DroneRecord(0,0,2018,"TYPE1","A","B","C");
    else if ( size < index)  //If index is invalid, return last element
        return *last;
    
    //Return the value at given index
    DroneRecord* element = first;       //Point element towards head
    for( int i = 0 ; i< index;i++)
        element=element->next;          //Loop through list and point element towards each next index
    
    return *element;
}

// PURPOSE: Searches for the given value, and returns the index of this value if found
unsigned int DronesManager::search(DroneRecord val) const {
    if( first==NULL)
        return 0;
    DroneRecord* location=first;
    int index = 0;
    while( location!=NULL){
        if( location->droneID == val.droneID)
            return index;
        index++;
        location=location->next;
    }
    return size;
}

// PURPOSE: Prints all the elements in the list to the console
void DronesManager::print() const {
    if(size==0){
        cout<<"EMPTY LIST"<<endl;
        return;
    }
    DroneRecord* location = first;
    int index = 0;
    while(location!=NULL){
        cout<<"INDEX:"<<index<<" DATA:"<<location->droneID<<" "<<location->range<<endl;
        index++;
        location=location->next;
    }
}

// PURPOSE: Inserts a value into the list at a given index
bool DronesManager::insert(DroneRecord val, unsigned int index) {
    if(size < index)
        return false;       //If index is out of bounds, return false

    if( index == 0){    //Insert at front
        DroneRecord* element = new DroneRecord(val.droneID, val.range, val.yearBought, val.droneType,val.manufacturer, val.description , val.batteryType);
        first->next=element;
        first->prev=NULL;
        size++;
        return true;
    }
    
    //Insert at given index
    DroneRecord* end = first;
    for( int i = 0; i <index-1; i++ ){
        end=end->next;
    }
    
    DroneRecord* elementTwo = end->next;      //Set elementTwo to the node in front of the
    end->next = new DroneRecord(val.droneID, val.range, val.yearBought, val.droneType,val.manufacturer, val.description , val.batteryType);
    end->next->prev=end;
    end->next->next=elementTwo;
    size++;
    return true;
}

bool DronesManager::insert_front(DroneRecord val) {
    if( size == 0){ //If list is empty
        first = new DroneRecord(val.droneID, val.range, val.yearBought, val.droneType,val.manufacturer, val.description , val.batteryType);
        first->next=NULL;
        first->prev=NULL;
        last=first;
        size++;
        return true;
    }
    else{
        int index = 0;
        return insert( val, index);
    }
}



bool DronesManager::insert_back(DroneRecord val) {
    
    if (size == 0) {
        first = new DroneRecord(val.droneID, val.range, val.yearBought, val.droneType,val.manufacturer, val.description , val.batteryType);
        first->prev=NULL;
        first->next=NULL;
        last=first;
    } else {
        DroneRecord* element = first;
        while (element->next)
            element = element->next;
        
        element->next=new DroneRecord(val.droneID, val.range, val.yearBought, val.droneType,val.manufacturer, val.description , val.batteryType);
        last=element->next;
        last->next=NULL;
        last->prev=NULL;
        cout << element->droneID;
    }
    size++;
    return true;
}

bool DronesManager::remove(unsigned int index) {
    if( size < index || first==NULL)        //If index is out of bounds, return false
        return false;
    
    DroneRecord* element = first;
    for( int i = 0; i< index-1;i++)
        element=element->next;          //Set element to the node prev to the index selected
    
    DroneRecord* ptr=element->next;
    element->next=ptr->next;
    ptr->next->prev=element;
    
    free(ptr);          //Remove dangling node
    size--;
    return true;
}

bool DronesManager::remove_front() {
    if( first==NULL)
        return false;
    DroneRecord* ptr = first;
    first = first->next;
    free(ptr);      //Remove dangling node
    size--;
    return true;
}

bool DronesManager::remove_back() {
    DroneRecord* ptr = first;
    DroneRecord* prev = ptr;
    
    if( first==NULL)
        return false;
    if(first->next == NULL){
        ptr = first;
        first = NULL;
        free(ptr);
    }
    else{
        ptr = first;
        while(ptr -> next != NULL){
            prev = ptr;
            ptr = ptr -> next;
        }
    }
    size--;
    return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord val) {
    if( size < index || first==NULL)
        return false;
    DroneRecord* element= first;
    for( int i = 0; i < index; i++)
        element=element->next;
    element->yearBought=val.yearBought;
    element->droneType=val.droneType;
    element->droneID=val.droneID;
    element->description=val.description;
    element->batteryType=val.batteryType;
    element->range=val.range;
    element->manufacturer=val.manufacturer;

    return true;
    
}

bool DronesManager::reverse_list() {
    if( first==NULL)
        return false;
    DroneRecord element( last->droneID, last->range, last->yearBought, last->droneType,last->manufacturer, last->description , last->batteryType);
    for(int i = 0; i < size;i++){
        insert(element,i);
        remove_back();
        element.description=last->description;
        element.batteryType=last->batteryType;
        element.droneID=last->droneID;
        element.yearBought=last->yearBought;
        element.droneType=last->droneType;
        element.range=last->range;
        element.manufacturer=last->manufacturer;
 
    }
    return true;
    
}

bool DronesManagerSorted::is_sorted_asc() const {
	return false;
}

bool DronesManagerSorted::is_sorted_desc() const {
    return false;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
	return false;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
	return false;
}

void DronesManagerSorted::sort_asc() {
}
    
void DronesManagerSorted::sort_desc() {
}
