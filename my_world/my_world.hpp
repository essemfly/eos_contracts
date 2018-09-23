#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/action.hpp>

using namespace eosio;
using namespace std;

class myworld : public contract
{
  public:
    myworld(account_name self) : contract(self) {}

    void regctr(const account_name author, const string app_name, const string description, const string avatar_url, const vector<string> actions);

    void follow(const account_name author, const uint64_t app_id);

    void unfollow(const account_name author, const uint64_t app_id);

  private:
    static uint64_t id;

    struct app_id
    {
        app_id() {}
        constexpr static uint64_t key = N(app_id);
        uint64_t id = 1;
    };

    bool get_app_id(app_id &data)
    {
        auto iter = db_find_i64(_self, _self, N(app_id), app_id::key);

        if (iter != -1)
        {
            auto size = db_get_i64(iter, (char *)&data, sizeof(app_id));
            eosio_assert(size == sizeof(app_id), "Invalid post id.");
            return true;
        }
        return false;
    }

    void set_app_id(const app_id &data)
    {
        auto iter = db_find_i64(_self, _self, N(app_id), app_id::key);

        if (iter != -1)
        {
            db_update_i64(iter, _self, (const char *)&data, sizeof(app_id));
        }
        else
        {
            db_store_i64(_self, N(app_id), _self, app_id::key, (const char *)&data, sizeof(app_id));
        }
    };

    // @abi table apps i64
    struct app
    {
        uint64_t id;
        account_name author;
        string name;
        string avatar_url;
        string description;
        string action;
        time created_at;
        time updated_at;

        uint64_t primary_key() const { return id; }
        account_name by_account() const { return author; }

        EOSLIB_SERIALIZE(app, (id)(author)(name)(avatar_url)(description)(action)(created_at)(updated_at))
    };

    typedef multi_index<N(apps), app> app_table;

    // @abi table flwrecords i64
    struct followship
    {
        uint64_t id;
        account_name author;
        uint64_t app_id;
        time created_at;
        time updated_at;

        uint64_t primary_key() const { return id; }

        EOSLIB_SERIALIZE(followship, (id)(author)(app_id)(created_at)(updated_at))
    };

    typedef multi_index<N(flwrecords), followship> follow_table;
};

EOSIO_ABI(myworld, (regctr)(follow)(unfollow))
