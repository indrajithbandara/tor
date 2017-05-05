/* Copyright (c) 2017, The Tor Project, Inc. */
/* See LICENSE for licensing information */

#ifndef TOR_CONSDIFFMGR_H
#define TOR_CONSDIFFMGR_H

/**
 * Possible outcomes from trying to look up a given consensus diff.
 */
typedef enum consdiff_status_t {
  CONSDIFF_AVAILABLE,
  CONSDIFF_NOT_FOUND,
  CONSDIFF_IN_PROGRESS,
} consdiff_status_t;

typedef struct consdiff_cfg_t {
  int32_t cache_max_age_hours;
  int32_t cache_max_num;
} consdiff_cfg_t;

struct consensus_cache_entry_t; // from conscache.h

int consdiffmgr_add_consensus(const char *consensus,
                              const networkstatus_t *as_parsed);

consdiff_status_t consdiffmgr_find_diff_from(
                           struct consensus_cache_entry_t **entry_out,
                           consensus_flavor_t flavor,
                           int digest_type,
                           const uint8_t *digest,
                           size_t digestlen,
                           compress_method_t method);
void consdiffmgr_rescan(void);
int consdiffmgr_cleanup(void);
void consdiffmgr_enable_background_compression(void);
void consdiffmgr_configure(const consdiff_cfg_t *cfg);
struct sandbox_cfg_elem;
int consdiffmgr_register_with_sandbox(struct sandbox_cfg_elem **cfg);
void consdiffmgr_free_all(void);
int consdiffmgr_validate(void);

#ifdef CONSDIFFMGR_PRIVATE
STATIC unsigned n_diff_compression_methods(void);
STATIC consensus_cache_t *cdm_cache_get(void);
STATIC consensus_cache_entry_t *cdm_cache_lookup_consensus(
                          consensus_flavor_t flavor, time_t valid_after);
STATIC int cdm_entry_get_sha3_value(uint8_t *digest_out,
                                    consensus_cache_entry_t *ent,
                                    const char *label);
STATIC int uncompress_or_copy(char **out, size_t *outlen,
                              consensus_cache_entry_t *ent);
#endif

#endif

