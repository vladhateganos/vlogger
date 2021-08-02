//
// Created by vlad on 02.08.2021.
//

#include "vlogger.h"

#include <iostream>
#include <tuple>
#include <vector>



int main()
{
    std::tuple<std::string, std::string> t = std::make_tuple("kek1","kek2");

    vlogger::VLogger vlogger;

    vlogger.info("test");

    return 0;
}
