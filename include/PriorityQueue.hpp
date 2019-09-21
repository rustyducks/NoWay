#include "Node.hpp"

#include <iostream>

// For sorting the heap the STL needs compare function that lets us compare
// the f value of two nodes

class HeapCompare_f 
{
	public:

		bool operator() ( const noway::NodePtr x, const noway::NodePtr y ) const
		{
			if(x->g() + x->h() > y->g() + y->h())
				return true;

			if(x->g() + x->h() < y->g() + y->h())
				return false;
			// We break ties among vertices with the same
			// f-values in favor of larger g-values
			if(x->g() + x->h() == y->g() + y->h())
			{
				if(x->g() > y->g())
					return true;
				else
					return false;

			}
			return false;
		}
};
