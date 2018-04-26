#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <bitset> 
#include "Iterable.h"

#define BIT_SIZE 8

template <class T>
class iterator
{
public:
	typedef iterator self_type;
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef std::forward_iterator_tag iterator_category;
	typedef int difference_type;

	iterator(T N, size_t index)
		: bit(N), index(index)
	{}
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
	std::bitset<32>::reference operator*()
	{
		return bit.at(index);
	}
	std::bitset<32>::reference* operator->()
	{
		return &bit.at(index);
	}
	bool operator==(const self_type& rhs)
	{
		return (this->bit == rhs.bit) && this->index == rhs.index;
	}
	bool operator!=(const self_type& rhs)
	{
		return !(*this == rhs);
	}
private:
	std::bitset<sizeof(T)* BIT_SIZE> bit;
	int index;
};

template <class T>
class const_iterator
{
public:
	typedef const_iterator self_type;
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef int difference_type;
	typedef std::forward_iterator_tag iterator_category;

	const_iterator(T N, size_t index)
		: bit(N), index(index)
	{}

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
	std::bitset<32>::reference operator*()
	{
		return bit[index];
	}
	std::bitset<32>::reference* operator->()
	{
		return &bit[index];
	}
	bool operator==(const self_type& rhs)
	{
		return (this->bit == rhs.bit) && this->index == rhs.index;
	}
	bool operator!=(const self_type& rhs)
	{
		return !(*this == rhs);
	}
private:
	std::bitset<sizeof(T)* BIT_SIZE> bit;
	int index;
};

template <class T>
class NumberFilterIterator
{
public:

	typedef NumberFilterIterator self_type;
	typedef bool value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef std::forward_iterator_tag iterator_category;
	typedef int difference_type;

	NumberFilterIterator(T N, size_t index, bool(*predicate)(bool))
		: bit(N), index(index)
	{
		this->predicate = predicate;
	}

	self_type operator++()
	{
		self_type i = *this;
		index++;
		if (index == bit.size())
			return *this;
		while (!predicate(bit.at(index)))
			index++;
		return i;
	}
	self_type operator++(int junk)
	{
		index++;
		if (index == bit.size())
			return *this;
		while (!predicate(bit.at(index)))
			index++;
		return *this;
	}
	std::bitset<32>::reference operator*()
	{
		if (index == bit.size())
			return bit.at(0);
		return bit.at(index);
	}
	std::bitset<32>::reference* operator->()
	{
		if (index == bit.size())
			return &bit.at(0);
		return &bit.at(index);
	}
	bool operator==(const self_type& rhs)
	{
		return (this->bit == rhs.bit) && this->index == rhs.index;
	}
	bool operator!=(const self_type& rhs)
	{
		return !(*this == rhs);
	}
private:
	bool(*predicate)(bool);
	std::bitset<sizeof(T)* BIT_SIZE> bit;
	int index;
};

template <typename T>
class Number : public Iterable<iterator<T>, const_iterator<T>, NumberFilterIterator<T> >
{
	T N;
public:

	typedef T size_type;
	typedef iterator<T> iterator;
	typedef const_iterator<T> const_iterator;
	typedef NumberFilterIterator<T> filter_iterator;


	Number(T N)
		:N(N)
	{
	}

	void SetNumber(unsigned int N)
	{
		this->N = N;
	}

	filter_iterator filter(bool(*predicate)(typename filter_iterator::value_type))
	{
		return filter_iterator(this->N, 0, predicate);
	}

	iterator begin()
	{
		return iterator(N, 0);
	}

	const_iterator begin() const
	{
		return const_iterator(N, 0);
	}

	iterator end()
	{
		return iterator(N, 32);
	}

	const_iterator end() const
	{
		return const_iterator(N, 32);
	}
};

#endif