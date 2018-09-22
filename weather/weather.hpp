#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/action.hpp>

using namespace eosio;
using namespace std;


class weather : public contract {
public:
    weather(account_name self) : contract(self) {}

    void write(const account_name author, const time observed_at, const vector<string> regions, const vector<string> weather, const vector<uint_64_t> temperatures);

private:
    
    // @abi table weathers i64
    struct record {
        uint64_t id;
        account_name author;
        string region;
        string weather;
        uint64_t temperature;
        time observed_at;
        time created_at;
        time updated_at;

        uint64_t primary_key() const { return id; }

        EOSLIB_SERIALIZE(record, (id)(author)(region)(weather)(temperature)(observed_at)(creaetd_at)(updated_at))
    };

    typedef multi_index<N(weathers), record> weather_table;
};

EOSIO_ABI(weather, (write))
