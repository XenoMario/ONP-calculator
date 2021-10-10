#include <gtest/gtest.h>
#include "Stack.inl"

TEST(STACK_TESTS, given_emptyStack_when_addingNewElement_then_ElementIsAdded)
{
	Stack<int> st;
	st.push(1);

	EXPECT_FALSE(st.isempty());
}
