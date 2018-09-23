#include <string>
#include <eosiolib/print.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/currency.hpp>
#include <string>

using namespace eosio;
using namespace std;

class vaccount : public contract
{
  public:
    vaccount(account_name self) : contract(self) {}

    // @abi action
    void debug();

    // @abi action
    void request(const account_name code);

    // @abi action
    void withdrawal(const string memo, const string pwd);

    // Deposit은 여기서 그냥 해결 
    void apply(const account_name contract, const account_name act);

    // 잔고 Check는 eosjs에서 알아서 처리

    void transferCheck(const currency::transfer &transfer, const account_name code);

  private:
    struct uint64_t id;

    struct vaccount_id
    {
      vaccount_id() {}
      constexpr static uint64_t key = N(vaccount_id);
      uint64_t id = 1;
    };

    bool get_vacc_id(vaccount_id &data)
    {
      auto iter = db_find_i64(_self, _self, N(vaccount_id), vaccount_id::key);

      if (iter != -1)
      {
        auto size = db_get_i64(iter, (char *)&data, sizeof(vaccount_id));
        eosio_assert(size == sizeof(vaccount_id), "Invalid vaccount id.");
        return true;
      }
      return false;
    };

    void set_vacc_id(const vaccount_id &data)
    {
      auto iter = db_find_i64(_self, _self, N(vaccount_id), vaccount_id::key);

      if (iter != -1)
      {
        db_update_i64(iter, _self, (const char *)&data, sizeof(vaccount_id));
      }
      else
      {
        db_store_i64(_self, N(vaccount_id), _self, vaccount_id::key, (const char *)&data, sizeof(vaccount_id));
      }
    };

  // @abi table vaccounts
  struct vaccount{
      uint64_t id;
      string memo;
      string pwd_hash;
      uint64_t amount;

      uint64_t primary_key() const { return id; }

      EOSLIB_SERIALIZE(vaccount, (id)(memo)(pwd_hash)(amount))
  };

  typedef multi_index<N(vaccounts), vaccount> vacc_table;
};
// EOSIO_ABI(vaccount, (debug)(request))