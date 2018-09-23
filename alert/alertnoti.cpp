#include "alertnoti.hpp"

// @abi action broadcast
void alertnoti::broadcast(const account_name author, const string title, const string description)
{
    require_auth(author);
    alert_table alert(_self, _self);
    
    alert_id alert_index;
    get_alert_id(alert_index);
    uint64_t alert_id = alert_index.id++;

    alert.emplace(_self, [&](auto &data) {
        data.id = alert.available_primary_key();
        data.author = author;
        data.title = title;
        data.description = description;
        data.status = true;
        data.created_at = now();
        data.updated_at = now();
    });

    set_alert_id(alert_index);
}

// @abi action stop
void alertnoti::stop(const account_name author, const uint64_t alert_id)
{
    require_auth(author);
    alert_table alert(_self, _self);

    auto alert_iter = alert.find(alert_id);
    eosio_assert(alert_iter != alert.end(), "Alert record doesn't exist");
    require_auth(alert_iter->author);

    alert.modify(alert_iter, 0, [&](auto& data) {
        data.status = false;
        data.updated_at = now();
    });
}