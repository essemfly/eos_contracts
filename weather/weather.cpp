#include "weather.hpp"

// @abi action write
void weather::write(const account_name author, const time observed_at, const vector<string> regions, const vector<string> weather, const vector<string> temperatures) {
    require_auth(author);
    prints("Success on")
}
