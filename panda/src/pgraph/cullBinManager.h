// Filename: cullBinManager.h
// Created by:  drose (27Feb02)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) Carnegie Mellon University.  All rights reserved.
//
// All use of this software is subject to the terms of the revised BSD
// license.  You should have received a copy of this license along
// with this source code in a file named "LICENSE."
//
////////////////////////////////////////////////////////////////////

#ifndef CULLBINMANAGER_H
#define CULLBINMANAGER_H

#include "pandabase.h"
#include "cullBin.h"
#include "cullBinEnums.h"
#include "pointerTo.h"
#include "pvector.h"
#include "epvector.h"
#include "pmap.h"
#include "vector_int.h"
#include "pStatCollector.h"

class CullResult;
class GraphicsStateGuardianBase;

////////////////////////////////////////////////////////////////////
//       Class : CullBinManager
// Description : This is a global object that maintains the collection
//               of named CullBins in the world.
////////////////////////////////////////////////////////////////////
class EXPCL_PANDA_PGRAPH CullBinManager : public CullBinEnums {
protected:
  CullBinManager();
  ~CullBinManager();

PUBLISHED:
  typedef CullBin::BinType BinType;

  int add_bin(const string &name, BinType type, int sort);
  void remove_bin(int bin_index);

  INLINE int get_num_bins() const;
  INLINE int get_bin(int n) const;
  MAKE_SEQ(get_bins, get_num_bins, get_bin);
  int find_bin(const string &name) const;

  INLINE string get_bin_name(int bin_index) const;

  INLINE BinType get_bin_type(int bin_index) const;
  INLINE BinType get_bin_type(const string &name) const;
  INLINE void set_bin_type(int bin_index, BinType type);
  INLINE void set_bin_type(const string &name, BinType type);

  INLINE int get_bin_sort(int bin_index) const;
  INLINE int get_bin_sort(const string &name) const;
  INLINE void set_bin_sort(int bin_index, int sort);
  INLINE void set_bin_sort(const string &name, int sort);

  INLINE bool get_bin_active(int bin_index) const;
  INLINE bool get_bin_active(const string &name) const;
  INLINE void set_bin_active(int bin_index, bool active);
  INLINE void set_bin_active(const string &name, bool active);

#ifndef NDEBUG
  INLINE bool get_bin_flash_active(int bin_index) const;
  INLINE const LColor &get_bin_flash_color(int bin_index) const;
  INLINE void set_bin_flash_active(int bin_index, bool active);
  INLINE void set_bin_flash_color(int bin_index, const LColor &color);
#endif

  void write(ostream &out) const;

  INLINE static CullBinManager *get_global_ptr();

public:
  // This interface is only intended to be used by CullResult.
  PT(CullBin) make_new_bin(int bin_index, GraphicsStateGuardianBase *gsg,
                           const PStatCollector &draw_region_pcollector);

  // This defines the factory interface for defining constructors to
  // bin types (the implementations are in the cull directory, not
  // here in pgraph, so we can't call the constructors directly).
  typedef CullBin *BinConstructor(const string &name,
                                  GraphicsStateGuardianBase *gsg,
                                  const PStatCollector &draw_region_pcollector);

  void register_bin_type(BinType type, BinConstructor *constructor);

private:
  void do_sort_bins();
  void setup_initial_bins();
  static BinType parse_bin_type(const string &bin_type);

  class EXPCL_PANDA_PGRAPH BinDefinition {
  public:
#ifndef NDEBUG
    LColorf _flash_color;
    bool _flash_active;
#endif
    bool _in_use;
    string _name;
    BinType _type;
    int _sort;
    bool _active;
  };
  typedef epvector<BinDefinition> BinDefinitions;
  BinDefinitions _bin_definitions;

  class SortBins {
  public:
    INLINE SortBins(CullBinManager *manager);
    INLINE bool operator () (int a, int b) const;
    CullBinManager *_manager;
  };

  typedef pmap<string, int> BinsByName;
  BinsByName _bins_by_name;

  typedef vector_int SortedBins;
  SortedBins _sorted_bins;
  bool _bins_are_sorted;
  bool _unused_bin_index;

  typedef pmap<BinType, BinConstructor *> BinConstructors;
  BinConstructors _bin_constructors;

  static CullBinManager *_global_ptr;
  friend class SortBins;
};

EXPCL_PANDA_PGRAPH ostream &
operator << (ostream &out, CullBinManager::BinType bin_type);

#include "cullBinManager.I"

#endif
