#include "pirates24b2.h"
#include <iostream>



//oceans_t::oceans_t() : array(new genericHash<int,shared_ptr<UnionFind>>(128)), fleetTable(M), pirateTable(N1)
//{
//
//}


//////////// my construct

oceans_t::oceans_t() : array(nullptr),  numOfElements(0), realSize(0), fleetTable(M), pirateTable(N1) {
    array = new genericHash<int, shared_ptr<UnionFind>>(128);
    realSize = 128;
}

//oceans_t::~oceans_t() {
//	 //Clean up fleets
//	delete[] array;
//    array = nullptr;
//
//	 for (int i = 0; i < fleetTable.tableSize; ++i) {
//	 	LinkedList& list = fleetTable.table[i];
//	 	Node* current = list.head;
//	 	while (current != nullptr) {
//	 		Node* toDelete = current;
//	 		current = current->next;
//	 		delete toDelete;
//	 	}
//	 }
//	 delete[] fleetTable.table; // Clean up the array of LinkedLists
//     fleetTable.table= nullptr;
//
//	 // Clean up pirates
//	 for (int i = 0; i < pirateTable.tableSize; ++i) {
//	 	PirateLinkedList& list = pirateTable.table[i];
//	 	PirateNode* current = list.head;
//	 	while (current != nullptr) {
//	 		PirateNode* toDelete = current;
//	 		current = current->next;
//	 		delete toDelete;
//	 	}
//	 }
//	 delete[] pirateTable.table; // Clean up the array of PirateLinkedLists
//     pirateTable.table= nullptr;
//}

//////// my destructor
//oceans_t::~oceans_t() {
//    // Clean up the genericHash array
//    if (array) {
//        for (size_t i = 0; i < array->getCapacity(); ++i) {
//            UnionFind *uf = (*array)[i];
//            if (uf != nullptr) {
//                delete uf;
//            }
//        }
//        delete array;
//        array = nullptr;
//    }
//}
//
//    // Clean up fleets
//    for (int i = 0; i < fleetTable.tableSize; ++i) {
//        LinkedList& list = fleetTable.table[i];
//        Node* current = list.head;
//        while (current != nullptr) {
//            Node* toDelete = current;
//            current = current->next;
//            delete toDelete;
//        }
//    }
//    delete[] fleetTable.table; // Clean up the array of LinkedLists
//    fleetTable.table = nullptr;
//
//    // Clean up pirates
//    for (int i = 0; i < pirateTable.tableSize; ++i) {
//        PirateLinkedList& list = pirateTable.table[i];
//        PirateNode* current = list.head;
//        while (current != nullptr) {
//            PirateNode* toDelete = current;
//            current = current->next;
//            delete toDelete;
//        }
//    }
//    delete[] pirateTable.table; // Clean up the array of PirateLinkedLists
//    pirateTable.table= nullptr;

//delete array;
//}


//////// chat desrtructor

//oceans_t::~oceans_t(){
//    for (int i = 0; i < numOfElements; ++i) {
//        shared_ptr<UnionFind> fleet = array->find(i);
//        delete fleet;
//    }
//    delete array; // Clean up dynamically allocated memory for the array
//}

/////
//oceans_t::~oceans_t() {
//    if (array) {
//        for (int i = 0; i < numOfElements; ++i) {
//            shared_ptr<UnionFind> fleet = array->find(i);
//            delete fleet;
//        }
//        delete array; // Clean up dynamically allocated memory for the array
//    }
//}
oceans_t::~oceans_t() {
    // if (array) {
    //     for (int i = 0; i < realSize; ++i) {
    //         shared_ptr<UnionFind> fleet = array->find(i);
    //         if (fleet != nullptr) {
    //             delete fleet;
    //         }
    //     }
    //     delete array; // Clean up dynamically allocated memory for the array
    // }
	delete array;
}





StatusType oceans_t::add_fleet(int fleetId)
{

	if (fleetId <= 0) {
		return StatusType::INVALID_INPUT;
	}

	// Check if the fleet already exists
	if (fleetTable.contains(fleetId)) {
		return StatusType::FAILURE;
	}
	try
	{
		if(array->find(fleetId) !=nullptr && array->find(fleetId)->findhead()->fleetId != fleetId){
				return StatusType::FAILURE;
		}
	}
	catch(...)
	{

	}


	// Try to insert the new fleet into the hashtable
	try {
		fleetTable.insert(fleetId, 1); // Insert with 1 ship initially
	}
	catch (std::bad_alloc&) {
		return StatusType::ALLOCATION_ERROR; // Handle memory allocation errors
	};

	try {
		shared_ptr<UnionFind> new_node = make_shared<UnionFind>(fleetId);
		array->insert(fleetId, new_node);
	}
	catch (std::bad_alloc&) {
		return StatusType::ALLOCATION_ERROR; // Handle memory allocation errors
	}
		return StatusType::SUCCESS;

}




StatusType oceans_t::add_pirate(int pirateId, int fleetId) {

	if (pirateId <= 0 || fleetId <= 0) {
		return StatusType::INVALID_INPUT;
	}

	if (!fleetTable.contains(fleetId)) {
		return StatusType::FAILURE; // Fleet does not exist
	}

	if (pirateTable.contains(pirateId)) {
		return StatusType::FAILURE; // Pirate already exists
	}
		// check if the fleetId is the same as saved in the unino find


	if(array->find(fleetId)->find()->fleetId != fleetId){
			return StatusType::FAILURE;
	}
	try {
		// rank = number of pirates in the fleet
		int rank = array->find(fleetId)->find()->size + 1;
		int decrease = getValue(fleetId);
		pirateTable.insert(pirateId, fleetId, 0, rank - decrease ); // Add pirate with initial money 0

		// Increase the number of pirates in the fleet
		fleetTable.find(fleetId)->numPirates += 1;
		// updating the UF
		array->find(fleetId)->find()->size += 1;

		// You might need to update the number of ships or pirates in fleetTable here
		return StatusType::SUCCESS;
	}
	catch (std::bad_alloc&) {
		return StatusType::ALLOCATION_ERROR;
	}

}


StatusType oceans_t::pay_pirate(int pirateId, int salary)
{
	// TODO: Your code goes here
	if (pirateId <= 0 || salary <= 0) {
		return StatusType::INVALID_INPUT;
	}

	if (!pirateTable.contains(pirateId)) {
		return StatusType::FAILURE; // Pirate does not exist
	}

	try {
		if (!pirateTable.update_salary(pirateId, salary)) {
			return StatusType::FAILURE; // Failed to update the salary
		}


		return StatusType::SUCCESS;
	}
	catch (std::bad_alloc&) {
		return StatusType::ALLOCATION_ERROR; // Handle memory allocation errors
	}

	

}

output_t<int> oceans_t::num_ships_for_fleet(int fleetId) {
	if (fleetId <= 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}

	// Check if the fleet exists
	if (!fleetTable.contains(fleetId)) {
		return output_t<int>(StatusType::FAILURE);
	}

	if(array->find(fleetId)->findhead()->fleetId != fleetId ){
			return StatusType::FAILURE;
	}

	try {
		int numShips = array->find(fleetId)->find()->numofships;
		return output_t<int>(numShips);
	}
	catch (std::bad_alloc&) {
		return output_t<int>(StatusType::ALLOCATION_ERROR);
	}
}

output_t<int> oceans_t::get_pirate_money(int pirateId) {
	if (pirateId <= 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}

	try {

		if (!pirateTable.contains(pirateId)) {
			return output_t<int>(StatusType::FAILURE);
		}

		// Retrieve the amount of money for the pirate
		int money = pirateTable.getMoney(pirateId);
		//int extra = getValue(pirateId);
		//money += extra;
		return output_t<int>(money); // SUCCESS with the amount of money
	}
	catch (const std::bad_alloc&) {
		return output_t<int>(StatusType::ALLOCATION_ERROR);
	}
}


/*
StatusType oceans_t::Union(int first_group , int second_group){

        shared_ptr<UnionFind> first = array->find(first_group)->findhead();
        shared_ptr<UnionFind> second = array->find(second_group)->findhead();

        if(first->fleetId == second->fleetId){ // means that the two groups had been merged before
            return StatusType::INVALID_INPUT;
        }


        shared_ptr<UnionFind> bigger = (first->size >= second->size) ? first : second;
        shared_ptr<UnionFind> smaller = (first->size < second->size) ? first : second;

		shared_ptr<UnionFind> bigger_pirates = (first->numOfPirates >= second->numOfPirates) ? first : second;


        if( array->find(first_group)->findhead()->fleetId == bigger ->fleetId){
            //bigger->extra += getValue(smaller->owner)*factor;
            smaller->extra -= bigger->extra;

            //bigger->CompanyVal += getValue(smaller->GroupID)*factor;

            //smaller->CompanyVal -= bigger->extra;
        }else{// first acquirer = smaller
            // smaller buys bigger

           // smaller->extra += getValue(bigger->owner)* factor;
            smaller->extra -= bigger->extra;

            //bigger->owner = smaller->owner;

        }

		// smaller in terms of number of ships
        smaller->father = bigger;

        //shared_ptr<UnionFind> smaller_pirates = (first->numOfPirates < second->numOfPirates) ? first : second;

		bigger->fleetId=bigger_pirates->fleetId;
		smaller->extra += bigger->size;
		bigger->numOfPirates += smaller->numOfPirates; // update the number of pirates

        bigger->size += smaller->size; //update the number of ships
        return StatusType::SUCCESS;
    }

	*/

	StatusType oceans_t::Union(int first_group, int second_group) {

    shared_ptr<UnionFind> first = array->find(first_group)->findhead();
    shared_ptr<UnionFind> second = array->find(second_group)->findhead();

    if (first->fleetId == second->fleetId) { // Groups are already merged
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<UnionFind> bigger = (first->size >= second->size) ? first : second;
    shared_ptr<UnionFind> smaller = (first->size < second->size) ? first : second;

	// the rank of the smaller pirates group will
	// get the extra value of the bigger pirates group
    
    smaller->extra += bigger->size;;


    // Union operation
    smaller->father = bigger;

  
    // Update the number of pirates and ships
    bigger->numofships += smaller->numofships;
    bigger->size += smaller->size;

    return StatusType::SUCCESS;
}


StatusType oceans_t::unite_fleets(int fleetId1, int fleetId2) {
	// Input validation
	if (fleetId1 <= 0 || fleetId2 <= 0 || fleetId1 == fleetId2) {
		return StatusType::INVALID_INPUT;
	}

	// Check if both fleets exist
	if (!fleetTable.contains(fleetId1) || !fleetTable.contains(fleetId2)) {
		return StatusType::FAILURE; // One or both fleets do not exist
	}
		// check if the fleetId is the same as saved in the unino find
	if(array->find(fleetId1)->findhead()->fleetId != fleetId1 || array->find(fleetId2)->findhead()->fleetId != fleetId2){
			return StatusType::FAILURE;
	}



	// Retrieve the number of pirates for both fleets
	int numOfPirates1 = this->array->find(fleetId1)->findhead()->size;
	int numOfPirates2 = this->array->find(fleetId2)->findhead()->size;	
	
	if (numOfPirates1 <=0 || numOfPirates2 <=0) {
		return StatusType::FAILURE; // Failure to retrieve number of ships
	}

	// Determine which fleet ID to keep
	//int newFleetId = (ships1 >= ships2) ? fleetId1 : fleetId2;
	//int oldFleetId = (newFleetId == fleetId1) ? fleetId2 : fleetId1;

	//shared_ptr<UnionFind> biggerFleet = this->array->find(newFleetId)->findhead();
	//shared_ptr<UnionFind> smallerFleet = this->array->find(oldFleetId)->findhead();

	// my code, union the two fleets in union find data structure
	try {
		this->Union(fleetId1, fleetId2);
	}
	catch (std::bad_alloc&) {
		return StatusType::ALLOCATION_ERROR;
	}

	return StatusType::SUCCESS;
}


StatusType oceans_t::pirate_argument(int pirateId1, int pirateId2) {

	// Input validation
	if (pirateId1 <= 0 || pirateId2 <= 0 || pirateId1 == pirateId2) {
		return StatusType::INVALID_INPUT;
	}

	// Check if both pirates exist
	if (!pirateTable.contains(pirateId1) || !pirateTable.contains(pirateId2)) {
		return StatusType::FAILURE;
	}

	// Retrieve pirate information
	PirateNode* pirate1 = nullptr;
	PirateNode* pirate2 = nullptr;

	// Find pirate1
	PirateLinkedList* list1 = &pirateTable.table[pirateTable.hashFunction(pirateId1)];
	PirateNode* current = list1->head;
	while (current != nullptr) {
		if (current->pirateId == pirateId1) {
			pirate1 = current;
			break;
		}
		current = current->next;
	}

	// Find pirate2
	PirateLinkedList* list2 = &pirateTable.table[pirateTable.hashFunction(pirateId2)];
	current = list2->head;
	while (current != nullptr) {
		if (current->pirateId == pirateId2) {
			pirate2 = current;
			break;
		}
		current = current->next;
	}

	// Check if pirates were found
	if (pirate1 == nullptr || pirate2 == nullptr) {
		return StatusType::FAILURE;
	}

	// Check if pirates are in the same fleet
	// auto pirate1_head = array->find(pirate1->fleetId)->findhead();
	if ( array->find(pirate1->fleetId)->findhead() != array->find(pirate2->fleetId)->findhead() ) {
		return StatusType::FAILURE;
	}



	int rankDifference = 0;
	int pirate1_rank = getValue(pirate1->fleetId) + pirate1->rank;
	int pirate2_rank = getValue(pirate2->fleetId) + pirate2->rank;

	// Determine rank difference
	if (pirate1_rank > pirate2_rank)
		rankDifference = pirate1_rank - pirate2_rank ;
	else 
		rankDifference = pirate2_rank - pirate1_rank;


	// Update pirate balances
	try {
		//std::cout << "rank:" << rankDifference << std::endl;

		if (pirate1_rank > pirate2_rank ) {
			pirateTable.update_salary(pirateId1, 0 - rankDifference);
			pirateTable.update_salary(pirateId2,  rankDifference);
		}
		else {
			// Pirate 1 pays Pirate 2

			pirateTable.update_salary(pirateId1,  rankDifference);
			pirateTable.update_salary(pirateId2, 0 - rankDifference);
		}
	}
	catch (std::bad_alloc&) {
		return StatusType::ALLOCATION_ERROR;
	}

	return StatusType::SUCCESS;
}