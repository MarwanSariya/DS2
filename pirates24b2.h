//
// 234218 Data Structures 1.
// Semester: 2024B (spring).
// Wet Exercise #2.
//
// Recommended TAB size to view this file: 8.
//
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
//

#ifndef PIRATESA2_H_
#define PIRATESA2_H_

#include "wet2util.h"
#include "genericHash.h"
#include "UnionFind.h"

class oceans_t
{
private:
	genericHash<int, shared_ptr<UnionFind>> *array;
	// we are using dynami array of UnionFind pointers to represent the fleets

	int numOfElements; // meaning the numer of fleets
	int realSize;	   // of the array
	const int multiply = 2;

	Hashtable fleetTable; // Hashtable for fleets

	PirateHashtable pirateTable; // Hashtable for pirates

	StatusType Union(int first_group, int second_group);

public:
	// <DO-NOT-MODIFY> {
	void resize();

	oceans_t();

	virtual ~oceans_t();

	StatusType add_fleet(int fleetId);

	StatusType add_pirate(int pirateId, int fleetId);

	StatusType pay_pirate(int pirateId, int salary);

	output_t<int> num_ships_for_fleet(int fleetId);

	output_t<int> get_pirate_money(int pirateId);

	StatusType unite_fleets(int fleetId1, int fleetId2);

	StatusType pirate_argument(int pirateId1, int pirateId2);

	double getValue(int id)
	{
		// auto it=this->findHead(id);
		auto it = array->find(id);
		double res = 0;
		while (it != nullptr)
		{
			res += it->extra;
			it = it->father;
		}
		return res;
	};
};

#endif // PIRATESA2_H_
