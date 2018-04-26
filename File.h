#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <bitset> 
#include <fstream>
#include <string>
#include "Iterable.h"

class line : public std::string {};

static std::istream &operator>>(std::istream &is, line &l)
{
	std::getline(is, l);
	return is;
}


class FileIterator
{
public:
	typedef FileIterator self_type;
	typedef line value_type;
	typedef line& reference;
	typedef line* pointer;
	typedef std::forward_iterator_tag iterator_category;
	typedef int difference_type;

	FileIterator(std::istream_iterator<line> N)
		: iter(N)
	{}

	self_type operator++()
	{
		self_type i = *this;
		++iter;
		return i;
	}
	self_type operator++(int junk)
	{
		++iter;
		return *this;
	}
	value_type operator*()
	{
		return *iter;
	}
	value_type operator->()
	{
		return *iter;
	}
	bool operator==(const self_type& rhs)
	{
		return this->iter == rhs.iter;
	}
	bool operator!=(const self_type& rhs)
	{
		return !(*this == rhs);
	}
private:
	std::istream_iterator<line> iter;
};


class ConstFileIterator
{
public:
	typedef ConstFileIterator self_type;
	typedef line value_type;
	typedef line& reference;
	typedef line* pointer;
	typedef int difference_type;
	typedef std::forward_iterator_tag iterator_category;

	ConstFileIterator(std::istream_iterator<line> N)
		: iter(N)
	{}

	self_type operator++()
	{
		self_type i = *this;
		++iter;
		return i;
	}
	self_type operator++(int junk)
	{
		++iter;
		return *this;
	}
	value_type operator*()
	{
		return *iter;
	}
	value_type operator->()
	{
		return *iter;
	}
	bool operator==(const self_type& rhs)
	{
		return this->iter == rhs.iter;
	}
	bool operator!=(const self_type& rhs)
	{
		return !(*this == rhs);
	}
private:
	std::istream_iterator<line> iter;
};

class FileFilterIterator
{
public:

	typedef FileFilterIterator self_type;
	typedef line value_type;
	typedef line const& reference;
	typedef line* pointer;
	typedef std::forward_iterator_tag iterator_category;
	typedef int difference_type;

	FileFilterIterator(std::istream_iterator<line> N, bool(*predicate)(line))
		: iter(N)
	{
		this->predicate = predicate;
	}

	self_type operator++()
	{
		++iter;
		self_type i = *this;
		while (!predicate(*iter))
			++iter;
		return i;
	}
	self_type operator++(int junk)
	{
		++iter;
		while (!predicate(*iter))
			++iter;
		return *this;
	}
	value_type operator*()
	{
		return *iter;
	}
	value_type operator->()
	{
		return *iter;
	}
	bool operator==(const self_type& rhs)
	{
		return this->iter == rhs.iter;
	}
	bool operator!=(const self_type& rhs)
	{
		return !(*this == rhs);
	}
private:
	bool(*predicate)(line);
	std::istream_iterator<line> iter;
};

class File : public Iterable<FileIterator, ConstFileIterator, FileFilterIterator >
{
	std::string filename;
	mutable std::ifstream infile;
public:

	typedef std::string size_type;
	typedef FileIterator iterator;
	typedef ConstFileIterator const_iterator;
	typedef FileFilterIterator filter_iterator;

	File()
	{

	}
	File(const std::string& fileName)
		: filename(fileName)
	{
		infile.open(filename);
	}

	~File()
	{
		infile.close();
	}

	filter_iterator filter(bool(*predicate)(filter_iterator::value_type))
	{
		infile.clear();
		infile.seekg(0, std::ios::beg);
		return filter_iterator(std::istream_iterator<line>(infile), predicate);
	}

	void SetFile(const std::string& fileName)
	{
		if (infile.is_open())
		{
			infile.close();
		}
		this->filename = fileName;
		infile.open(filename);
	}

	iterator begin()
	{
		infile.clear();
		infile.seekg(0, std::ios::beg);
		return iterator(std::istream_iterator<line>(infile));
	}
	const_iterator begin() const
	{
		infile.clear();
		infile.seekg(0, std::ios::beg);
		return const_iterator(std::istream_iterator<line>(infile));
	}

	iterator end()
	{
		return iterator(std::istream_iterator<line >());
	}
	const_iterator end() const
	{
		return const_iterator(std::istream_iterator<line >());
	}
};

#endif