#ifndef __H5ERRORHANDLING__
#define __H5ERRORHANDLING__

#include "hdf5.h"
#include <string>
#include <vector>
#include <sstream>

/*
 * See http://www.hdfgroup.org/HDF5/doc/UG/13_ErrorHandling.html
 * and http://www.hdfgroup.org/HDF5/doc/RM/RM_H5E.html
 */

namespace DAL {

/*!
 * Saves and restores the current error stack. Useful for preserving
 * the HDF5 error state if it cannot be counted on to be empty.
 *
 * Example usage as a scope guard:
 *   {
 *      ScopedErrorStack ses();
 *
 *      ... code that can generate and handle HDF5 errors ...
 *   }
 */
class ScopedErrorStack {
public:
  ScopedErrorStack(): olderrorstack(H5Eget_current_stack()) {
  }

  ~ScopedErrorStack() {
    if(H5Eset_current_stack(olderrorstack) < 0)
      /* TODO */;
  }
private:
  const hid_t olderrorstack;
};

/*!
 * Prevent HDF5 from printing errors directly on stderr within
 * the scope of any DisableErrorPrinting object.
 *
 * Note that this class disables any automatic error handling
 * mechanism installed into HDF5, including those installed
 * by other libraries using HDF5, if any.
 */
class DisableErrorPrinting {
public:
  DisableErrorPrinting() {
    // remove the handler but save the old one
    H5Eget_auto2(H5E_DEFAULT, &oldhandler, &oldclientdata);
    H5Eset_auto2(H5E_DEFAULT, NULL, NULL);
  }

  ~DisableErrorPrinting() {
    // restore the old handler
    H5Eset_auto2(H5E_DEFAULT, oldhandler, oldclientdata);
  }

private:  
  H5E_auto2_t oldhandler;
  void *oldclientdata;
};

/*!
 * All information about a single stack-trace line for HDF5 error handling routines.
 */
struct HDF5StackLine {
  unsigned n;            //!< Index number within this stack trace (starting at 0)

  hid_t cls_id;          //!< Identifier for the module generating this error
  hid_t maj_num;         //!< Major error number
  hid_t min_num;         //!< Minor error number

  unsigned line;         //!< Source line number
  std::string func_name; //!< Source function name
  std::string file_name; //!< Source file name

  std::string desc;      //!< Error description

  std::string cls;       //!< Module in which error occurred ("HDF5" for all errors generated by HDF5)
  std::string maj;       //!< Description of major error number
  std::string min;       //!< Description of minor error number

  /*!
   * Returns a short description of this stack line, useful for reporting errors.
   */
  std::string shortDesc() const {
    std::ostringstream oss(std::ostringstream::out);

    oss << func_name << "(): " << desc;

    return oss.str();
  }

  /*!
   * Returns an extensive description of this stack line, useful for debugging errors.
   */
  std::string longDesc() const {
    std::ostringstream oss(std::ostringstream::out);

    oss << "Error in " << file_name << ":" << line << " " << func_name << "(): " << desc << "; major = " << maj << "; minor = " << min;

    return oss.str();
  }
};


/*!
 * Saves and wraps the current HDF5 error stack.
 */
class HDF5ErrorStack {
public:
  /*!
   * The HDF5 error stack as it was when this object was constructed.
   */
  std::vector<struct HDF5StackLine> stack;

private:  
  static herr_t walker(unsigned n, const H5E_error2_t *err_desc, void *clientdata) {
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

    obj->stack.push_back(stackline);
    return 0;
  }

public:
  HDF5ErrorStack() {
    // save the stack in case it is cleared during walkng
    // H5Eget_current_stack also clears the error stack
    hid_t stackid = H5Eget_current_stack();

    // walk downwards: from the API call to the innermost function
    if (H5Ewalk2(stackid, H5E_WALK_DOWNWARD, &walker, this) < 0) {
      /* TODO */
    } 

    // restore the error stack, such that subsequent code
    // can still analyse it -- note that
    // 1) this quiets errors generated by the walker function
    // 2) a subsequent HDF5 API call typically clears the error stack
    H5Eset_current_stack(stackid);
  }

  /*!
   * Clear the HDF5 error stack
   */
  static void clear() {
    H5Eclear2(H5E_DEFAULT);
  }
};

}

#endif