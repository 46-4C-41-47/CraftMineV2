#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <vector>


class AppSql
{
public:
	template<typename T>
	static std::set<T> UNION(std::set<T> A, std::set<T> B)
	{
		std::set<T> result;

		for (const T& element : A)
			result.insert(element);

		for (const T& element : B)
			result.insert(element);

		return result;
	}


	template<typename T>
	static std::set<T> INTERSECT(std::set<T> A, std::set<T> B)
	{
		std::set<T> result;

		for (const T& element : A)
			if (B.contains(element))
				result.insert(element);

		return result;
	}


	template<typename T>
	static std::set<T> EXCEPT(std::set<T> A, std::set<T> B)
	{
		std::set<T> result;

		for (const T& element : A)
			if (!B.contains(element))
				result.insert(element);

		return result;
	}


	template<typename T>
	static std::set<T> OUTER(std::set<T> A, std::set<T> B)
	{
		std::set<T> result;

		for (const T& element : A)
			if (!B.contains(element))
				result.insert(element);

		for (const T& element : B)
			if (!A.contains(element))
				result.insert(element);

		return result;
	}


	template<typename T>
	static std::set<T> WHERE(
		std::set<T> A, std::set<T> B, 
		std::function<bool(T elementA, T elementB)> condition
	) {
		std::set<T> result;

		for (const T& elementA : A)
			for (const T& elementB : B)
				if (condition(elementA, elementB))
					result.insert(elementA);

		return result;
	}


	template<typename T>
	static std::set<T> toSet(const std::vector<T>& vector)
	{
		std::set<T> set;

		for (const T& element : vector)
			set.insert(element);

		return set;
	}


	template<typename K, typename V>
	static std::set<K> getKeys(const std::map<K, V>& map)
	{
		std::set<K> keys;

		for (const auto& [key, value] : map)
			keys.insert(key);

		return keys;
	}
};
