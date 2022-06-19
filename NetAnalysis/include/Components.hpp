#pragma once
#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP
#include <networkit/components/ConnectedComponents.hpp>
#include "GraphAnalyzer.hpp"

namespace NetAnalysis::Routines
{

	template<typename T>
	void ShowComponentsResult(T& algorithm)
	{
		static_assert(std::is_convertible<T*, NetworKit::ComponentDecomposition*>::value);


	}


	void ExecuteComponentsAnalysis(GraphAnalyzer* analyzer)
	{
		
	}
}



#endif