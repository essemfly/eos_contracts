#include "banks.hpp"

// @abi action debug
void banks::debug()
{
    prints("debug gogosing");
}

void banks::apply(const account_name contract, const account_name act)
{
    if (act == N(transfer))
    {
        transferReceived(unpack_action_data<currency::transfer>(), contract);
        return;
    }

    auto &thiscontract = *this;

    switch (act)
    {
        EOSIO_API(banks, (debug))
    };
}

void banks::transferReceived(const currency::transfer &transfer, const account_name code)
{
    if (transfer.from != N(banks))
    {
        if (transfer.to != _self)
        {
            return;
        }

        if (static_cast<uint32_t>(transfer.quantity.symbol == S(4, SYS)))
        {
            eosio_assert(static_cast<uint32_t>(code == N(eosio.token)), "Eosio.token");
            eosio_assert(static_cast<uint32_t>(transfer.memo.length() > 0), "Memo");

            asset eosReceived = transfer.quantity;
            uint64_t EOSamount = eosReceived.amount - 1;
            asset eosToSend = asset(EOSamount, S(4, SYS));
            print("hoit:", account_name(code));
            print("my:", account_name(_self));
            print("bank:", account_name(N(banks)));
            print("transfer_to:", account_name(transfer.to));
            prints("hoit2");

            action(permission_level{_self, N(active)}, N(eosio.token), N(transfer), make_tuple(_self, transfer.from, eosToSend, string("I will get 1EOS"))).send();
        }
    }
}

extern "C"
{

    void apply(uint64_t receiver, uint64_t code, uint64_t action)
    {
        auto self = receiver;
        banks contract(self);
        contract.apply(code, action);
        eosio_exit(0);
    }
}
