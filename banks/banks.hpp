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

class banks : public contract
{
public:
  banks(account_name self) : contract(self) {}

  // @abi action
  void debug();

  void apply(const account_name contract, const account_name act);

  void transferReceived(const currency::transfer &transfer, const account_name code);
};
// EOSIO_ABI(banks, (debug))