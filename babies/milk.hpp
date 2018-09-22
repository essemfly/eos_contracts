#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/action.hpp>

using namespace eosio;
using namespace std;


class milk : public contract {
public:
    milk(account_name self) : contract(self) {}

    void debug();
    // void write(const account_name author, const string meal_type, const string child_name, const uint32_t volume, const time ate_at);
    void write(const account_name author, const string meal_type, const string child_name, const uint32_t volume);

    void update(const uint64_t record_id, const account_name author, const string meal_type, const string child_name, const uint32_t volume, const time ate_at);

    void remove(const uint64_t record_id);
private:
    static uint64_t id;

    struct post_id {
        post_id() {}
        constexpr static uint64_t key = N(post_id);
        uint64_t id = 1;
    };

    bool get_post_id(post_id &data) {
        auto iter = db_find_i64(_self, _self, N(post_id), post_id::key);

        if (iter != -1) {
            auto size = db_get_i64(iter, (char *)&data, sizeof(post_id));
            eosio_assert(size == sizeof(post_id), "Invalid post id.");
            return true;
        }
        return false;
    }
    
    void set_post_id(const post_id &data) {
        auto iter = db_find_i64(_self, _self, N(post_id), post_id::key);

        if (iter != -1) {
            db_update_i64(iter, _self, (const char *)&data, sizeof(post_id));
        } else {
            db_store_i64(_self, N(post_id), _self, post_id::key, (const char *)&data, sizeof(post_id));
        }
    };

    // @abi table milk_records i64
    struct record {
        uint64_t id;
        account_name author;
        string type;
        string name;
        string volume;
        time ate_at;
        time created_at;
        time updated_at;

        uint64_t primary_key() const { return id; }
        account_name by_account() const { return author; }

        EOSLIB_SERIALIZE(record, (id)(author)(type)(name)(volume)(ate_at)(created_at)(updated_at))
    };

    typedef multi_index<N(milk_records), record, indexed_by<N(author), const_mem_fun<record, account_name, &record::by_account>>> record_table;
};

EOSIO_ABI(milk, (debug)(write)(update)(remove))
