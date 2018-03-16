#include "OpenAddMap.h"

OpenAddMap::OpenAddMap(const ProbingScheme pScheme)
{
	_pScheme = pScheme;
	_mSize = 2;
	_numElem = 0;
	_hashmap.reserve(_mSize);

	_hashmap.push_back(FREE);
	_hashmap.push_back(FREE);
}

unsigned OpenAddMap::linear_hash(unsigned const int k, unsigned i)
{
	return ((k % _mSize)+i) % _mSize;
}

unsigned OpenAddMap::quadratic_hash(unsigned const int k, unsigned i)
{
	unsigned c1 = 2;
	unsigned c2 = 7;

	return ((k % _mSize) + (c1*i) + ((c2^2)*i)) % _mSize;
}

unsigned OpenAddMap::double_hash(unsigned const int k, unsigned i)
{
	return ((k % _mSize) + (1+(k % (_mSize-1)))*i) % _mSize;
}

unsigned OpenAddMap::GetHashKey(unsigned const int k, unsigned i)
{
	unsigned hashVal = 0;

	if(_pScheme == ProbingScheme::LINEAR)
	{
		hashVal = linear_hash(k, i);
	}
	else if(_pScheme == ProbingScheme::QUADRATIC)
	{
		hashVal = quadratic_hash(k, i);
	}
	else if(_pScheme == ProbingScheme::DOUBLE)
	{
		hashVal = double_hash(k, i);
	}
	else
	{
		std::cout << "(╯°□°）╯︵ ┻━┻" << std::endl;
	}

	return hashVal;
}

void OpenAddMap::resize()
{
	double resize_factor = 1;

	if(((double)_numElem / (double)_mSize) >= 0.75)
	{
		resize_factor = 2;
	}
	else if(((double)_numElem / (double)_mSize) <= 0.25)
	{
		resize_factor = 0.5;
	}
	else
	{
		return;
	}

	std::vector<unsigned> old_map(_hashmap);

    std::vector<unsigned> nVec;
	_hashmap = nVec;
	_hashmap.reserve((_mSize*resize_factor)-1);
	_mSize = (_mSize*resize_factor)-1;

	for(unsigned i = 0; i < _mSize; i++)
	{
        _hashmap.push_back(FREE);
	}

	for(unsigned k : old_map)
	{
		if(k != FREE && k != DELETED)
		{
            unsigned counter = 0;
            unsigned hashVal;

            do
            {
                hashVal = GetHashKey(k, counter);
                counter++;
            }
            while(_hashmap[hashVal] != FREE);

            _hashmap[hashVal] = k;
		}
	}
}

bool OpenAddMap::insert(unsigned const int k)
{
    if(find(k))
        return false;

	unsigned counter = 0;
	unsigned hashVal;

	do
	{
		hashVal = GetHashKey(k, counter);
		counter++;
	}
	while(_hashmap[hashVal] != FREE);

	_hashmap[hashVal] = k;
	_numElem++;
	resize();

	return true;
}

bool OpenAddMap::find(unsigned const int k)
{
    probeCounter.push_back(0);

	unsigned counter = 0;
	unsigned hashVal;

	do
	{
        probeCounter[probeCounter.size()-1]++;

		hashVal = GetHashKey(k, counter);

		if(_hashmap[hashVal] == k)
		{
			return true;
		}
		counter++;
	}
	while(_hashmap[hashVal] != FREE);

	return false;
}

bool OpenAddMap::remove(unsigned const int k)
{
    if(!find(k))
        return false;

	unsigned counter = 0;
	unsigned hashVal;

	do
	{
		hashVal = GetHashKey(k, counter);

		if(_hashmap[hashVal] == k)
		{
			_hashmap[hashVal] = DELETED;
			resize();
			_numElem--;
			return true;
		}
		counter++;
	}
	while(_hashmap[hashVal] != FREE);

	return false;
}

size_t OpenAddMap::size() const
{
	return _mSize;
}

size_t OpenAddMap::numElem() const
{
	return _numElem;
}

void OpenAddMap::visualise()
{
    for(unsigned k : _hashmap)
    {
        if(k == FREE)
            std::cout << "|-|" << std::endl;
        else if(k == DELETED)
            std::cout << "|O|" << std::endl;
        else
            std::cout << "|X|" << std::endl;
    }
}

void OpenAddMap::avgProbes()
{
    unsigned sumProbes = 0;

    for(unsigned i : probeCounter)
    {
        sumProbes += i;
    }

    std::cout << "AvgProbes: " << (double)sumProbes/(double)probeCounter.size() << std::endl;
}


void OpenAddMap::printProbeVec()
{
    for(unsigned i : probeCounter)
    {
        std::cout << i << std::endl;
    }
}







