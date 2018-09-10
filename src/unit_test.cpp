#include <gtest/gtest.h>
#include "node.h"

template< typename itemType >
class node_test : public ::testing::Test {

};
using itemType_test = ::testing::Types< int , double , unsigned >;
TYPED_TEST_CASE( node_test , itemType_test );

TYPED_TEST( node_test , constructor ) {
    node< TypeParam > n( 10 );
    EXPECT_EQ( 10 , n.getData() );
    EXPECT_EQ( 1 , n.getHeight() );
    EXPECT_EQ( n.getLeftChild() , nullptr );
    EXPECT_EQ( nullptr , n.getRightChild() );
}

GTEST_API_ int main( int argc , char **argv ) {
	testing::InitGoogleTest( &argc , argv );
	return RUN_ALL_TESTS();
}
