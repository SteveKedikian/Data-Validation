#include "datavalidation.h"

const std::string skt::DataValidation::m_months[DATE_MONTH_COUNT] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

bool skt::DataValidation::is_special_symbol(const char symbol) {
    if ((symbol >= ZERO_ASCII && symbol <= NINE_ASCII) ||
        (symbol >= CAPITAL_A_ASCII && symbol <= CAPITAL_Z_ASCII) ||
        (symbol >= SMALL_a_ASCII && symbol <= SMALL_Z_ASCII))
    {
        return false;
    }
    return true;
}

bool skt::DataValidation::is_letter_symbol(const char symbol) {
    if ((symbol >= CAPITAL_A_ASCII && symbol <= CAPITAL_Z_ASCII) ||
        (symbol >= SMALL_a_ASCII && symbol <= SMALL_Z_ASCII))
    {
        return true;
    }
    return false;
}

bool skt::DataValidation::is_number_symbol(const char symbol) {
    if (symbol >= ZERO_ASCII && symbol <= NINE_ASCII) {
        return true;
    }
    return false;
}

bool skt::DataValidation::line_has_letter_or_special_symbol(const std::string& line) {
    for (int i = 0; i < line.length(); ++i) {
        if (is_special_symbol(line[i]) || is_letter_symbol(line[i])) {
            return true;
        }
    }
    return false;
}

int skt::DataValidation::slash_count(const std::string& line) {
    int slash_count = 0;
    for (int i = 0; i < line.length(); ++i) {
        if (line[i] == SLASH_SIGN_ASCII) {
            ++slash_count;
        }
    }
    return slash_count;
}

int skt::DataValidation::comma_count(const std::string& line) {
    int comma_count = 0;
    for (int i = 0; i < line.length(); ++i) {
        if (line[i] == COMMA_SIGN_ASCII) {
            ++comma_count;
        }
    }
    return comma_count;
}
    
int skt::DataValidation::space_count(const std::string& line) {
    int space_count = 0;
    for (int i = 0; i < line.length(); ++i) {
        if (line[i] == SPACE_SIGN_ASCII) {
            ++space_count;
        }
    }
    return space_count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool skt::DataValidation::email_at_symbol_check(const std::string& line) {
    int symbol_counter = 0;
    for (int i = 0; i < line.length(); ++i) {
        if (line[i] == AT_SIGN_ASCII) {
            ++symbol_counter;
        }

        if (symbol_counter > EMAIL_AT_SIGN_COUNT) {
            return false;
        }
    }
    return true;
}

std::string skt::DataValidation::email_get_reciepient_name(const std::string& line) {
    std::string reciepient_name = "";
    for (int i = 0; line[i] != AT_SIGN_ASCII; ++i) {
        reciepient_name += line[i];
    }
    return reciepient_name;
}

std::string skt::DataValidation::email_get_domain_name(const std::string& line, const int start) {
    std::string domain_name = "";
    for (int i = start; i < line.length(); ++i) {
        domain_name += line[i];
    }
    return domain_name;
}

bool skt::DataValidation::email_check_reciepient_name(const std::string& reciepient_name) {
    int begin = 0;
    int end = reciepient_name.length() - 1;

    if (is_special_symbol(reciepient_name[begin]) || is_special_symbol(reciepient_name[end])) {
        return false;
    }
    ++begin;
    --end;
    
    while (begin <= end) {
        if (is_special_symbol(reciepient_name[begin])) {
            if (reciepient_name[begin] == reciepient_name[begin + 1]) {
                return false;
            }
        }
        ++begin;
    }
    return true;
}

bool skt::DataValidation::email_check_domain_name(const std::string& domain_name) {
    for (int i = 0; i < domain_name.length(); ++i) {
        if (domain_name[i] == DOT_SIGN_ASCII || domain_name[i] == HYPHEN_SIGN_ASCII) {
            if (domain_name[i] == domain_name[i + 1]) {
                return false;
            }
        }
        else if (is_special_symbol(domain_name[i])) {
            return false;
        }
    }
    return true;
}

bool skt::DataValidation::is_valid_email(const std::string& email_line) {
    if (!email_at_symbol_check(email_line) || (email_line.length() > RECIEPIENT_NAME_SIZE + DOMAIN_NAME_SIZE + AT_SIGN_ASCII)) {
        return false;
    }

    std::string reciepient_name = email_get_reciepient_name(email_line);
    if (reciepient_name.empty() || reciepient_name.size() > RECIEPIENT_NAME_SIZE) {
        return false;
    }

    std::string domain_name = email_get_domain_name(email_line, reciepient_name.length() + 1);
    if (domain_name.empty() || domain_name.size() > DOMAIN_NAME_SIZE) {
        return false;
    }

    if (!email_check_reciepient_name(reciepient_name) || !email_check_domain_name(domain_name)) {
        return false;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool skt::DataValidation::url_colon_symbol_check(const std::string& line) {
    for (int i = 0; i < line.length(); ++i) {
        if (line[i] == SLASH_SIGN_ASCII) {
            return true;
        }
    }
    return false;
}

std::string skt::DataValidation::url_get_scheme(const std::string& line) {
    std::string scheme = "";
    for (int i = 0; line[i] != COLON_SIGN_ASCII; ++i) {
        scheme += line[i];
    }
    return scheme;
}

bool skt::DataValidation::url_check_scheme(const std::string& line) {
    int begin = 0;
    int end = line.length() - 1;

    if (!is_letter_symbol(line[begin])) {
        return false;
    }
    ++begin;

    while (begin <= end) {
        if (!(line[begin] == PLUS_SIGN_ASCII || line[begin] == SLASH_SIGN_ASCII ||
              line[begin] == HYPHEN_SIGN_ASCII || is_letter_symbol(line[begin])))
        {
            return false;
        }
        ++begin;
    }
    return true;
}

bool skt::DataValidation::is_valid_url(const std::string& url_line) {
    if (!url_colon_symbol_check(url_line)) {
        return false;
    }

    std::string scheme = url_get_scheme(url_line);
    if (!url_check_scheme(scheme)) {
        return false;
    }

    if ((url_line[scheme.length() + 1] != SLASH_SIGN_ASCII) &&  // after scheme, for example 'http:' must be double slashes '//'
        (url_line[scheme.length() + 2] != SLASH_SIGN_ASCII)) { 
        return false;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string skt::DataValidation::date_get_token_slash(const std::string& line, const int start) {
    std::string token = "";
    for (int i = start; i < line.length() && line[i] != '/'; ++i) {
        token += line[i];
    }
    return token;
}

bool skt::DataValidation::date_check_two_slash(const std::string& line) {
    std::string left = date_get_token_slash(line, 0); // start from the begining
    std::string mid = date_get_token_slash(line, left.length() + 1); // +1 passing first slash
    std::string right = date_get_token_slash(line, left.length() + mid.length() + 2); // +2 passing first and second slash

    if (line_has_letter_or_special_symbol(left) ||
        line_has_letter_or_special_symbol(mid) ||
        line_has_letter_or_special_symbol(right))
    {
        return false;
    }

    if (left.size() > DATE_MONTH_OR_DAY_SIZE &&                                         // Y/M/D or Y/D/M
       (mid.size() > DATE_MONTH_OR_DAY_SIZE || right.size() > DATE_MONTH_OR_DAY_SIZE)) 
    {
        return false;
        }
        else if (mid.size() > DATE_MONTH_OR_DAY_SIZE &&                                 // M/Y/D or D/Y/M
            (left.size() > DATE_MONTH_OR_DAY_SIZE || right.size() > DATE_MONTH_OR_DAY_SIZE)) 
    {
        return false;
    }
    else if (right.size() > DATE_MONTH_OR_DAY_SIZE &&                                   // M/D/Y or D/M/Y
            (left.size() > DATE_MONTH_OR_DAY_SIZE || mid.size() > DATE_MONTH_OR_DAY_SIZE))
    {
        return false;
    }

    return true;
}

bool skt::DataValidation::date_check_one_slash(const std::string& line) {
    std::string left = date_get_token_slash(line, 0); // start from the begining
    std::string right = date_get_token_slash(line, left.length() + 1); // +1 passing first slash

    if (line_has_letter_or_special_symbol(left) ||
        line_has_letter_or_special_symbol(right))
    {
        return false;
    }

    if (std::stoi(left) > DAY_COUNT_PER_YEAR &&     // D/Y or Y/D
        std::stoi(right) > DAY_COUNT_PER_YEAR)
    {
        return false;
    }

    return true;
}

std::string skt::DataValidation::date_get_token_letter(const std::string& line, int& start) {
    std::string token = "";
    for (int i = start; i < line.length(); ++i) {
        if (line[i] == COMMA_SIGN_ASCII) {
            start = i + 2;
            break;
        }

        if (line[i] == SPACE_SIGN_ASCII) {
            start = i + 1;
            break;
        }

        token += line[i];
    }
    return token;
}

bool skt::DataValidation::date_month_exists(const std::string& line) {
    for (int i = 0; i < DATE_MONTH_COUNT; ++i) {
        if (line == m_months[i]) {
            return true;
        }
    }
    return false;
}

bool skt::DataValidation::date_check_lines(const std::string& left, const std::string& mid, const std::string& right) {
    if (date_month_exists(left) && is_valid_number(mid) && is_valid_number(right)) {
        if (std::stoi(mid) >= DATE_MONTH_DAYS && std::stoi(right) >= DATE_MONTH_DAYS) {
            return false;
        }
        return true;
    }
    else if (date_month_exists(mid) && is_valid_number(left) && is_valid_number(right)) {
        if (std::stoi(left) >= DATE_MONTH_DAYS && std::stoi(right) >= DATE_MONTH_DAYS) {
            return false;
        }
        return true;
    }
    else if (date_month_exists(right) && is_valid_number(left) && is_valid_number(mid)) {
        if (std::stoi(left) >= DATE_MONTH_DAYS && std::stoi(mid) >= DATE_MONTH_DAYS) {
            return false;
        }
        return true;
    }

    return false;
}

bool skt::DataValidation::date_check_letters(const std::string& line) {
    if (!(comma_count(line) == DATE_COMMA_COUNT)) {
        return false;
    }

    if (!(space_count(line) == DATE_SPACE_COUNT)) {
        return false;
    }

    int start = 0;
    std::string left = date_get_token_letter(line, start);
    std::string mid = date_get_token_letter(line, start);
    std::string right = date_get_token_letter(line, start);

    if (!date_check_lines(left, mid, right)) {
        return false;
    }

    return true;
}

bool skt::DataValidation::date_check_slash(const std::string& line) {
    int slash_counter = slash_count(line);

    if (slash_counter > DATE_SLASH_COUNT) {
        return false;
    }

    if (slash_counter == DATE_SLASH_COUNT) {
        if (!date_check_two_slash(line)) {
            return false;
        }
    }

    if (!date_check_one_slash(line)) {
        return false;
    }

    return true;
}
    
bool skt::DataValidation::date_check_none(const std::string& line) {
    for (int i = 0; i < line.length(); ++i) {
        if (is_special_symbol(line[i])) {
            return false;
        }
    }
    return true;
}

bool skt::DataValidation::is_valid_date(const std::string& date_line) {
    if (date_line.size() > DATE_SIZE) {
        return false;
    }

    bool checked = false;
    for (int i = 0; i < date_line.length(); ++i) {
        if (date_line[i] == SPACE_SIGN_ASCII || 
            date_line[i] == COMMA_SIGN_ASCII ||
            is_letter_symbol(date_line[i])) 
        {
            if (!date_check_letters(date_line)) {
                return false;
            }
            checked = true;
            break;
        }
        
        if (date_line[i] == SLASH_SIGN_ASCII) {
            if (!date_check_slash(date_line)) {
                return false;
            }
            checked = true;
            break;
        }
    }

    if (!checked) {
        if (!date_check_none(date_line)) {
            return false;
        }
    } 

    return true;
}

bool skt::DataValidation::is_valid_number(const std::string& number_line) {
    for (int i = 0; i < number_line.length(); ++i) {
        if (!is_number_symbol(number_line[i])) {
            return false;
        }
    }
    return true;
}