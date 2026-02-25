#include "../include/ft_table.h"
#include "table.h"

#include "../include/ft_swiss.h"
#include "../include/ft_robinhood.h"
#include "../include/ft_config.h"

int ft_table_insert(ft_table* t, void* entry, uint64_t hash)
{
    if ((double)t->size / t->capacity >= FT_LOAD_FACTOR)
        ft_table_resize(t);

    size_t mask = t->mask;
    size_t pos = ft_swiss_probe_start(hash, t->capacity);
    uint8_t fp = ft_swiss_h2(hash);

    size_t dist = 0;

    while (1)
    {
        uint8_t ctrl = t->ctrl[pos];

        if (ft_swiss_is_empty(ctrl) ||
            ft_swiss_is_deleted(ctrl))
        {
            t->ctrl[pos] = fp;
            t->hashes[pos] = hash;
            t->entries[pos] = entry;
            t->size++;
            return 1;
        }

        if (ft_swiss_match(ctrl, fp))
        {
            if (t->hashes[pos] == hash &&
                t->entries[pos] == entry)
                return 0;
        }

        size_t ideal = t->hashes[pos] & mask;
        size_t resident_dist = (pos - ideal) & mask;

        if (ft_rh_should_swap(dist, resident_dist))
        {
            uint64_t tmp_hash = t->hashes[pos];
            void* tmp_entry = t->entries[pos];
            uint8_t tmp_ctrl = t->ctrl[pos];

            t->hashes[pos] = hash;
            t->entries[pos] = entry;
            t->ctrl[pos] = fp;

            hash = tmp_hash;
            entry = tmp_entry;
            fp = tmp_ctrl;

            dist = resident_dist;
        }

        pos = (pos + 1) & mask;
        dist++;
    }
}