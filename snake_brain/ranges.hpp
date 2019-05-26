#pragma once
#include <forward_list>

template<typename Iterator, typename Sentinel = Iterator>
class range
{
	Iterator first;
	Sentinel last;

public:
	range(Iterator first, Sentinel last) : first{ first }, last{ last } {}

	Iterator begin() const { return first; }
	Iterator cbegin() const { return begin(); }

	Sentinel end() const { return last; }
	Sentinel cend() const { return end(); }
};

template<typename Container>
auto make_range(Container&& container)
{
	return range{ begin(std::forward<Container>(container)), end(std::forward<Container>(container)) };
}

template<typename Container>
auto make_reverse_range(Container&& container)
{
	return range{ rbegin(std::forward<Container>(container)), rend(std::forward<Container>(container)) };
}