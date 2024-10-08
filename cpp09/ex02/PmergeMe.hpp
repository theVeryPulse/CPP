#pragma once
#ifndef PMERGE_ME_H
#define PMERGE_ME_H

#include <vector>
#include <list>
#include <iostream>

class PmergeMe
{
  public:
    //--------------- Types: Classes, Enums, and Aliases (using) ---------------
    //----------------- Constructors, Assignments, Destructor ------------------

    PmergeMe();
    ~PmergeMe();

    //------------------------------- Functions --------------------------------

    void sort(std::vector<int>& vec, bool print_message = true);
    void sort(std::list<int>& lst, bool print_message = true,
              std::string print_padding = "");

    //---------------------------------- Data ----------------------------------

  protected:
    //--------------- Types: Classes, Enums, and Aliases (using) ---------------
    //----------------- Constructors, Assignments, Destructor ------------------
    //------------------------------- Functions --------------------------------
    //---------------------------------- Data ----------------------------------

  private:
    //--------------- Types: Classes, Enums, and Aliases (using) ---------------

    struct Pair
    {
        int tail;
        int main;
    };

    typedef std::vector<int> VecInt;
    typedef std::list<int>   ListInt;

    //----------------- Constructors, Assignments, Destructor ------------------

    PmergeMe(const PmergeMe& other);            // Copy constructor
    PmergeMe& operator=(const PmergeMe& other); // Copy assignment operator

    //------------------------------- Functions --------------------------------

    void sortWithinPairs(VecInt& nums);
    int  nextToInsert(int nth_group);

    VecInt::iterator  findInsertPos(VecInt::iterator       begin,
                                    VecInt::const_iterator end,
                                    const int              to_insert);
    ListInt::iterator findInsertPos(ListInt::iterator       begin,
                                    ListInt::const_iterator end,
                                    const int               to_insert);
    //---------------------------------- Data ----------------------------------
};

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec);
std::ostream& operator<<(std::ostream& os, const std::list<int>& lst);

#endif /* PMERGE_ME_H */
