#pragma once
#include "..\lib_stack\stack.h"

bool check_breckets(std::string str)
{
	TStack<char> staples;
	for (char c : str)
	{
		if (c == '(' || c == '[' || c == '{') staples.push(c);
		else if (c == ')' || c == ']' || c == '}')
		{
			if (staples.is_empty()) throw std::invalid_argument("Missing opened brecket");
			if ((staples.top() == '(' && c == ')')
				|| staples.top() == '[' && c == ']'
				|| staples.top() == '{' && c == '}')
				staples.pop();
			else
			{
				throw std::invalid_argument("Missing opened brecket");
				return false;
			}
		}

	}
	if (!staples.is_empty())
	{
		throw std::invalid_argument("Missing closed brecket");
		return false;
	}
	return true;
}