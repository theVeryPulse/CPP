#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main()
{
    {
        const Animal* meta = new Animal();
        const Animal* j    = new Dog();
        const Animal* i    = new Cat();

        std::cout << j->getType() << " \n";
        std::cout << i->getType() << " \n";

        i->makeSound(); // will output the cat sound!
        j->makeSound();
        meta->makeSound();

        delete meta;
        delete i;
        delete j;
    }

    {
        const WrongAnimal* meta = new WrongAnimal();
        const WrongAnimal* i    = new WrongCat();

        std::cout << i->getType() << " \n";

        i->makeSound(); // will output the cat sound!
        meta->makeSound();

        delete meta;
        delete i;
    }
    return 0;
}
