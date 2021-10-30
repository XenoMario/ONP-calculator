#include <gtest/gtest.h>
#include "Stack.inl"

struct StactTest : public testing::Test // Fixtura
{
	Stack<int> st;

	void SetUp() override
	{

	}

	void TearDown() override
	{
		st.clean();
	}
};

// Makro - (np. #define) dyrektywna preprocesora

TEST_F(StactTest, given_emptyStack_when_addingNewElement_then_ElementIsAdded)
{
	st.push(1);

	EXPECT_FALSE(st.isempty());
}

TEST_F(StactTest, given_StachWithThreeElements_when_Peeked_then_ElementsAreCorrect)
{
	st.push(1);
	st.push(2);
	st.push(3);

	int x = st.pop();
	EXPECT_EQ(3, x);
	x = st.pop();
	EXPECT_EQ(2, x);
	x = st.pop();
	EXPECT_EQ(1, x);
}

