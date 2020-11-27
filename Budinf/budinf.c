#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mmzone.h>
#include <linux/stddef.h>
#include <linux/mm.h>

#define DRI_ATH "Philip Poretsky <pporetsky@gmail.com/ptp24@njit.edu>"
#define DRI_DSC "Recreate Proc buddyinf"

struct pglist_data *first_online_pgdat(void)
{
	return NODE_DATA(first_online_node);
}

struct pglist_data *next_online_pgdat(struct pglist_data *pgdat)
{
	int nid = next_online_node(pgdat->node_id);

	if (nid == MAX_NUMNODES)
		return NULL;
	return NODE_DATA(nid);
}

/*
 * next_zone - helper magic for for_each_zone()
 */
struct zone *next_zone(struct zone *zone)
{
	pg_data_t *pgdat = zone->zone_pgdat;

	if (zone < pgdat->node_zones + MAX_NR_ZONES - 1)
		zone++;
	else {
		pgdat = next_online_pgdat(pgdat);
		if (pgdat)
			zone = pgdat->node_zones;
		else
			zone = NULL;
	}
	return zone;
}

static inline int zref_in_nodemask(struct zoneref *zref, nodemask_t *nodes)
{
#ifdef CONFIG_NUMA
	return node_isset(zonelist_node_idx(zref), *nodes);
#else
	return 1;
#endif /* CONFIG_NUMA */
}

/* Returns the next zone at or below highest_zoneidx in a zonelist */
struct zoneref *__next_zones_zonelist(struct zoneref *z,
					enum zone_type highest_zoneidx,
					nodemask_t *nodes)
{
	/*
	 * Find the next suitable zone to use for the allocation.
	 * Only filter based on nodemask if it's set
	 */
	if (unlikely(nodes == NULL))
		while (zonelist_zone_idx(z) > highest_zoneidx)
			z++;
	else
		while (zonelist_zone_idx(z) > highest_zoneidx ||
				(z->zone && !zref_in_nodemask(z, nodes)))
			z++;

	return z;
}

#ifdef CONFIG_ARCH_HAS_HOLES_MEMORYMODEL
bool memmap_valid_within(unsigned long pfn,
					struct page *page, struct zone *zone)
{
	if (page_to_pfn(page) != pfn)
		return false;

	if (page_zone(page) != zone)
		return false;

	return true;
}
#endif /* CONFIG_ARCH_HAS_HOLES_MEMORYMODEL */

void lruvec_init(struct lruvec *lruvec)
{
	enum lru_list lru;

	memset(lruvec, 0, sizeof(struct lruvec));

	for_each_lru(lru)
		INIT_LIST_HEAD(&lruvec->lists[lru]);
}

#if defined(CONFIG_NUMA_BALANCING) && !defined(LAST_CPUPID_NOT_IN_PAGE_FLAGS)
int page_cpupid_xchg_last(struct page *page, int cpupid)
{
	unsigned long old_flags, flags;
	int last_cpupid;

	do {
		old_flags = flags = page->flags;
		last_cpupid = page_cpupid_last(page);

		flags &= ~(LAST_CPUPID_MASK << LAST_CPUPID_PGSHIFT);
		flags |= (cpupid & LAST_CPUPID_MASK) << LAST_CPUPID_PGSHIFT;
	} while (unlikely(cmpxchg(&page->flags, old_flags, flags) != old_flags));

	return last_cpupid;
}
#endif

pg_data_t *bigbudi;
struct zone *zbuddo;

static int __init muhpg(void)
{
bigbudi = first_online_pgdat();
zbuddo = bigbudi->node_zones;
	printk(KERN_INFO "Phil's BuddyInfo\n");
    while(bigbudi){
        while(zbuddo){
            int i;
            printk(KERN_CONT "Node: %d Name: %s ", bigbudi->node_id,zbuddo->name);
            for(i=0; i<11;i++){
                printk(KERN_CONT "%lu ",zbuddo->free_area[i].nr_free);
            } 
            printk(KERN_INFO "\n");
            zbuddo = next_zone(zbuddo);
        }
        bigbudi = next_online_pgdat(bigbudi);
    }
return 0;
}

static void __exit endpg(void)
{
    printk(KERN_INFO "End Process\n");
} 

module_init(muhpg);
module_exit(endpg);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRI_ATH);
MODULE_DESCRIPTION(DRI_DSC);
MODULE_SUPPORTED_DEVICE("testdevice");