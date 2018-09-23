#include "news.hpp"

// @abi action write
void news::write(const account_name author, const string title, const string content, const time published_at)
{
    uint64_t news_id = 0;
    article_table article(_self, _self);
    require_auth(author);

    auto article_iter = article.find(news_id);

    if (article_iter == article.end())
    {
        article.emplace(_self, [&](auto &data) {
            data.id = news_id;
            data.num_news = 1;
            data.updated_at = now();
        });
    }
    else
    {
        article.modify(article_iter, 0, [&](auto &data) {
            uint64_t num_news = article_iter->num_news;
            data.id = article_iter->id;
            data.num_news = num_news + 1;
            data.updated_at = now();
        });
    }
}
