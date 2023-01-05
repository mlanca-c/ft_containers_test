/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_Rb_tree.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlancac </var/spool/mail/mlancac>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:21:53 by mlancac           #+#    #+#             */
/*   Updated: 2023/01/04 15:34:02 by mlancac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* Headers                                                                    */
/* ************************************************************************** */

#define GTEST 1

#include "ft_containers.hpp"

#include <gtest/gtest.h>
#include <iostream>
#include <map>

/* ************************************************************************** */
/* Class                                                                      */
/* ************************************************************************** */

#if LIB == FT

# define RESET  "\033[0m"
# define BLACK  "\033[1m\033[30m"
# define RED    "\033[1m\033[31m"
# define YELLOW "\033[1m\033[33m"

class test_Rb_tree : public ::testing::Test {

    public:

        typedef ft::pair<int, int>              value_type;
        typedef typename value_type::first_type key_type;

        struct _key_value {

                key_type operator()( value_type const& rhs ) const {
                    return ( rhs.first );
                }
        };

        typedef ft::Rb_tree< key_type, value_type, _key_value,
                             std::less<key_type> >
            Tree;

        void SetUp( void ) {}

        void TearDown( void ) { this->verify(); }

        void verify( void ) { ASSERT_TRUE( this->t.rb_verify() ); }

        void Print( Tree x ) { this->Print( x.header.parent, "|  ", 0 ); }

        void Print( ft::Rb_tree_node<value_type>* root, std::string indent,
                    int left ) {

            if ( !root ) { return; }

            std::cout << indent;
            if ( !left ) {
                std::cout << "ROOT--";
                indent += "      ";
            }
            else if ( left == 1 ) {
                std::cout << "L-----";
                indent += "|     ";
            }
            else {
                std::cout << "R-----";
                indent += "      ";
            }

            std::cout << root->value_field.first << "["
                      << root->value_field.second << "]";

            std::string color = ( root->color == ft::red ? "R" : "B" );
            std::cout << " ( " << color << " )" << std::endl;

            this->Print( root->left, indent, 1 );
            this->Print( root->right, indent, 2 );
        }

        void AddValues( int n, int increment = 1 ) {

            int val = ( this->t.empty() ? 0 : ( --( this->t.end() ) )->first );
            for ( auto i = 0; i < n; i++ ) {
                val += increment;
                this->t._insert_unique( ft::make_pair( val, val * 2 ) );
            }
        }

    protected:

        Tree t;
};

/* ************************************************************************** */
/* Tests                                                                      */
/* ************************************************************************** */

TEST_F( test_Rb_tree, default_constructor ) {

    typename test_Rb_tree::Tree a;
    ASSERT_EQ(
        typeid( a._alloc ),
        typeid( std::allocator<ft::Rb_tree_node<ft::pair<int, int> > > ) );
    ASSERT_EQ( typeid( a._comp ), typeid( std::less<int> ) );
    ASSERT_EQ( typeid( a.header ),
               typeid( ft::Rb_tree_node<ft::pair<int, int > > ) );
    ASSERT_EQ( a.node_count, 0 );
}

TEST_F( test_Rb_tree, copy_constructor ) {

    this->AddValues( 3 );
    typename test_Rb_tree::Tree a( this->t );

    ASSERT_EQ( typeid( a._alloc ), typeid( this->t._alloc ) );
    ASSERT_EQ( typeid( a._comp ), typeid( this->t._comp ) );
    ASSERT_EQ( typeid( a.header ), typeid( this->t.header ) );
    ASSERT_EQ( a.node_count, 3 );
    ASSERT_EQ( a, this->t );

    this->AddValues( 1 );
    typename test_Rb_tree::Tree b( this->t );

    ASSERT_EQ( typeid( a._alloc ), typeid( b._alloc ) );
    ASSERT_EQ( typeid( a._comp ), typeid( b._comp ) );
    ASSERT_EQ( typeid( a.header ), typeid( b.header ) );
    ASSERT_EQ( b.node_count, 4 );
    ASSERT_TRUE( b == this->t );
}

TEST_F( test_Rb_tree, destructor ) {

    typename test_Rb_tree::Tree* a;
    a = new typename test_Rb_tree::Tree;
    delete a;
    this->AddValues( 3 );
    a = new typename test_Rb_tree::Tree( this->t );
    delete a;
    a = new typename test_Rb_tree::Tree;
    *a = this->t;
    delete a;
}

TEST_F( test_Rb_tree, operator_assignment ) {

    this->AddValues( 3 );
    typename test_Rb_tree::Tree a;
    a = this->t;
    ASSERT_EQ( typeid( a._alloc ), typeid( this->t._alloc ) );
    ASSERT_EQ( typeid( a._comp ), typeid( this->t._comp ) );
    ASSERT_EQ( typeid( a.header ), typeid( this->t.header ) );
    ASSERT_EQ( a.size(), 3 );
    ASSERT_TRUE( a == this->t );
}

TEST_F( test_Rb_tree, key_comp ) {

    ASSERT_EQ( typeid( this->t.key_comp() ), typeid( this->t._comp ) );
}

/* Testing Iterators */
TEST_F( test_Rb_tree, begin ) {

    this->AddValues( 2 );
    ASSERT_EQ( *this->t.begin(), ft::make_pair( 1, 2 ) );
    ASSERT_EQ( typeid( this->t.begin() ),
               typeid( typename ft::Rb_tree_iterator<value_type> ) );
}

TEST_F( test_Rb_tree, end ) {

    this->AddValues( 2 );
    ASSERT_EQ( *( --this->t.end() ), ft::make_pair( 2, 4 ) );
    ASSERT_EQ( typeid( this->t.begin() ),
               typeid( typename ft::Rb_tree_iterator<value_type> ) );
}

TEST_F( test_Rb_tree, rbegin ) {

    this->AddValues( 2 );
    ASSERT_EQ( *this->t.rbegin(), ft::make_pair( 2, 4 ) );
    ASSERT_EQ(
        typeid( this->t.rbegin() ),
        typeid(
            typename ft::reverse_iterator<ft::Rb_tree_iterator<value_type>> ) );
}

TEST_F( test_Rb_tree, rend ) {

    this->AddValues( 2 );
    ASSERT_EQ( *this->t.rend(), *( this->t.begin() ) );
    ASSERT_EQ(
        typeid( this->t.rend() ),
        typeid(
            typename ft::reverse_iterator<ft::Rb_tree_iterator<value_type>> ) );
}

TEST_F( test_Rb_tree, empty ) {

    ASSERT_TRUE( this->t.empty() );
    this->AddValues( 2 );
    ASSERT_FALSE( this->t.empty() );
}

TEST_F( test_Rb_tree, max_size ) {

    ASSERT_EQ( this->t.max_size(), this->t._alloc.max_size() );
    ASSERT_NE( this->t.max_size(), this->t.get_allocator().max_size() );
}

TEST_F( test_Rb_tree, _insert_unique ) {

    typename test_Rb_tree::Tree a;

    auto beg = ( a._insert_unique( ft::make_pair( 1, 2 ) ) ).first;
    auto end = ( a._insert_unique( ft::make_pair( 4, 8 ) ) ).first;
    ASSERT_TRUE( a._insert_unique( ft::make_pair( 2, 4 ) ).second );
    ASSERT_TRUE( a._insert_unique( ft::make_pair( 3, 6 ) ).second );

    ASSERT_EQ( a.size(), 4 );
    ASSERT_EQ( a.begin(), beg );
    ASSERT_EQ( --a.end(), end );

    ASSERT_FALSE( a._insert_unique( ft::make_pair( 3, 6 ) ).second );
    ASSERT_EQ( a.size(), 4 );

    ASSERT_TRUE( a._insert_unique( ft::make_pair( 5, 10 ) ).second );
    ASSERT_NE( --a.end(), end );
}

TEST_F( test_Rb_tree, _insert_range_unique ) {

    this->AddValues( 3 );
    typename test_Rb_tree::Tree a;

    a._insert_range_unique( this->t.begin(), this->t.end() );
    ASSERT_EQ( a.size(), 3 );
    ASSERT_EQ( a, this->t );
}

TEST_F( test_Rb_tree, swap ) {

    this->AddValues( 3 );
    typename test_Rb_tree::Tree a;
    typename test_Rb_tree::Tree b( this->t );

    ASSERT_EQ( this->t.size(), 3 );
    ASSERT_EQ( a.size(), 0 );
    ASSERT_EQ( b, this->t );
    ASSERT_FALSE( b == a );

    a.swap( this->t );

    ASSERT_EQ( this->t.size(), 0 );
    ASSERT_EQ( a.size(), 3 );
    ASSERT_EQ( b, a );
    ASSERT_FALSE( b == this->t );
    ASSERT_TRUE( b.rb_verify() );
}

TEST_F( test_Rb_tree, erase ) {

    this->AddValues( 6 );

    typename test_Rb_tree::Tree a;
    a._insert_unique( ft::make_pair( 1, 2 ) );
    a._insert_unique( ft::make_pair( 4, 8 ) );
    // erase first value
    ASSERT_EQ( this->t.size(), 6 );
    this->t.erase( ++this->t.begin() );
    ASSERT_EQ( this->t.size(), 5 );
    ASSERT_EQ( this->t.find( 2 ), this->t.end() );
    // erase last 2 values
    auto it = --this->t.end();
    this->t.erase( --it, this->t.end() );
    ASSERT_EQ( this->t.find( 5 ), this->t.end() );
    ASSERT_EQ( this->t.find( 6 ), this->t.end() );
    ASSERT_EQ( this->t.size(), 3 );
    // erase value from key
    ASSERT_NE( this->t.find( 3 ), this->t.end() );
    this->t.erase( 3 );
    ASSERT_EQ( this->t.find( 3 ), this->t.end() );
    ASSERT_EQ( this->t.size(), 2 );
    // checking values
    ASSERT_EQ( this->t, a );
    // erasing everything
    this->t.erase( this->t.begin(), this->t.end() );
    ASSERT_TRUE( this->t.empty() );
}

TEST_F( test_Rb_tree, clear ) {

    this->AddValues( 5 );
    ASSERT_EQ( this->t.size(), 5 );
    this->t.clear();
    ASSERT_TRUE( this->t.empty() );
}

TEST_F( test_Rb_tree, find ) {

    this->AddValues( 3 );
    ASSERT_EQ( this->t.find( 0 ), this->t.end() );
    ASSERT_EQ( this->t.find( 1 )->first, 1 );
    ASSERT_EQ( this->t.find( 1 )->second, 2 );
    ASSERT_EQ( this->t.find( 2 )->first, 2 );
    ASSERT_EQ( this->t.find( 2 )->second, 4 );
    ASSERT_EQ( this->t.find( 3 )->first, 3 );
    ASSERT_EQ( this->t.find( 3 )->second, 6 );
    ASSERT_EQ( this->t.find( 4 ), this->t.end() );
}

TEST_F( test_Rb_tree, count ) {

    this->AddValues( 4 );
    // for ( auto it = this->t.begin(); it != this->t.end(); it++ )
    //     ASSERT_EQ( this->t.count( it->first ), 1 );
    ASSERT_EQ( this->t.count( 10 ), 0 );
}

TEST_F( test_Rb_tree, lower_bound ) {

    this->AddValues( 2 );
    auto it = this->t.begin();

    ASSERT_EQ( this->t.lower_bound( 0 ), it );
    ASSERT_EQ( this->t.lower_bound( 1 ), it );
    ASSERT_EQ( this->t.lower_bound( 2 ), ++it );
    ASSERT_EQ( this->t.lower_bound( 3 ), this->t.end() );
}

TEST_F( test_Rb_tree, upper_bound ) {

    this->AddValues( 2 );
    auto it = this->t.begin();

    ASSERT_EQ( this->t.upper_bound( 0 ), this->t.begin() );
    ASSERT_EQ( this->t.upper_bound( 1 ), ++it );
    ASSERT_EQ( this->t.upper_bound( 2 ), this->t.end() );
    ASSERT_EQ( this->t.upper_bound( 3 ), this->t.end() );
}

TEST_F( test_Rb_tree, equal_range ) {

    this->AddValues( 3 );

    auto it = this->t.equal_range( 1 );
    ASSERT_EQ( it.second, this->t.find( 2 ) );

    it = this->t.equal_range( -1 );
    ASSERT_EQ( it.first, this->t.begin() );
    ASSERT_EQ( it.second, this->t.begin() );

    it = this->t.equal_range( 10 );
    ASSERT_EQ( it.first, this->t.end() );
    ASSERT_EQ( it.second, this->t.end() );
}

TEST_F( test_Rb_tree, get_allocator ) {

    ASSERT_EQ( typeid( this->t.get_allocator() ),
               typeid( std::allocator< ft::pair<int, int> > ) );
}

TEST_F( test_Rb_tree, rb_verify ) {}

TEST_F( test_Rb_tree, non_member_functions ) {

    typename test_Rb_tree::Tree a;
    // equals
    ASSERT_TRUE( this->t == this->t );
    this->AddValues( 5 );
    ASSERT_FALSE( this->t == a );
    a = this->t;
    ASSERT_TRUE( this->t == a );
    // not equals
    ASSERT_TRUE( this->t == this->t );
    this->AddValues( 5 );
    ASSERT_FALSE( this->t == a );
    a = this->t;
    ASSERT_TRUE( this->t == a );
    // less and less eq
    ASSERT_FALSE( this->t < a );
    this->AddValues( 5 );
    ASSERT_FALSE( this->t < a );
    this->t = a;
    ASSERT_FALSE( this->t < a );
}

#endif /* GTEST */
