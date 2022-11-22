//
// Created by filip on 22/11/2022.
//

#include <iostream>
#include "badNotifier.h"

void badNotifier::update(Message &msg) {
    std::cout << msg.getMyTime() << std::endl;
}

badNotifier::badNotifier(int number) : number(number) {

}
