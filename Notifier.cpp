//
// Created by filip on 15/11/2022.
//

#include <iostream>
#include "Notifier.h"

Notifier::Notifier(const std::string &name){
    this->name = name;
}

void Notifier::update(Message msg) {
    using namespace std;
    cout << "Ehi " << this->name << ", hai ricevuto un messaggio: " << msg.getText() << endl;
}

std::string Notifier::getName() {
    return name;
}

Notifier::~Notifier() {

}

