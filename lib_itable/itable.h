#pragma once

template<class TKey, class TVal>
class Table
{
public:

    struct Row
    {
        TKey key;
        TVal value;
    };

    virtual void insert(const TKey& key, const TVal& value) = 0;

    virtual void erase(const TKey& key) = 0;

    virtual TVal& find(const TKey& key) = 0;

    virtual bool contains(const TKey& key) const = 0;

    virtual size_t size() const = 0;

    virtual bool empty() const = 0;

    virtual void clear() = 0;

    virtual void print() const = 0;

    virtual ~Table() {}
};