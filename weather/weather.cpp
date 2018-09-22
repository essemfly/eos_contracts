#include "weather.hpp"

// @abi action write
void weather::write(const account_name author, const time observed_at, const vector<string> regions, const vector<string> weather, const vector<uint64_t> temperatures, const string message, const bool warning)
{
    require_auth(author);

    weather_table weather_index(_self, _self);

    if (warning == true)
    {
        weather_index.emplace(_self, [&](auto &data) {
            data.id = weather_index.available_primary_key();
            data.message = message;
            data.warning = warning;
            data.observed_at = observed_at;
            data.created_at = now();
            data.updated_at = now();
        });
    } else {
        prints("Keep going");
    }
}
