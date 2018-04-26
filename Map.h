#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <bitset> 
#include "Iterable.h"

#define BIT_SIZE 8

template <class T>
class MapIterator
{
public:
	typedef MapIterator self_type;
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef std::forward_iterator_tag iterator_category;
	typedef int difference_type;

	MapIterator(std::vector<T>& d, int N)
		:data(d), index(N)
	{
	}

	MapIterator(const MapIterator<T>& obj)
		:data(obj.data), index(obj.index)
	{
	}

	self_type& operator=(const MapIterator<T>& obj)
	{
		data = obj.data;
		index = obj.index;
		return *this;
	}

	self_type operator++()
	{
		self_type i = *this;
		index++;
		return i;
	}
	self_type operator++(int junk)
	{
		index++;
		return *this;
	}
	const reference operator*()
	{
		return data[index];
	}
	const pointer operator->()
	{
		return &data[index];
	}
	bool operator==(const self_type& rhs)
	{
		return index == rhs.index;
	}
	bool operator!=(const self_type& rhs)
	{
		return !(*this == rhs);
	}
private:
	std::vector<T>& data;
	int index;
};

template <class T>
class ConstMapIterator
{
public:
	typedef ConstMapIterator self_type;
	typedef T value_type;
	typedef T const& reference;
	typedef T const* pointer;
	typedef int difference_type;
	typedef std::forward_iterator_tag iterator_category;

	ConstMapIterator(const std::vector<T>& d, int N)
		:data(d), index(N)
	{
	}

	ConstMapIterator(const ConstMapIterator<T>& obj)
		:data(obj.data), index(obj.index)
	{
	}

	self_type operator++()
	{
		self_type i = *this;
		index++;
		return i;
	}
	self_type operator++(int junk)
	{
		index++;
		return *this;
	}
	reference operator*()
	{
		return data[index];
	}
	pointer operator->()
	{
		return &data[index];
	}
	bool operator==(const self_type& rhs)
	{
		return index == rhs.index;
	}
	bool operator!=(const self_type& rhs)
	{
		return !(*this == rhs);
	}
private:
	const std::vector<T>& data;
	int index;
};

template <class T>
class MapFilterIterator
{
public:

	typedef MapFilterIterator self_type;
	typedef T value_type;
	typedef T const& reference;
	typedef T* pointer;
	typedef std::forward_iterator_tag iterator_category;
	typedef int difference_type;

	MapFilterIterator(const std::vector<T>& d, int N, bool(*predicate)(T))
		: data(d), index(N)
	{
		this->predicate = predicate;
	}

	self_type operator++()
	{
		index++;
		if (index == data.size())
			return *this;
		self_type i = *this;
		while (!predicate(data[index]))
			index++;
		return i;
	}
	self_type operator++(int junk)
	{
		index++;
		if (index == data.size())
			return *this;
		while (!predicate(data[index]))
			index++;
		return *this;
	}
	reference operator*()
	{
		if (index == data.size())
			return data[0];
		return data[index];
	}
	pointer operator->()
	{
		if (index == data.size())
			return &data[0];
		return &data[index];
	}
	bool operator==(const self_type& rhs)
	{
		return index == rhs.index;
	}
	bool operator!=(const self_type& rhs)
	{
		return !(*this == rhs);
	}
private:
	bool(*predicate)(T);
	const std::vector<T>& data;
	int index;
};

template <typename T>
struct Coords
{
	T latitude;
	T longitude;

	Coords(T lat, T lon)
		:latitude(lat), longitude(lon)
	{}

	bool operator==(const Coords<T>& cord) const
	{
		return latitude == cord.latitude && longitude == cord.longitude;
	}
};

template <typename T>
struct Region
{
	std::string name;
	std::vector<Coords<T> > coords;

	Region(std::string name, Coords<T> crd) :name(name)
	{
		this->coords.push_back(crd);
	}

	bool operator==(const Region<T>& reg)
	{
		return name == reg.name && coords == reg.coords;
	}
};

template < typename T >
std::ostream& operator<<(std::ostream& out, const Region<T>& reg)
{
	out << reg.name << std::endl;
	for (std::vector<Coords<T> >::const_iterator it = reg.coords.begin();
		it != reg.coords.end();
		++it)
	{
		out << it->latitude << " " << it->longitude << "\n";
	}
	return out;
}

template <typename TRegion>
class Map : public Iterable<MapIterator<TRegion>, ConstMapIterator<TRegion>, MapFilterIterator<TRegion> >
{
private:
	std::vector<TRegion> regions;
public:

	typedef TRegion size_type;
	typedef MapIterator<TRegion> iterator;
	typedef ConstMapIterator<TRegion> const_iterator;
	typedef MapFilterIterator<TRegion> filter_iterator;

	Map()
	{

	}
	Map(TRegion rgn)
	{
		this->regions.push_back(rgn);
	}

	void addRegion(TRegion rgn)
	{
		this->regions.push_back(rgn);
	}

	filter_iterator filter(bool(*predicate)(typename filter_iterator::value_type))
	{
		return filter_iterator(regions, 0, predicate);
	}

	iterator begin()
	{
		return iterator(regions, 0);
	}
	const_iterator begin() const
	{
		return const_iterator(regions, 0);
	}

	iterator end()
	{
		return iterator(regions, regions.size());
	}
	const_iterator end() const
	{
		return const_iterator(regions, regions.size());
	}
};

#endif