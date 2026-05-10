#pragma once
#include <stdexcept>
#include <vector>
#include "..\lib_itable\itable.h"

template<class TKey, class TVal>
class SortedTableOnArr : public Table<TKey, TVal>
{
private:
    std::vector<typename Table<TKey, TVal>::Row> rows;

    int findIndex(const TKey& key) const
    {
        int left = 0;
        int right = (int)rows.size() - 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (rows[mid].key == key)
                return mid;

            if (key < rows[mid].key)
                right = mid - 1;
            else
                left = mid + 1;
        }

        return -1;
    }

    // позици€ вставки (нельз€ объединить с fI)
    int lowerBound(const TKey& key) const
    {
        int left = 0;
        int right = (int)rows.size() - 1;
        int result = rows.size();

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (rows[mid].key < key)
                left = mid + 1;
            else
            {
                result = mid;
                right = mid - 1;
            }
        }

        return result;
    }

public:

    void insert(const TKey& key, const TVal& value) override
    {
        int pos = lowerBound(key);

        // если ключ уже есть Ч ничего не делаем
        if (pos < rows.size() && rows[pos].key == key)
            return;

        typename Table<TKey, TVal>::Row r;
        r.key = key;
        r.value = value;

        rows.insert(rows.begin() + pos, r);
    }

    void erase(const TKey& key) override
    {
        int index = findIndex(key);

        if (index == -1)
            throw std::out_of_range("non_found");

        rows.erase(rows.begin() + index);
    }

    TVal& find(const TKey& key) override
    {
        int index = findIndex(key);

        if (index == -1)
            throw std::out_of_range("non_found");

        return rows[index].value;
    }

    bool contains(const TKey& key) const override
    {
        return findIndex(key) != -1;
    }

    size_t size() const override
    {
        return rows.size();
    }

    bool empty() const override
    {
        return rows.empty();
    }

    void clear() override
    {
        rows.clear();
    }

    const typename Table<TKey, TVal>::Row& getRow(size_t index) const override
    {
        if (index >= rows.size())
            throw std::out_of_range("index_out_of_range");

        return rows[index];
    }
};