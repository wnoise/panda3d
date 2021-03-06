// Filename: cylindricalLens.I
// Created by:  drose (12Dec01)
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

////////////////////////////////////////////////////////////////////
//     Function: CylindricalLens::Constructor
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
INLINE CylindricalLens::
CylindricalLens() {
}

////////////////////////////////////////////////////////////////////
//     Function: CylindricalLens::Copy Constructor
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
INLINE CylindricalLens::
CylindricalLens(const CylindricalLens &copy) : Lens(copy) {
}

////////////////////////////////////////////////////////////////////
//     Function: CylindricalLens::Copy Assignment Operator
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void CylindricalLens::
operator = (const CylindricalLens &copy) {
  Lens::operator = (copy);
}

