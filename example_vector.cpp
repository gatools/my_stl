/*******************************************************************************
 * Example of usage
 *******************************************************************************/

#include "vector.hpp"

#include <iostream>

/** Helper function to print vector
 * @param aName Test name
 * @param aVector Vector to print
 */
template <typename T>
static void printVector(const char*const aName, const gatools::vector<T>& aVector)
{
    std::cout << aName << ":" << std::endl;
    std::cout << "|--- Capacity: " << aVector.capacity() << std::endl;
    std::cout << "|--- Size: " << aVector.size() << std::endl;
    std::cout << "|--- Values: ";

    const gatools::size_type size = aVector.size();
    if (size > 0) {
        for (gatools::size_type i = 0, end = size - 1; i < end; ++i) {
            std::cout << aVector[i] << ", ";
        }
        std::cout << aVector[size - 1];
    }
    std::cout << std::endl << std::endl;
}

/** Main function */
int main(int argc, char** argv)
{
    std::cout << "First case" << std::endl;
    gatools::vector<int> myvector1 {1, 2, 3};
    myvector1.push_back(4);

    printVector("myvector1", myvector1);

    std::cout << "Second case: copy to second vector" << std::endl;
    gatools::vector<int> myvector2(myvector1);

    printVector("myvector1", myvector1);
    printVector("myvector2", myvector2);

    myvector1.push_back(5);
    myvector1.push_back(6);
    myvector1.push_back(7);
    myvector1.push_back(8);
    myvector1.push_back(8);
    myvector1.insert(1, 46);

    std::cout << "Third case: Move to third vector" << std::endl;
    gatools::vector<int> myvector3(std::move(myvector1));
    printVector("myvector1", myvector1);
    printVector("myvector2", myvector2);
    printVector("myvector3", myvector3);

    return 0;
}
