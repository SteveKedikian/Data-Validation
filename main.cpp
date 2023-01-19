#include "datavalidation.h"

#include <iostream>

int main() {
    skt::DataValidation check;

    std::cout << check.is_valid_email("john.doe43!_*^&^&f@domainsample.co.uk") << "\n";
    std::cout << check.is_valid_url("htt@sadadadwap://aff.woww..com/f/f/af/waf/aw/fa") << "\n";
    std::cout << check.is_valid_date("5223/24") << "\n";
    std::cout << check.is_valid_date("Feb, 12 2021") << "\n";
    std::cout << check.is_valid_date("111@1, Jan 25") << "\n";
    std::cout << check.is_valid_date("14 Sep, 2523") << "\n";
}