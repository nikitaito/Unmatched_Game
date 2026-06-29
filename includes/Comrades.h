#pragma once

#include<string>

class Comrades
{

    private:
    std::string name;
    std::string Attacktype;
    int Health;
    int Movement;

    bool islive {};

    public:
    Comrades(std::string, std::string, int, int);

    bool get_islive() const;
    // void set_islive();

    std::string get_Attacktype() const;

    int get_Movement() const;    
    int get_Health() const;
    
    virtual void Damage(int) = 0;


};