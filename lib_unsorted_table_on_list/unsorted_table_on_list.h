#pragma once
#include <stdexcept>
#include "..\lib_itable\itable.h"
#include "..\lib_tvector\tvector.h"

template<class TKey, class TVal>
class UnsortedTableOnArr : public ITable<TKey, TVal>
{
private:

    TVector<typename ITable<TKey, TVal>::Row> rows;

public:

    void insert(const TKey& key, const TVal& value) override
    {
        for (size_t i = 0; i < rows.size(); i++)
        {
            if (rows[i].key == key)
            {
                throw std::logic_error("key_exists");
            }
        }

        typename ITable<TKey, TVal>::Row r;
        r.key = key;
        r.value = value;

        rows.push_back(r);
    }

    void erase(const TKey& key) override
    {
        for (size_t i = 0; i < rows.size(); i++)
        {
            if (rows[i].key == key)
            {
                rows.erase(i);
                return;
            }
        }

        throw std::out_of_range("non_found");
    }

    TVal& find(const TKey& key) override
    {
        for (size_t i = 0; i < rows.size(); i++)
        {
            if (rows[i].key == key)
            {
                return rows[i].value;
            }
        }

        throw std::out_of_range("non_found");
    }

    bool contains(const TKey& key) const override
    {
        for (size_t i = 0; i < rows.size(); i++)
        {
            if (rows[i].key == key)
            {
                return true;
            }
        }

        return false;
    }

    size_t size() const override
    {
        return rows.size();
    }

    bool empty() const override
    {
        return rows.size() == 0;
    }

    void clear() override
    {
        rows.clear();
    }
};