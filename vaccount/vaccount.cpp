#include "vaccount.hpp"

// @abi action debug
void vaccount::debug()
{
    prints("debug gogosing");
}

void vaccount::request(const account_name code)
{
    vacc_table vaccout(_self, _self);
    require_auth(code);

    vacc_id vacc_index;
    get_vacc_id(vacc_index);
    uint64_t vacc_id = vacc_index.id++;

    checksum256 result
    sha256((char *)&code, sizeof(code), &result);

    vaccount.emplace(_self, [&](auto &data) {
        data.id = vaccount.available_primary_key();
        data.memo = result.hash;
        data.pwd_hash = "random_generated";
        data.amount = 0;
    });
}

void vaccount::apply(const account_name contract, const account_name act)
{
    if (act == N(transfer))
    {
        transferReceived(unpack_action_data<currency::transfer>(), contract);
        return;
    }

    auto &thiscontract = *this;

    switch (act)
    {
        EOSIO_API(vaccount, (debug))
    };
}

void vaccount::transferCheck(const currency::transfer &transfer, const account_name code)
{
    if (transfer.from != N(vaccount))
    {
        if (transfer.to != _self)
        {
            return;
        }

        if (static_cast<uint32_t>(transfer.quantity.symbol == S(4, SYS)))
        {
            eosio_assert(static_cast<uint32_t>(code == N(eosio.token)), "It should be eos token");
            eosio_assert(static_cast<uint32_t>(transfer.memo.length() > 0), "Memo");

            asset eosReceived = transfer.quantity;
            uint64_t EOSamount = eosReceived.amount - 1;
            asset eosToSend = asset(EOSamount, S(4, SYS));

            action(permission_level{_self, N(active)}, N(eosio.token), N(transfer), make_tuple(_self, transfer.from, eosToSend, string("I will get 1EOS"))).send();
        }
    }
}

extern "C"
{

    void apply(uint64_t receiver, uint64_t code, uint64_t action)
    {
        auto self = receiver;
        vaccount contract(self);
        contract.apply(code, action);
        eosio_exit(0);
    }
}
