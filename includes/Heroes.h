#pragma once

#include <string>

class Heroes
{

private:
    std::string name;
    std::string Attacktype;
    int Health;
    int Movement;

public:
    Heroes(std::string, std::string, int, int);

    std::string get_name();
    std::string get_Attacktype();
    int get_Movement();

    void set_Health(int);

};