#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "forwardList.h"

namespace dmitriev
{
	template< typename Key, typename Value, typename Compare = std::less< > >
	class Dictionary
	{
	public:
		using fList = ForwardList< std::pair< Key, Value > >;
		using iterator = typename fList::iterator;
		using constIterator = typename fList::constIterator;

		Dictionary():
			m_fList(),
			m_comp()
		{}
		Dictionary(const Dictionary& other):
			m_fList(other.m_flist),
			m_comp(other.m_comp)
		{}
		Dictionary(Dictionary&& other):
			m_fList(other.m_fList),
			m_comp(other.m_comp)
		{}

		~Dictionary() = default;

		void push(Key k, const Value& v)
		{
			iterator it = lowerBound(k);
			iterator movedIt = it;

			movedIt++;

			if (movedIt == end())
			{
				m_fList.insertAfter(it, std::pair< Key, Value >{k, v});
			}
			else if (movedIt->first == k)
			{
				movedIt->second = v;
			}
			else
			{
				m_fList.insertAfter(it, std::pair< Key, Value >{k, v});
			}
		}
		Value get(Key k)
		{
			iterator it = find(k);

			return it->second;
		}

		iterator slowerBound(const Key& key)
		{
			iterator result = beforeBegin();

			for(iterator it = begin(); it != end() && m_comp(it->first, key); it++, result++)
			{}

			return result;
		}
		constIterator lowerBound(const Key& key) const
		{
			constIterator result = const_cast< const Dictionary< Key, Value, Compare >* >(this)->slowerBound(key);
			return result;
		}


		iterator beforeBegin()
		{
			return m_fList.beforeBegin();
		}
		iterator begin()
		{
			return m_fList.begin();
		}
		iterator end()
		{
			return m_fList.end();
		}

		constIterator constBeforeBegin()
		{
			return m_fList.constBeforeBegin();
		}
		constIterator constBegin()
		{
			return m_fList.constBegin();
		}
		constIterator constEnd()
		{
			return m_fList.constEnd();
		}

		iterator find(Key k)
		{
			iterator result = begin();
			for (; result != end() && m_comp(result->first, k); result++)
			{}
			
			return result;
		}

	private:
		fList m_fList;
		Compare m_comp;

	};
}

#endif

//template< typename Key, typename Value, typename Compare >
//class Dictionary;
//
//template< typename Key, typename Value, typename Compare >
//class ConstDictionaryIterator;
//
//template< typename Key, typename Value, typename Compare >
//class DictionaryIterator
//{
//	friend ConstDictionaryIterator;
//	friend Dictionary;
//
//	DictionaryIterator():
//		fIterator()
//	{}
//	DictionaryIterator(const ForwardList< std::pair< Key, Value > >::iterator& it):
//		fIterator(it)
//	{}
//
//	DictionaryIterator& operator++()
//	{
//		fIterator++;
//		return *this;
//	}
//	DictionaryIterator& operator++(int)
//	{
//		return DictionaryIterator(++fIterator);
//	}
//
//	DictionaryIterator& operator*()
//	{
//		return fIterator.operator*();
//	}
//	DictionaryIterator& operator->()
//	{
//		return ForwardIterator.operator->();
//	}
//
//	bool operator==(const DictionatyIterator& other)
//	{
//		return (fIterator == other.fIterator);
//	}
//	bool operator!=(const DictionatyIterator& other)
//	{
//		return !(*this == other);
//	}
//
//private:
//	ForwardList< std::pair< Key, Value > >::iterator fIterator;
//
//};
//
//template< typename Key, typename Value, typename Compare >
//class ConstDictionaryIterator
//{
//	friend Dictionary;
//
//	ConstDictionaryIterator():
//		cFIterator()
//	{}
//	ConstDictionaryIterator(ForwardList< std::pair< Key, Value > >::constIterator& it):
//		cFIterator(it)
//	{}
//
//	ConstDictionaryIterator& operator++()
//	{
//		cFIterator++;
//		return *this;
//	}
//	ConstDictionaryIterator& operator++(int)
//	{
//		return ConstDictionaryIterator(++cFIterator);
//	}
//
//	ConstDictionaryIterator& operator*() const
//	{
//		return cFIterator.operator*();
//	}
//	ConstDictionaryIterator& operator->() const
//	{
//		return cFIterator.operator->();
//	}
//
//	bool operator==(const DictionatyIterator& other) const
//	{
//		return (cFIterator == other.cFIterator);
//	}
//	bool operator!=(const DictionatyIterator& other) const
//	{
//		return !(*this == other);
//	}
//
//private:
//	ForwardList< std::pair< Key, Value > >::constIterator cFIterator;
//
//};