#include "State.hpp"

State* State::next()
{
	return m_next;
}

bool State::finished()
{
	return m_finished;
}

bool State::remove()
{
	return m_remove;
}