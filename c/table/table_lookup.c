#include "../include/ft_table.h"
#include "table.h"

#include "../include/ft_swiss.h"

int ft_table_contains(ft_table* t, void* entry, uint64_t hash)
{
    size_t mask = t->mask;

    size_t pos = ft_swiss_probe_start(hash, t->capacity);

    uint8_t fp = ft_swiss_h2(hash);

    size_t dist = 0;

    while (1)
    {
        uint8_t ctrl = t->ctrl[pos];

        if (ft_swiss_is_empty(ctrl))
            return 0;

        if (ft_swiss_match(ctrl, fp))
        {
            if (t->hashes[pos] == hash &&
                t->entries[pos] == entry)
                return 1;
        }

        size_t ideal = t->hashes[pos] & mask;
        size_t resident_dist = (pos - ideal) & mask;

        if (resident_dist < dist)
            return 0;

        pos = (pos + 1) & mask;
        dist++;
    }
}