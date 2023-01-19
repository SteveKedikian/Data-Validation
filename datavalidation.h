#ifndef DATA_VALIDATION_H
#define DATA_VALIDATION_H

#include <string>

enum {
    // size limits
    EMAIL_AT_SIGN_COUNT = 1,
    DATE_SIZE = 20,
    DATE_SLASH_COUNT = 2,
    DATE_MONTH_OR_DAY_SIZE = 2,
    DATE_MONTH_NAME_SIZE = 3,
    DATE_SPACE_COUNT = 2,
    DATE_COMMA_COUNT = 1,
    DATE_MONTH_COUNT = 12,
    DATE_MONTH_DAYS = 31,
    RECIEPIENT_NAME_SIZE = 64,
    DOMAIN_NAME_SIZE = 253,
    DAY_COUNT_PER_YEAR = 365,

    // ASCII symbols
    SPACE_SIGN_ASCII = 32,
    PLUS_SIGN_ASCII = 43,
    COMMA_SIGN_ASCII = 44,
    HYPHEN_SIGN_ASCII = 45,
    DOT_SIGN_ASCII = 46,
    SLASH_SIGN_ASCII = 47,
    ZERO_ASCII = 48,
    NINE_ASCII = 57,
    COLON_SIGN_ASCII = 58,
    AT_SIGN_ASCII = 64,
    CAPITAL_A_ASCII = 65,
    CAPITAL_Z_ASCII = 90,
    SMALL_a_ASCII = 97,
    SMALL_Z_ASCII = 122,
};

namespace skt {

class DataValidation 
{
public:
    // if data is valid, functions will return true, false if it's not
    bool is_valid_email(const std::string& email_line);
    bool is_valid_url(const std::string& url_line);
    bool is_valid_date(const std::string& date_line);
    bool is_valid_number(const std::string& number_line);

private: // helping functions
    bool is_special_symbol(const char symbol);
    bool is_letter_symbol(const char symbol);
    bool is_number_symbol(const char symbol);
    bool line_has_letter_or_special_symbol(const std::string& line);
    int slash_count(const std::string& line);
    int comma_count(const std::string& line);
    int space_count(const std::string& line);

private: // email checking functions
    bool email_at_symbol_check(const std::string& line); // 64 represents ASCII '@' symbol's number
    std::string email_get_reciepient_name(const std::string& line);
    std::string email_get_domain_name(const std::string& line, const int start);
    bool email_check_reciepient_name(const std::string& reciepient_name);
    bool email_check_domain_name(const std::string& domain_name);

private: // url checking functions
    bool url_colon_symbol_check(const std::string& line);
    std::string url_get_scheme(const std::string& line);
    bool url_check_scheme(const std::string& line);

private: // date checking functions
    bool date_check_letters(const std::string& line);
    bool date_check_slash(const std::string& line);
    bool date_check_two_slash(const std::string& line);
    bool date_check_one_slash(const std::string& line);
    std::string date_get_token_letter(const std::string& line, int& start);
    std::string date_get_token_slash(const std::string& line, const int start);
    bool date_check_none(const std::string& line);
    bool date_month_exists(const std::string& line);
    bool date_check_lines(const std::string& left, const std::string& mid, const std::string& right);

private:
    static const std::string m_months[DATE_MONTH_COUNT];

}; // class end - DataValidation

} // namespace end - skt

#endif // DATA_VALIDATION_H