#ifndef ITERABLE_H
#define ITERABLE_H

class FilterIterator
{
public:
	virtual ~FilterIterator() = 0;
};

template <typename TIterator, typename TConstIterator, typename TFilterIterator>
class Iterable
{
public:
	virtual TIterator begin() = 0;
	virtual TIterator end() = 0;
	virtual TConstIterator begin() const = 0;
	virtual TConstIterator end() const = 0;

	virtual TFilterIterator filter(bool(*pred)(typename TFilterIterator::value_type)) = 0;
};

#endif