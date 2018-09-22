#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/action.hpp>

using namespace eosio;
using namespace std;

class weather : public contract
{
  public:
    weather(account_name self) : contract(self) {}

    void write(const account_name author, const time observed_at, const vector<string> regions, const vector<string> weather, const vector<uint64_t> temperatures, const string message, const bool warning);

  private:
    // @abi table weathers i64
    struct record
    {
        uint64_t id;
        string message;
        bool warning;
        time observed_at;
        time created_at;
        time updated_at;

        uint64_t primary_key() const { return id; }

        EOSLIB_SERIALIZE(record, (id)(message)(warning)(observed_at)(created_at)(updated_at))
    };

    typedef multi_index<N(weathers), record> weather_table;
};

EOSIO_ABI(weather, (write))
