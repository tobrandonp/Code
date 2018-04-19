#include <cassert>
#include <iostream>
#include <vector>

 #include <boost/type_traits.hpp>

template<class Derived, class ROWS_TYPE_1, class ROWS_TYPE_2, class ROWS_TYPE_3>
class Base
{
public:
	template <class GP_ROW_TYPE>
	void addGrandparentRow(GP_ROW_TYPE& grandparentRow)
	{
		assert((boost::is_same<GP_ROW_TYPE,ROWS_TYPE_1>::value));
		m_rows1.push_back(grandparentRow);
		std::cout << "val is " << m_rows1.at(0) << std::endl;
	}

	template<class PARENT_ROW_TYPE>
	void addParentRow(uint index, const PARENT_ROW_TYPE& parentRow)
	{
		static_cast<Derived*>(this)->addParentRow(index, parentRow);
	}

	virtual ~Base(){}

protected:
    std::vector<ROWS_TYPE_1> m_rows1;
	std::vector<ROWS_TYPE_2> m_rows2;
	std::vector<ROWS_TYPE_3> m_rows3;
};

// Grandparent
template <class T1, class T2, class T3>
class Grandparent : public Base<Grandparent<T1,T2,T3>, T1, T2, T3>
{

public:
	Grandparent()
	{
	}

	template<class PARENT_ROW_TYPE>
	void addParentRow(uint index, const PARENT_ROW_TYPE& parentRow)
	{
		std::cout << "Error: Attempt to add parent row to Grandparent BulkInserter" << std::endl;
	}
};

// Grandparent - Parent, Parent
template <class T1, class T2, class T3>
class GrandparentTwoParents : public Base<GrandparentTwoParents<T1,T2,T3>, T1, T2, T3>
{

public:
	GrandparentTwoParents()
	{
	}

	template<class PARENT_ROW_TYPE>
	void addParentRow(uint index, const PARENT_ROW_TYPE& parentRow)
	{
		if (index == 0)
		{
			Base<GrandparentTwoParents<T1,T2,T3>, T1, T2, T3>::m_rows2.push_back(parentRow);
		}
		else if (index == 1)
		{
			Base<GrandparentTwoParents<T1,T2,T3>, T1, T2, T3>::m_rows3.push_back(parentRow);
		}
	}
};

// Grandparent - Parent - Child
template <class T1, class T2, class T3>
class GrandparentParentChild : public Base<GrandparentParentChild<T1,T2,T3>, T1, T2, T3>
{

public:
	GrandparentParentChild()
	{
	}


	template<class PARENT_ROW_TYPE>
	void addParentRow(uint index, const PARENT_ROW_TYPE& parentRow)
	{
		if (index == 0)
		{
			assert((boost::is_same<PARENT_ROW_TYPE,T2>::value));
			Base<GrandparentParentChild<T1,T2,T3>, T1, T2, T3>::m_rows2.push_back(parentRow);
		}
		else
		{
			std::cout << "Error: wrong parent index for GrandparentParentChild Table Chain type" << std::endl;
		}
	}
};



//template <class BulkInsertRowsType, class T1, class T2, class T3>

template <class T> 
class BulkInserter
{
public:

    template<class GP_TYPE>
	void addGrandparentRow(GP_TYPE& grandparentRow)
	{
		rows.addGrandparentRow(grandparentRow);
	}
	template<class PARENT_ROW_TYPE>
	void addParentRow(uint index, const PARENT_ROW_TYPE& parentRow)
	{
		rows.addParentRow();
	}
	T rows;
};