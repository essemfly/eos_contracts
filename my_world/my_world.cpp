#include "my_world.hpp"

// @abi action regctr
void myworld::regctr(const account_name user, const string app_name, const string description, const vector<string> actions)
{
    require_auth(user);
    app_table app(_self, _self);
    
    app_id app_index;
    get_app_id(app_index);
    uint64_t app_id = app_index.id++;

    prints("I am fine");

    for (auto &action : actions)
    {
        app.emplace(_self, [&](auto &data) {
            data.id = app.available_primary_key();
            data.author = user;
            data.name = app_name;
            data.description = description;
            data.action = action;
            data.created_at = now();
            data.updated_at = now();
        });

        app_id++;
    }
    prints("good");

    set_app_id(app_index);
}

// @abi action follow
void myworld::follow(const account_name user, const uint64_t app_id)
{
    follow_table followship(_self, _self);
    require_auth(user);

    followship.emplace(_self, [&](auto &data) {
        data.id = followship.available_primary_key();
        data.author = user;
        data.app_id = app_id;
        data.created_at = now();
        data.updated_at = now();
    });
}

// @abi action unfollow
void myworld::unfollow(const account_name user, const uint64_t app_id)
{
    // follow_table followship(_self, user);

    // auto iter = followship.find(app_id);
    // eosio_assert(iter != followship.end(), "Record doesn't exist");
    // require_auth(iter->author);

    // followship.erase(iter);
    // print("Record deleted");
}