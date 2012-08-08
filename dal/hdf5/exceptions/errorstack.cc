/* Copyright 2011-2012  ASTRON, Netherlands Institute for Radio Astronomy
 * This file is part of the Data Access Library (DAL).
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "dal/dal_config.h"
#include "dal/dal_version.h"
#include "dal/hdf5/exceptions/errorstack.h"
#include "dal/hdf5/exceptions/exceptions.h"
#include <hdf5.h>

namespace DAL {

/*!
 * Disables HDF5 error printing to stderr by uninstalling the HDF5 error handler
 * throughout the life time of the DAL library. This class only silences errors
 * if QUIET_HDF5_ERRORS is defined (through CMake).
 */
class GlobalDisableErrorPrinting {
public:
  GlobalDisableErrorPrinting(): dep(quietErrors() ? new DisableErrorPrinting : NULL) {}
  ~GlobalDisableErrorPrinting() { delete dep; }
private:
  /*!
   * Return whether error printing should be silenced.
   */
  bool quietErrors() const;

  const DisableErrorPrinting *dep;
};

static GlobalDisableErrorPrinting gdep;

bool GlobalDisableErrorPrinting::quietErrors() const {
#ifndef QUIET_HDF5_ERRORS
  return false;
#endif

  // Don't cause us to abort already
  if (!check_hdf5_versions())
    return false;

  return true;  
}

ScopedErrorStack::ScopedErrorStack()
:
  olderrorstack(H5Eget_current_stack())
{
}

ScopedErrorStack::~ScopedErrorStack() {
  if(H5Eset_current_stack(olderrorstack) < 0)
    throw HDF5Exception("Could not restore error stack");
}

DisableErrorPrinting::DisableErrorPrinting() {
  // remove the handler but save the old one
  H5Eget_auto2(H5E_DEFAULT, &oldhandler, &oldclientdata);
  H5Eset_auto2(H5E_DEFAULT, NULL, NULL);
}

DisableErrorPrinting::~DisableErrorPrinting() {
  // restore the old handler
  H5Eset_auto2(H5E_DEFAULT, oldhandler, oldclientdata);
}

std::string HDF5StackLine::shortDesc() const {
  std::ostringstream oss(std::ostringstream::out);

  oss << func_name << "(): " << desc;

  return oss.str();
}

std::string HDF5StackLine::longDesc() const {
  std::ostringstream oss(std::ostringstream::out);

  oss << "Error in " << file_name << ":" << line << " " << func_name << "(): " << desc << "; major = " << maj << "; minor = " << min;

  return oss.str();
}

HDF5ErrorStack::HDF5ErrorStack()
{
  // save the stack in case it is cleared during walkng
  // H5Eget_current_stack also clears the error stack
  hid_t stackid = H5Eget_current_stack();

  // walk downwards: from the API call to the innermost function
  if (H5Ewalk2(stackid, H5E_WALK_DOWNWARD, &walker, this) < 0) {
    /* our walker does not generate any errors yet */
  } 

  // restore the error stack, such that subsequent code
  // can still analyse it -- note that
  // 1) this quiets errors generated by the walker function
  // 2) a subsequent HDF5 API call typically clears the error stack
  H5Eset_current_stack(stackid);
}

std::vector<struct HDF5StackLine> HDF5ErrorStack::stack() const {
  return _stack;
}

herr_t HDF5ErrorStack::walker(unsigned n, const H5E_error2_t *err_desc, void *clientdata)
{
  HDF5ErrorStack *obj = static_cast<HDF5ErrorStack *>(clientdata);

  // marshall the C-style stack line `eptr` to the C++ struct `HDF5StackLine`
  char      maj[80];
  char      min[80];
  char      cls[80];

  struct HDF5StackLine stackline;

  stackline.n        = n;

  stackline.cls_id   = err_desc->cls_id;
  stackline.maj_num  = err_desc->maj_num;
  stackline.min_num  = err_desc->min_num;

  stackline.line     = err_desc->line;
  stackline.func_name= err_desc->func_name;
  stackline.file_name= err_desc->file_name;

  stackline.desc     = err_desc->desc;

  /* Get descriptions for the major and minor error numbers */
  if (H5Eget_class_name(err_desc->cls_id, cls, sizeof cls) >= 0)
    stackline.cls = cls;
  else
    stackline.cls = "(unknown)";

  if (H5Eget_msg(err_desc->maj_num, NULL, maj, sizeof maj) >= 0)
    stackline.maj = maj;
  else
    stackline.maj = "(unknown)";

  if (H5Eget_msg(err_desc->min_num, NULL, min, sizeof min) >= 0)
    stackline.min = min;
  else
    stackline.min = "(unknown)";

  obj->_stack.push_back(stackline);
  return 0;
}

void HDF5ErrorStack::clear() {
  H5Eclear2(H5E_DEFAULT);
}


}

