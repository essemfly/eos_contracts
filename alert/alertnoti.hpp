#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/action.hpp>

using namespace eosio;
using namespace std;

class alertnoti : public contract
{
  public:
    alertnoti(account_name self) : contract(self) {}

    // @abi action
    void broadcast(const account_name author, const string title, const string description);

    // @abi action
    void stop(const account_name author, const uint64_t alert_id);

  private:
    static uint64_t id;

    struct alert_id
    {
        alert_id() {}
        constexpr static uint64_t key = N(alert_id);
        uint64_t id = 1;
    };

    bool get_alert_id(alert_id &data)
    {
        auto iter = db_find_i64(_self, _self, N(alert_id), alert_id::key);

        if (iter != -1)
        {
            auto size = db_get_i64(iter, (char *)&data, sizeof(alert_id));
            eosio_assert(size == sizeof(alert_id), "Invalid alert_id.");
            return true;
        }
        return false;
    }

    void set_alert_id(const alert_id &data)
    {
        auto iter = db_find_i64(_self, _self, N(alert_id), alert_id::key);

        if (iter != -1)
        {
            db_update_i64(iter, _self, (const char *)&data, sizeof(alert_id));
        }
        else
        {
            db_store_i64(_self, N(alert_id), _self, alert_id::key, (const char *)&data, sizeof(alert_id));
        }
    };

    // @abi table alerts
    struct alert
    {
        uint64_t id;
        account_name author;
        string title;
        string description;
        bool status;
        time created_at;
        time updated_at;

        uint64_t primary_key() const { return id; }
        account_name by_account() const { return author; }

        EOSLIB_SERIALIZE(alert, (id)(author)(title)(description)(status)(created_at)(updated_at))
    };

    typedef multi_index<N(alerts), alert> alert_table;
};

EOSIO_ABI(alertnoti, (broadcast))
