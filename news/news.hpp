#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/action.hpp>

using namespace eosio;
using namespace std;

class news : public contract
{
  public:
    news(account_name self) : contract(self) {}

    void write(const account_name author, const string title, const string content, const time published_at);

  private:
    // @abi table articles i64
    struct article
    {
        uint64_t id;
        uint64_t num_news;
        time updated_at;

        uint64_t primary_key() const { return id; }

        EOSLIB_SERIALIZE(article, (id)(num_news)(updated_at))
    };

    typedef multi_index<N(articles), article> article_table;
};

EOSIO_ABI(news, (write))
