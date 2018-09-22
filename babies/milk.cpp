#include "milk.hpp"

// @abi action debug
void milk::debug() {
    print("I am seokmin");
}

// @abi action write
void milk::write(const account_name author, const string meal_type, const string child_name, const uint32_t volume) {
    record_table record(_self, _self);
    require_auth(author);

    post_id record_index;
    get_post_id(record_index);
    uint64_t post_id = record_index.id++;
    prints("record write call is good");
    record.emplace(_self, [&](auto& data) {
       data.id = post_id;
       data.author = author;
       data.type = meal_type;
       data.name = child_name;
       data.volume = volume;
       data.ate_at = now();
       data.created_at = now();
    });

    prints("What's the problem?");

    // set_post_id(record_index);
}

// @abi action update
void milk::update(const uint64_t record_id, const account_name author, const string meal_type, const string child_name, const uint32_t volume, const time ate_at) {
    record_table record(_self, _self);
    require_auth(author);

    auto record_iter = record.find(record_id);
    eosio_assert(record_iter != record.end(), "Record doesn't exist");
    require_auth(record_iter->author);

    record.modify(record_iter, 0, [&](auto& data) {
        data.type = meal_type;
        data.name = child_name;
        data.volume = volume;
        data.ate_at = ate_at;
        data.updated_at = now();
    });
}

// @abi action remove
void milk::remove(const uint64_t record_id) {
    record_table record(_self, _self);

    auto record_iter = record.find(record_id);
    eosio_assert(record_iter != record.end(), "Record doesn't exist");
    require_auth(record_iter->author);

    record.erase(record_iter);
    print("Record deleted");
}
