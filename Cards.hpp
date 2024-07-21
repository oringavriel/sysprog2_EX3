#pragma once

#ifndef CARDS_HPP
#define CARDS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

namespace ariel
{
    class Cards
    {
        private:
            map<string, int> cardsPack;
        public:
            Cards();
            vector<string> getCardTypes();
            map<string, int> getCardsPack();
            void reduceCard(string str);
    };
}
#endif 