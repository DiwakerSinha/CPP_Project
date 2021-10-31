/**
 * @file room.cpp
 * Implementation of the Room class.
 */

#include <iostream>
#include "room.h"

Room::Room() : capacity(0), count(0), max_letters(26), letters(NULL), letterCount(0)
{
  letters = new Letter[max_letters];
}

Room::Room(const std::string& init_name, int init_capacity)
    : name(init_name),
      capacity(init_capacity),
      count(0),
      max_letters(26),
      letterCount(0)
{
    letters = new Letter[max_letters];
}

Room::Room(const Room& other)
{
    copy(other);
}

Room& Room::operator=(const Room& other)
{
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

Room::~Room()
{
    clear();
}

void Room::addLetter(const Letter& L)
{
    letters[letterCount++] = L;
    count += L.count;
}

int Room::spaceRemaining()
{
    return capacity - count;
}

void Room::print(std::ostream & stream /* = std::cout */)
{
    stream << name << " (" << count << "/" << capacity << "):";
    for (int L = 0; L < letterCount; L++)
        stream << " " << letters[L].letter;
    stream << std::endl;
}

void Room::clear()
{
    if (letters != NULL)

        //delete letters; cannot use this since we have a full array, so we need to delete the entire array
        delete []letters;
    
}

void Room::copy(const Room& other)
{
    name = other.name;
    capacity = other.capacity;
    count = other.count;
    letterCount = other.letterCount;
    //letters = other.letters; cannot use this since we have a full array, so we need to manually traverse the array and copy each value
    letters = new Letter[max_letters];
    for (int i = 0; i <= (letterCount - 1); i++){
      letters[i] = other.letters[i];
    }

}
