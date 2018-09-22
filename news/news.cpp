#include "news.hpp"

// @abi action write
void news::write(const account_name author, const string title, const string content, const time published_at)
{
    article_table article(_self, _self);
    require_auth(author);

    auto article_iter = article.find(1);

    article.modify(article_iter, 0, [&](auto& data) {
        data.id = article_iter->id + 1;
        data.num_news = article_iter->num_news + 1;
        data.updated_at = now();
    });
}
