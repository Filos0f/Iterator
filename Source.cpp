#include <iostream>
#include <algorithm>
#include "Tests.h"
#include "Number.h"
#include "Map.h"
#include "File.h"
#include <bitset> 
#include <string>

template <typename TSequance>
void ShowSequaence(const TSequance& obj, char separator = ' ')
{
	for (auto s : obj)
	{
		std::cout << s << separator;
	}
	std::cout << std::endl;
}

int main()
{
	Number<unsigned int> n(123);
	ShowSequaence(n);

	Number<unsigned int>::iterator itemN = std::find(n.begin(), n.end(), (bool)1);
	std::cout << *itemN << std::endl;
	*itemN = !*itemN;
	std::cout << "Found: " << *itemN << std::endl;

	Number<unsigned int>::filter_iterator filtIter = n.filter([](bool obj)
	{
		return obj == 0 ? false : true;
	});
	std::cout << *filtIter++ << std::endl;
	std::cout << *filtIter++ << std::endl;
	std::cout << *filtIter++ << std::endl;
	std::cout << *filtIter << std::endl;
	
	std::bitset<32> b(123);
	std::bitset<32>::reference& r = b[1];
	r = !r;
	std::cout << b.to_ulong() << std::endl;

	std::cout << "==================MAP==============\n";

	Map<Region<int> > m;
	m.addRegion(Region<int>("LA", Coords<int>(34, -118)));
	m.addRegion(Region<int>("LA1", Coords<int>(1, 18)));
	m.addRegion(Region<int>("LA2", Coords<int>(2, -118)));
	m.addRegion(Region<int>("LA3", Coords<int>(3, -118)));

	ShowSequaence(m);
	
	Region<int> toFind("LA1", Coords<int>(1, 18));
	Map<Region<int> >::iterator itemM = std::find(m.begin(), m.end(), toFind);
	std::cout << "Found: " << *itemM << std::endl;

	Map<Region<int> >::filter_iterator filtMapIter =
		m.filter([](Region<int> obj)
	{
		return obj.name == "LA1" ? false : true; 
	});

	std::cout << *filtMapIter++ << std::endl;
	std::cout << *filtMapIter++ << std::endl;
	std::cout << *filtMapIter++ << std::endl;

	std::cout << "==================FILE==============\n";

	File f("text.txt");
	ShowSequaence(f, '\n');

	File::iterator itemF = std::find(f.begin(), f.end(), "3.black");
	std::cout << "Found: " << *itemF << std::endl;

	File::filter_iterator filtFileIter =
		f.filter([](line obj)
	{
		return obj == "4.red" ? false : true;
	});

	std::cout << *filtFileIter++ << std::endl;
	std::cout << *filtFileIter++ << std::endl;
	std::cout << *filtFileIter++ << std::endl;

	return 0;
}

