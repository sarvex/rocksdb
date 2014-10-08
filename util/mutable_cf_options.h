// Copyright (c) 2014, Facebook, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.

#pragma once

#include <vector>
#include "rocksdb/options.h"
#include "rocksdb/immutable_options.h"

namespace rocksdb {

struct MutableCFOptions {
  MutableCFOptions(const Options& options, const ImmutableCFOptions& ioptions)
    : write_buffer_size(options.write_buffer_size),
      arena_block_size(options.arena_block_size),
      memtable_prefix_bloom_bits(options.memtable_prefix_bloom_bits),
      memtable_prefix_bloom_probes(options.memtable_prefix_bloom_probes),
      memtable_prefix_bloom_huge_page_tlb_size(
          options.memtable_prefix_bloom_huge_page_tlb_size),
      max_successive_merges(options.max_successive_merges),
      filter_deletes(options.filter_deletes),
      level0_file_num_compaction_trigger(
          options.level0_file_num_compaction_trigger),
      level0_slowdown_writes_trigger(options.level0_slowdown_writes_trigger),
      level0_stop_writes_trigger(options.level0_stop_writes_trigger),
      max_grandparent_overlap_factor(options.max_grandparent_overlap_factor),
      expanded_compaction_factor(options.expanded_compaction_factor),
      source_compaction_factor(options.source_compaction_factor),
      target_file_size_base(options.target_file_size_base),
      target_file_size_multiplier(options.target_file_size_multiplier),
      max_bytes_for_level_base(options.max_bytes_for_level_base),
      max_bytes_for_level_multiplier(options.max_bytes_for_level_multiplier),
      max_bytes_for_level_multiplier_additional(
          options.max_bytes_for_level_multiplier_additional)
  {
    RefreshDerivedOptions(ioptions);
  }
  MutableCFOptions()
    : write_buffer_size(0),
      arena_block_size(0),
      memtable_prefix_bloom_bits(0),
      memtable_prefix_bloom_probes(0),
      memtable_prefix_bloom_huge_page_tlb_size(0),
      max_successive_merges(0),
      filter_deletes(false),
      level0_file_num_compaction_trigger(0),
      level0_slowdown_writes_trigger(0),
      level0_stop_writes_trigger(0),
      max_grandparent_overlap_factor(0),
      expanded_compaction_factor(0),
      source_compaction_factor(0),
      target_file_size_base(0),
      target_file_size_multiplier(0),
      max_bytes_for_level_base(0),
      max_bytes_for_level_multiplier(0)
  {}

  // Must be called after any change to MutableCFOptions
  void RefreshDerivedOptions(const ImmutableCFOptions& ioptions);

  // Get the max file size in a given level.
  uint64_t MaxFileSizeForLevel(int level) const;
  // Returns maximum total bytes of data on a given level.
  uint64_t MaxBytesForLevel(int level) const;
  // Returns maximum total overlap bytes with grandparent
  // level (i.e., level+2) before we stop building a single
  // file in level->level+1 compaction.
  uint64_t MaxGrandParentOverlapBytes(int level) const;
  uint64_t ExpandedCompactionByteSizeLimit(int level) const;

  // Memtable related options
  size_t write_buffer_size;
  size_t arena_block_size;
  uint32_t memtable_prefix_bloom_bits;
  uint32_t memtable_prefix_bloom_probes;
  size_t memtable_prefix_bloom_huge_page_tlb_size;
  size_t max_successive_merges;
  bool filter_deletes;

  // Compaction related options
  int level0_file_num_compaction_trigger;
  int level0_slowdown_writes_trigger;
  int level0_stop_writes_trigger;
  int max_grandparent_overlap_factor;
  int expanded_compaction_factor;
  int source_compaction_factor;
  int target_file_size_base;
  int target_file_size_multiplier;
  uint64_t max_bytes_for_level_base;
  int max_bytes_for_level_multiplier;
  std::vector<int> max_bytes_for_level_multiplier_additional;

  // Derived options
  // Per-level target file size.
  std::vector<uint64_t> max_file_size;
  // Per-level max bytes
  std::vector<uint64_t> level_max_bytes;
};

}  // namespace rocksdb
