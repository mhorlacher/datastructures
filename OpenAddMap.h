#ifndef OPEN_ADD_MAP_H
#define OPEN_ADD_MAP_H

#include <iostream>
#include <vector>
#include <string>

class OpenAddMap
{
private:
	//std::vector<unsigned> _hashmap;
	std::vector<unsigned> _hashmap;
	unsigned _mSize;
	unsigned _numElem;

	unsigned FREE = -1;
	unsigned DELETED = -2;

	unsigned linear_hash(unsigned const int, unsigned);
	unsigned quadratic_hash(unsigned const int, unsigned);
	unsigned double_hash(unsigned const int, unsigned);

	unsigned GetHashKey(unsigned const int, unsigned);

	void printArray(unsigned[]);


	void resize();

	std::vector<unsigned> probeCounter;


public:
    // defines which probing scheme are available
    enum class ProbingScheme : uint8_t
    {
        LINEAR,
        QUADRATIC,
        DOUBLE
    };
    ProbingScheme _pScheme;

    // Constructor, takes a ProbingScheme as argument
    OpenAddMap(const ProbingScheme);
    //OpenAddMap(std::string);

    // returns the size (reserved slots) of the table.
    size_t size() const;
    // returns the number of elements currently in the table (not including NIL markers)
    size_t numElem() const;

    // insert a new element into the table. On success return true.
    // If element was already in the table return false.
    bool insert(unsigned const int);

    //search for entry in the table. If found return true otherwise false.
    bool find(unsigned const int);

    // delete entry from table. If deleted return true.
    // If element was not in the table return false.
    bool remove(unsigned const int);

    void visualise();
    void avgProbes();
    void printProbeVec();
};

#endif /* OPEN_ADD_MAP_H */
